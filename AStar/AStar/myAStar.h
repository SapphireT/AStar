#pragma once
#include <vector>
#include <math.h>

const int EUCLIDEAN_MTR = 0; // Euclidean metric
const int MANHATTAN_DST = 1; // Manhattan distance

extern std::vector<std::vector<int>> MAP; // map 1: obstacles; 0: no obstacle

class Node {
	friend class Queue;
	friend class AStar;
	friend int main();
private:
	// father node
	Node *father;
	// the G, H, F value
	double G, H, F;
	// coordinates
	int x, y;

public:
	// constructor
	Node(int _x = 0, int _y = 0):
		x(_x), y(_y), F(0), G(0), H(0) {
		father = NULL;
	}

	// overload "="
	Node & operator= (const Node &node) {
		if (this != &node) {
			G = node.G;
			H = node.H;
			F = node.F;
			x = node.x;
			y = node.y;
			father = node.father;
		}
		return *this;
	}

	// overload "=="
	bool operator== (const Node &node) const {
		return x == node.x && y == node.y;
	}

	// calculate the distance between 2 nodes, method
	double distanceTo(const Node &node, int method = EUCLIDEAN_MTR) const {
		if (method == EUCLIDEAN_MTR) {
			return sqrt(pow(node.x - x, 2) + pow(node.y - y, 2));
		}
		else if (method == MANHATTAN_DST) {
			return abs(double(node.x - x)) + abs(double(node.y - y));
		}
		else
			return 2 * (abs(double(node.x - x)) + abs(double(node.y - y)));
	}

};

class QueueNode {
	friend class Queue;
	friend class AStar;
private:
	Node *data;
	QueueNode *link;
};

class Queue {
	friend class AStar;
private:
	QueueNode *front;
	int length;
public:
	// constructor
	Queue(): front(NULL), length(0){}

	// deconstructor
	~Queue() {
		QueueNode *next;
		while (front) {
			next = front->link;
			delete front;
			front = next;
		}
	}

	// if the Queue is empty or not
	bool isEmpty()const;

	// Add a node in terms of G value
	Queue & addItoG(Node * &node);

	// Add a node in terms of F value
	Queue & addItoF(Node * &node);

	// Delete the front node in the queue, and get the front value
	Queue & Delete(Node* &node);
};


class AStar {
public:
	Node * findPath(const Node* start, const Node* end, int method = EUCLIDEAN_MTR) const;
	bool isInQueue(const Queue* queue, const Node * node) const;
	bool isReachable(const Node* cur, const Node* node, const Queue* close) const;
	std::vector<Node*> getNeighborNodes(const Node * node, const Queue* close) const;
	double calcG(const Node *start, const Node *node) const;
	double calcH(const Node *end, const Node *node, int method = EUCLIDEAN_MTR) const;
};