#include "myAStar.h"

bool Queue::isEmpty()const {
	return (front ? false : true);
}

Queue & Queue::addItoG(Node * &node) {
	QueueNode *p = front;
	// the front node is of the smallest G value
	while (p && p->link && (node->G) > (p->link->data->G)) {
		p = p->link;
	}
	// add the new node
	QueueNode * tmp = new QueueNode;
	tmp->data = node;
	tmp->link = NULL;

	if (!front) {
		front = tmp;
		length++;
		return *this;
	}

	if (p != front || (node->G) > front->data->G) {
		tmp->link = p->link;
		p->link = tmp;		
	}
	else {
		tmp->link = front;
		front = tmp;
	}
	length++;
	return *this;
}

Queue & Queue::addItoF(Node * &node) {
	QueueNode *p = front;
	// the front node is of the smallest F value
	while (p && p->link && (node->F) > (p->link->data->F)) {
		p = p->link;
	}
	// add the new node
	QueueNode * tmp = new QueueNode;
	tmp->data = node;
	tmp->link = NULL;

	if (!front) {
		front = tmp;
		length++;
		return *this;
	}

	if (p != front || (node->F) > front->data->F) {
		tmp->link = p->link;
		p->link = tmp;
	}
	else {
		tmp->link = front;
		front = tmp;
	}
	length++;
	return *this;
}

Queue & Queue::Delete(Node* &node) {
	node = front->data;
	QueueNode *tmp = front->link;
	delete front;
	front = tmp;
	length--;
	return *this;
}

// the main function for A* Algorithm
Node * AStar::findPath(const Node* start, const Node* end, int method) const {
	Queue *OPEN = new Queue; // the open list
	Queue * CLOSE = new Queue; // the close list
	Node *tmp1, *tmp2;
	tmp2 = new Node;
	tmp1 = new Node(start->x, start->y);
	OPEN->addItoF(tmp1);

	// start node = end node
	if (*tmp1 == *end) {
		return tmp1;
	}

	while ( !OPEN->isEmpty() ) {

		OPEN->Delete(tmp2);
		if (*tmp2 == *end) {
			return tmp2;
		}

		// move the current node from OPEN to CLOSE list
		CLOSE->addItoG(tmp2);		
		std::vector<Node*> neightbors = getNeighborNodes(tmp2, CLOSE);
		for (auto &node : neightbors) {
			if (!isInQueue(OPEN, node)) {
				node->father = tmp2;
				node->G = calcG(tmp2, node);
				node->H = calcH(node, end, method);
				node->F = node->G + node->H;
				OPEN->addItoF(node);
			}
			else {
				double tmpG = calcG(tmp2, node);
				if (tmpG < node->G) {
					node->father = tmp2;
					node->G = tmpG;
					node->F = node->G + node->F;
				}
			}
		}
	}
	return NULL;
}

bool AStar::isInQueue(const Queue* queue, const Node * node) const {
	QueueNode * p = queue->front;
	while (p) {
		if (*(p->data) == *(node)) {
			return true;
		}
		p = p->link;
	}
	return false;
}

// return the reachable neighbor nodes in the map
std::vector<Node *> AStar::getNeighborNodes(const Node * node, const Queue* close) const {
	std::vector<Node *> neighbors;
	for (int x = node->x - 1; x < node->x + 2; x++) {
		for (int y = node->y - 1; y < node->y + 2; y++) {
			if (isReachable(node, new Node(x, y), close)) {
				neighbors.push_back(new Node(x, y));
			}
		}
	}
	return neighbors;
}

// determine if a node is reachable to a neighboring node
bool AStar::isReachable(const Node* cur, const Node* node, const Queue* close) const {
	if (node->x<0 || node->x>MAP[0].size() - 1 || node->y<0 || node->y>MAP.size() - 1 ||
		MAP[node->y][node->x] || *cur == *node ||isInQueue(close, node)) {
		return false;
	}
	return true;
}

double AStar::calcG(const Node *start, const Node *node) const {
	double fatherG = start->father ? start->father->G : 0;
	return fatherG + node->distanceTo(*start);
}
double AStar::calcH(const Node *end, const Node *node, int method) const {
	return node->distanceTo(*end, method);
}