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

int comps;
bool compare(bool a) {
	comps++;
	return a;
}

int reads;
Node* read(Node* node) {
	reads++;
	return node;
}

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
	Node* x = read(node->right);
	node->right = read(read(x->left));
	if (read(x->left) != NIL) x->left->parent = read(node);
	x->parent = read(read(node->parent));
	if (read(node->parent) == NIL) root = x;
	else if (node == read(node->parent->left)) node->parent->left = read(x);
	else node->parent->right = read(x);
	x->left = read(node);
	node->parent = read(x);
}

void rightRotate(Node* node) {
	Node* x = read(node->left);
	node->left = read(read(x->right));
	if (read(x->right) != NIL) x->right->parent = read(node);
	x->parent = read(read(node->parent));
	if (read(node->parent) == NIL) root = x;
	else if (node == read(node->parent->left)) node->parent->left = read(x);
	else node->parent->right = read(x);
	x->right = read(node);
	node->parent = read(x);
}

void splay(Node* node) {
	while (read(node->parent) != NIL) {
		if (read(node->parent->parent) == NIL) {
			if (node == read(node->parent->left)) rightRotate(read(node->parent));
			else leftRotate(read(node->parent));
		} else if (node == read(node->parent->left) && read(node->parent) == read(node->parent->parent->left)) {
			rightRotate(read(node->parent->parent));
			rightRotate(read(node->parent));
		} else if (node == read(node->parent->right) && read(node->parent) == read(node->parent->parent->right)) {
			leftRotate(read(node->parent->parent));
			leftRotate(read(node->parent));
		} else if (node == read(node->parent->right) && read(node->parent) == read(node->parent->parent->left)) {
			leftRotate(read(node->parent));
			rightRotate(read(node->parent));
		} else {
			rightRotate(read(node->parent));
			leftRotate(read(node->parent));
		}
	}
}

Node* find(Node* node, int key) {
	if (node == NIL || compare(node->key == key)) return node;
	if (compare(node->key < key)) return find(read(node->right), key);
	return find(read(node->left), key);
}

Node* treeMaximum(Node* node) {
	while (read(node->right) != NIL) node = read(node->right);
	return node;
}

void Insert(Node* node, int key) {
	Node* parent = NIL;
	Node* x = node;
	while (x != NIL) {
		parent = x;
		if (compare(key < x->key)) x = read(x->left);
		else x = read(x->right);
	}

	Node* newNode = new Node{key, NIL, NIL, parent};
	
	if (parent == NIL) root = newNode;
	else if (compare(key < parent->key)) parent->left = read(newNode);
	else parent->right = read(newNode);

	splay(newNode);
}

void Delete(Node* node, int key) {
	Node* z = find(root, key);
	if (z == NIL) return;
	splay(z);
	if (read(z->left) == NIL) {
		Node* x = read(z->right);
		x->parent = read(NIL);
		root = x;
		delete z;
	} else if (read(z->right) == NIL) {
		Node* x = read(z->left);
		x->parent = read(NIL);
		root = x;
		delete z;
	} else {
		Node* leftSub = read(z->left);
		leftSub->parent = read(NIL);
		Node* rightSub = read(z->right);
		rightSub->parent = read(NIL);
		delete z;
		Node* maxNode = treeMaximum(leftSub);
		root = leftSub;
		splay(maxNode);
		maxNode->right = read(rightSub);
		rightSub->parent = read(maxNode);
		root = maxNode;
	}
}

int height(Node* node) {
	if (node == NIL) return 0;
	int heightL = height(read(node->left)), heightR = height(read(node->right));
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