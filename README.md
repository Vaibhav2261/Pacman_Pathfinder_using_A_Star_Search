# Pacman-using-A-*
Pacman Pathfinding Game
This project is a simple console-based Pacman game, where the player controls Pacman to find the shortest path to a goal position on a grid. The grid contains barriers that Pacman must navigate around to reach the goal. The game uses the A (A-star) search algorithm* to compute the shortest path, considering walkable cells and barriers.

Table of Contents
1.Game Overview
2.A* Search Algorithm
3.Graph Theory Concepts
4.Shortest Path Finding
5.How to Play
6.Sample Output 

1. Game Overview:
The Pacman game takes place on a grid where:
Each cell can be either walkable, a barrier, or the start/goal.
Barriers are randomly placed based on the selected difficulty level.
The goal is to find the shortest path for Pacman to reach the target position using the A* search algorithm.
The grid displays the path with '*' symbols, and Pacman's current position is shown as P.

2. A* Search Algorithm:
The A search algorithm* is used to find the shortest path in the grid. It combines Dijkstra’s Algorithm (finding the shortest path with minimal cost) with a heuristic approach to guide the search, making it both efficient and effective for pathfinding tasks.

Key Features of A* Algorithm:
G Cost: The actual cost from the start node to the current node.
H Cost: A heuristic estimate of the cost from the current node to the goal node. Here, the Manhattan distance is used as the heuristic.
F Cost: The sum of G and H, which is used to prioritize nodes in the search.
A* Process:
A priority queue stores the nodes in the order of their F values, with lower F values having higher priority.
The algorithm explores neighboring cells (up, down, left, right) to find the least-cost path to the goal.
When the goal is reached, the algorithm reconstructs the path by backtracking through parent nodes.

3. Graph Theory Concepts:
In this project:
Each cell on the grid is a node in a graph.
Each walkable path between cells is an edge with a cost (1 in this case).
The start and goal nodes are specific cells representing Pacman’s starting position and target.
The grid is undirected, as each cell can potentially move in any direction to its neighbors.

4. Shortest Path Finding:
In this game:
The A* algorithm determines the shortest route Pacman can take to reach the goal, avoiding barriers.
The chosen heuristic (Manhattan distance) effectively estimates the distance in grid-based pathfinding problems.

5. How to Play:
Initialize the Game: Enter the grid dimensions, start, and goal positions.
Set Difficulty: Choose a difficulty level between 1 and 5. Higher levels increase the number of barriers.
Find the Path: The game displays the initial grid. Press Enter to let Pacman move step-by-step along the computed path.
Reach the Goal: The game marks each step Pacman takes and prints the message upon reaching the goal.

6. Sample Output:
Upon execution, the game displays a grid with Pacman (P), barriers (#), walkable spaces (.), and the goal path (*). Pacman moves along the path step-by-step, with each step appearing in real time.
