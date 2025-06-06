#ifndef HEAP
#define HEAP

#include <bits/stdc++.h>
using namespace std;

struct Node {
	int key;
	int degree;
	Node* parent;
	Node* child;
	Node* sibling;
};

Node* makeNode(int x) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->key = x;
	node->degree = 0;
	node->parent = nullptr;
	node->child = nullptr;
	node->sibling = nullptr;
	return node;
}

int comps;
bool compare(bool a) {
	comps++;
	return a;
}

// used in extractMin
Node* reverseList(Node* x) {
	Node* prev = nullptr;
	Node* curr = x;
	Node* next;

	while (curr) {
		next = curr->sibling;
		curr->sibling = prev;
		curr->parent = nullptr;
		prev = curr;
		curr = next;
	}

	return prev;
}

// used in union
Node* mergeRootLists(Node* H1, Node* H2) {
	if (!H1) return H2;
	if (!H2) return H1;

	Node* head = nullptr;
	Node* tail = nullptr;
	Node* a = H1;
	Node* b = H2;

	if (a->degree <= b->degree) {
		head = a;
		a = a->sibling;
	} else {
		head = b;
		b = b->sibling;
	}
	tail = head;

	while (a && b) {
		if (a->degree <= b->degree) {
			tail->sibling = a;
			a = a->sibling;
		} else {
			tail->sibling = b;
			b = b->sibling;
		}
		tail = tail->sibling;
	}

	if (a) tail->sibling = a;
	else tail->sibling = b;

	return head;
}

// used in union
Node* linkTrees(Node* r1, Node* r2) {
	r2->parent = r1;
	r2->sibling = r1->child;
	r1->child = r2;
	r1->degree++;
	return r1;
}

Node* MakeHeap() {return nullptr;}

Node* Union(Node* H1, Node* H2) {
	Node* newHead = mergeRootLists(H1, H2);
	if (!newHead) return nullptr;

	Node* prev = nullptr;
	Node* curr = newHead;
	Node* next = curr->sibling;

	while (next) {
		if (curr->degree != next->degree || (next->sibling && next->sibling->degree == curr->degree)) {
			prev = curr;
			curr = next;
		} else if (compare(curr->key <= next->key)) {
			curr->sibling = next->sibling;
			linkTrees(curr, next);
		} else {
			if (!prev) newHead = next;
			else prev->sibling = next;
			linkTrees(next, curr);
			curr = next;
		}
		next = curr->sibling;
	}

	return newHead;
}

Node* Insert(Node* H, int x) {
	Node* newNode = makeNode(x);
	H = Union(H, newNode);
	return H;
}

Node* Minimum(Node* H) {
	if (!H) return nullptr;

	Node* y = nullptr;
	Node* x = H;

	int minKey = INT_MAX;
	while (x) {
		if (compare(x->key < minKey)) {
			minKey = x->key;
			y = x;
		}
		x = x->sibling;
	}

	return y;
}

Node* ExtractMin(Node* H, int& minKeyOut) {
	if (!H) {
		minKeyOut = INT_MAX;
		return nullptr;
	}

	Node* prevMin = nullptr;
	Node* minNode = H;
	Node* prev = nullptr;
	Node* curr = H;
	int minKey = curr->key;

	while (curr) {
		if (compare(curr->key < minKey)) {
			minKey = curr->key;
			prevMin = prev;
			minNode = curr;
		}
		prev = curr;
		curr = curr->sibling;
	}

	if (!prevMin) H = minNode->sibling;
	else prevMin->sibling = minNode->sibling;

	Node* childList = reverseList(minNode->child);

	minKeyOut = minNode->key;

	free(minNode);

	H = Union(H, childList);

	return H;
}

void DecreaseKey(Node* x, int newKey) {
	if (!x || compare(newKey > x->key)) return;

	x->key = newKey;
	Node* y = x;
	Node* z = y->parent;

	while (z && compare(y->key < z->key)) {
		int temp = y->key;
		y->key = z->key;
		z->key = temp;

		y = z;
		z = y->parent;
	}
}

Node* Delete(Node* H, Node* x) {
	if (!H || !x) return H;

	DecreaseKey(x, INT_MIN);
	int dummy;
	H = ExtractMin(H, dummy);
	return H;
}

void printHeap(Node* root, int indent = 0) {
	if (!root) return;

	for (int i = 0; i < indent; i++) cout << "  ";

	cout << root->key << endl;

	printHeap(root->child, indent+1);
	printHeap(root->sibling, indent);
}

Node* find(Node* x, int v) {
	if (x == nullptr) return nullptr;
	if (compare(x->key == v)) return x;
	if (compare(x->key > v)) return find(x->sibling, v);
	Node* sibling = find(x->sibling, v);
	Node* child = find(x->child, v);
	return sibling ? sibling : child;
}

#endif