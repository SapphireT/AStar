#include "myAStar.h"
#include <iostream>

using namespace std;

// map 1: obstacles; 0: no obstacle
vector<vector<int>> MAP = {
	{ 0,0,0,0,0,0,0 },
	{ 0,0,0,1,0,0,0 },
	{ 0,0,0,1,0,0,0 },
	{ 0,0,1,1,0,1,0 },
	{ 0,0,1,1,0,1,0 },
	{ 0,0,0,1,0,0,0 },
	{ 0,0,0,0,0,0,0 }
};

int main() {

	// print map
	cout << "******MAP******(0: no obstacle; 1: obstacles)" << endl;
	for (int y = 0; y < MAP.size(); ++y) {
		for (int x = 0; x < MAP[0].size(); ++x) {
			cout << MAP[y][x] << ' ';
		}
		cout << endl;
	}
	
	int startX, startY, endX, endY;
	int method;
	cout << "Input start point x, y coordinates" << endl;
	cout << "Start point X: ";
	cin >> startX;
	cout << "Start point Y: ";
	cin >> startY;

	cout << "Input end point x, y coordinates" << endl;
	cout << "End point X: ";
	cin >> endX;
	cout << "End point Y: ";
	cin >> endY;
	cout<< "Heuristic method (0: EUCLIDEAN METRIC, 1: MANHATTAN DISTANCE, OTHER: BAD)";
	cin >> method;

	Node *start = new Node(startX, startY);
	Node *end = new Node(endX, endY);

	Node *path = new Node;
	AStar astar;
	path = astar.findPath(start, end, method);

	// print path
	vector<vector<int>> PATH = MAP;
	cout << endl << "Total length of the found path: " << path->G << endl;
	while (path) {
		PATH[path->y][path->x] = 2;
		path = path->father;
	}
	cout << endl << "***PATH******(2: path points)" << endl;
	for (int y = 0; y < MAP.size(); ++y) {
		for (int x = 0; x < MAP[0].size(); ++x) {
			cout << PATH[y][x] << ' ';
		}
		cout << endl;
	}

	system("pause");
	return 0;
}