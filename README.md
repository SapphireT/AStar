# AStar
This is the C++ implementation of A* algorithm.
This code uses VS 2017 community.

In the program, first, you are given a block map. (1 denotes there is an obstacle; 0 denotes no obstacle)

Then, input starting and ending point coordinates. (pick two points without obstacles from the given map)

Input method index to calculate the heuristic. (0 denotes using euclidean metric, 1 denotes using Manhattan distance, otherwise using a bad heuristic which can be longer than the real distance between current point and ending point)
