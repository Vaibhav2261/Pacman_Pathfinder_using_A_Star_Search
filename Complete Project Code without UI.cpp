#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <random>  // For random number generation
#include <cstdlib> // For system("clear") or system("CLS") on Windows

using namespace std;

// Node class representing a cell on the grid
class Node {
public:
    int x, y; // Position
    float g, h; // Cost values
    Node* parent; // Pointer to the parent node (for path reconstruction)

    Node(int _x, int _y, float _g = 0, float _h = 0, Node* _parent = nullptr)
        : x(_x), y(_y), g(_g), h(_h), parent(_parent) {}

    float f() const {
        return g + h; // Total cost function
    }
};

// Comparator for priority queue (min-heap)
struct Compare {
    bool operator()(const Node* a, const Node* b) {
        return a->f() > b->f(); // Min-heap based on f()
    }
};

// Grid class representing the Pacman game grid
class Grid {
private:
    vector<vector<int>> grid;
    int rows, cols;

public:
    Grid(int _rows, int _cols) : rows(_rows), cols(_cols) {
        grid.resize(rows, vector<int>(cols, 0)); // Initialize grid with 0s (walkable spaces)
    }

    void setBarrier(int x, int y) {
        if (x >= 0 && y >= 0 && x < rows && y < cols)
            grid[x][y] = 1; // Set barrier (wall)
    }

    bool isWalkable(int x, int y) const {
        return x >= 0 && y >= 0 && x < rows && y < cols && grid[x][y] == 0;
    }

    void markPath(const vector<Node*>& path) {
        for (const auto& node : path) {
            if (grid[node->x][node->y] == 0) // Avoid overwriting start and goal positions
                grid[node->x][node->y] = 2; // Mark path with 2 (we'll display it as '*')
        }
    }

    void displayGrid(const pair<int, int>& pacmanPos) const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (pacmanPos.first == i && pacmanPos.second == j)
                    cout << "P "; // Pacman's position
                else if (grid[i][j] == 1)
                    cout << "# "; // Barrier
                else if (grid[i][j] == 2)
                    cout << "* "; // Path
                else
                    cout << ". "; // Free space
            }
            cout << endl;
        }
        cout << endl;
    }

    int getRows() const { return rows; }
    int getCols() const { return cols; }
};

// AStar class implementing the A* search algorithm
class AStar {
private:
    Grid& grid;
    pair<int, int> start;
    pair<int, int> goal;

public:
    AStar(Grid& _grid, pair<int, int> _start, pair<int, int> _goal)
        : grid(_grid), start(_start), goal(_goal) {}

    // Heuristic function (Manhattan distance)
    int heuristic(int x1, int y1, int x2, int y2) {
        return abs(x1 - x2) + abs(y1 - y2);
    }

    // A* algorithm to find the shortest path
    vector<Node*> findPath() {
        priority_queue<Node*, vector<Node*>, Compare> openList;
        vector<vector<bool>> closedList(grid.getRows(), vector<bool>(grid.getCols(), false));

        Node* startNode = new Node(start.first, start.second, 0, heuristic(start.first, start.second, goal.first, goal.second));
        openList.push(startNode);

        while (!openList.empty()) {
            Node* current = openList.top();
            openList.pop();

            // Check if we've reached the goal
            if (current->x == goal.first && current->y == goal.second) {
                return reconstructPath(current); // Return the path
            }

            closedList[current->x][current->y] = true;

            // Explore neighbors (up, down, left, right)
            vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
            for (auto& dir : directions) {
                int nx = current->x + dir.first, ny = current->y + dir.second;

                if (grid.isWalkable(nx, ny) && !closedList[nx][ny]) {
                    float newG = current->g + 1; // Each step has a cost of 1
                    Node* neighbor = new Node(nx, ny, newG, heuristic(nx, ny, goal.first, goal.second), current);
                    openList.push(neighbor);
                }
            }
        }
        return {}; // Return empty path if no solution found
    }

private:
    // Reconstruct the path from goal to start using parent pointers
    vector<Node*> reconstructPath(Node* current) {
        vector<Node*> path;
        while (current != nullptr) {
            path.push_back(current);
            current = current->parent;
        }
        reverse(path.begin(), path.end()); // Start to goal order
        return path;
    }
};

// PacmanGame class to manage the game
class PacmanGame {
private:
    Grid grid;
    pair<int, int> start;
    pair<int, int> goal;

public:
    PacmanGame(int rows, int cols, pair<int, int> _start, pair<int, int> _goal)
        : grid(rows, cols), start(_start), goal(_goal) {}

    void setLevel(int level) {
        int totalCells = grid.getRows() * grid.getCols();
        int numBarriers = static_cast<int>(totalCells * 0.05 * level); // 5% * level

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> rowDist(0, grid.getRows() - 1);
        uniform_int_distribution<> colDist(0, grid.getCols() - 1);

        int placedBarriers = 0;
        while (placedBarriers < numBarriers) {
            int x = rowDist(gen);
            int y = colDist(gen);

            // Avoid placing barriers on the start or goal positions
            if ((x != start.first || y != start.second) && 
                (x != goal.first || y != goal.second) && 
                grid.isWalkable(x, y)) {
                grid.setBarrier(x, y);
                placedBarriers++;
            }
        }
    }

    void startGame() {
        AStar astar(grid, start, goal);
        vector<Node*> path = astar.findPath();

        if (!path.empty()) {
            // Mark and display the final path
            grid.markPath(path);
            cout << "Final path to goal (marked with '*'):\n";
            grid.displayGrid(start);

            cout << "\nPath found! Press Enter to move Pacman step-by-step:\n";
            for (auto& step : path) {
                system("clear"); // Clears screen on Unix-based systems; use "CLS" on Windows
                grid.displayGrid({step->x, step->y});
                cout << "Pacman moves to (" << step->x << ", " << step->y << ")" << endl;
                cin.ignore(); // Waits for user to press Enter to proceed
            }
            cout << "Pacman reached the goal!" << endl;
        } else {
            cout << "No path found." << endl;
        }
    }

    void printInitialGrid() const {
        grid.displayGrid(start);
    }
};

int main() {
    int rows, cols;
    cout << "Enter grid dimensions (rows and cols): ";
    cin >> rows >> cols;

    int startX, startY, goalX, goalY;
    cout << "Enter Pacman's starting position (x y): ";
    cin >> startX >> startY;
    cout << "Enter goal position (x y): ";
    cin >> goalX >> goalY;

    PacmanGame game(rows, cols, {startX, startY}, {goalX, goalY});

    int level;
    cout << "Select game level (1-5): ";
    cin >> level;

    game.setLevel(level);

    cout << "\nInitial Grid:\n";
    game.printInitialGrid();

    cin.ignore(); // Clear input buffer
    game.startGame();

    return 0;
}
