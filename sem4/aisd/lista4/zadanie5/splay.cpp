#ifndef SPLAY
#define SPLAY

#include <iostream>
using namespace std;

struct Node {
	int key;
	Node* left;
	Node* right;
	Node* parent;
};

Node* root;
Node* NIL;

void initNIL() {
	NIL = new Node;
	NIL->left = NIL;
	NIL->right = NIL;
	NIL->parent = NIL;
	root = NIL;
}

void leftRotate(Node* node) {
	Node* x = node->right;
	node->right = x->left;
	if (x->left != NIL) x->left->parent = node;
	x->parent = node->parent;
	if (node->parent == NIL) root = x;
	else if (node == node->parent->left) node->parent->left = x;
	else node->parent->right = x;
	x->left = node;
	node->parent = x;
}

void rightRotate(Node* node) {
	Node* x = node->left;
	node->left = x->right;
	if (x->right != NIL) x->right->parent = node;
	x->parent = node->parent;
	if (node->parent == NIL) root = x;
	else if (node == node->parent->left) node->parent->left = x;
	else node->parent->right = x;
	x->right = node;
	node->parent = x;
}

void splay(Node* x) {
	while (x->parent != NIL) {
		if (x->parent->parent == NIL) {
			if (x == x->parent->left) rightRotate(x->parent);
			else leftRotate(x->parent);
		} else if (x == x->parent->left && x->parent == x->parent->parent->left) {
			rightRotate(x->parent->parent);
			rightRotate(x->parent);
		} else if (x == x->parent->right && x->parent == x->parent->parent->right) {
			leftRotate(x->parent->parent);
			leftRotate(x->parent);
		} else if (x == x->parent->right && x->parent == x->parent->parent->left) {
			leftRotate(x->parent);
			rightRotate(x->parent);
		} else {
			rightRotate(x->parent);
			leftRotate(x->parent);
		}
	}
}

Node* find(Node* node, int key) {
	if (node == NIL || node->key == key) return node;
	if (node->key < key) return find(node->right, key);
	return find(node->left, key);
}

Node* treeMaximum(Node* node) {
	while (node->right != NIL) node = node->right;
	return node;
}

void Insert(Node* node, int key) {
	Node* parent = NIL;
	Node* x = node;
	while (x != NIL) {
		parent = x;
		if (key < x->key) x = x->left;
		else x = x->right;
	}

	Node* newNode = new Node{key, NIL, NIL, parent};
	
	if (parent == NIL) root = newNode;
	else if (key < parent->key) parent->left = newNode;
	else parent->right = newNode;

	splay(newNode);
}

void Delete(Node* node, int key) {
	Node* z = find(root, key);
	if (z == NIL) return;
	splay(z);
	if (z->left == NIL) {
		Node* temp = z->right;
		temp->parent = NIL;
		root = temp;
		delete z;
	} else if (z->right == NIL) {
		Node* temp = z->left;
		temp->parent = NIL;
		root = temp;
		delete z;
	} else {
		Node* leftSub = z->left;
		leftSub->parent = NIL;
		Node* rightSub = z->right;
		rightSub->parent = NIL;
		delete z;
		Node* maxNode = treeMaximum(leftSub);
		root = leftSub;
		splay(maxNode);
		maxNode->right = rightSub;
		rightSub->parent = maxNode;
		root = maxNode;
	}
}

int height(Node* node) {
	if (node == NIL) return 0;
	int heightL = height(node->left), heightR = height(node->right);
	return (heightL > heightR ? heightL : heightR) + 1;
}

char left_trace[30];
char right_trace[30];
void Print(Node* node, int depth, char prefix) {
	if (node == NIL) return;
	if (node->left != NIL) Print(node->left, depth + 1, '/');
	if (prefix == '/') left_trace[depth - 1] = '|';
	if (prefix == '\\') right_trace[depth - 1] = ' ';
	if (depth == 0) cout << "-";
	if (depth > 0) cout << " ";
	for (int i = 0; i < depth - 1; i++) {
		if (left_trace[i] == '|' || right_trace[i] == '|') cout << "| ";
		else cout << "  ";
	}
	if (depth > 0) cout << prefix << "-";
	cout << "[" << node->key << "]" << endl;
	left_trace[depth] = ' ';
	if (node->right != NIL) {
		right_trace[depth] = '|';
		Print(node->right, depth + 1, '\\');
	}
}

#endif
