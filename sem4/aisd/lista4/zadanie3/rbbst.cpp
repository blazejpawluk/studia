#ifndef RBBST
#define RBBST

#include <iostream>
using namespace std;

struct Node {
	int key;
	Node* left;
	Node* right;
	Node* parent;
	char color;
};

Node* root;
Node* NIL;

void initNIL() {
	NIL = new Node{0, NIL, NIL, NIL, 'b'};
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

void fixupInsert(Node* x) {
	x->color = 'r';
	while (x != root && x->parent->color == 'r') {
		if (x->parent == x->parent->parent->left) {
			Node* y = x->parent->parent->right;
			if (y->color == 'r') {
				x->parent->color = 'b';
				y->color = 'b';
				x->parent->parent->color = 'r';
				x = x->parent->parent;
			} else {
				if (x == x->parent->right) {
					x = x->parent;
					leftRotate(x);
				}
				x->parent->color = 'b';
				x->parent->parent->color = 'r';
				rightRotate(x->parent->parent);
			}
		} else {
			Node* y = x->parent->parent->left;
			if (y->color == 'r') {
				x->parent->color = 'b';
				y->color = 'b';
				x->parent->parent->color = 'r';
				x = x->parent->parent;
			} else {
				if (x == x->parent->left) {
					x = x->parent;
					rightRotate(x);
				}
				x->parent->color = 'b';
				x->parent->parent->color = 'r';
				leftRotate(x->parent->parent);
			}
		}
	}
	root->color = 'b';
}

void Insert(Node* node, int key) {
	Node* parent = NIL;
	Node* x = node;
	while (x != NIL) {
		parent = x;
		if (key < x->key) x = x->left;
		else x = x->right;
	}

	Node* newNode = new Node{key, NIL, NIL, parent, 'r'};
	
	if (parent == NIL) root = newNode;
	else if (key < parent->key) parent->left = newNode;
	else parent->right = newNode;
	
	fixupInsert(newNode);
}

Node* find(Node* node, int key) {
	if (node == NIL || node->key == key) return node;
	if (node->key < key) return find(node->right, key);
	return find(node->left, key);
}

Node* treeMinimum(Node* node) {
	while (node != NIL && node->left != NIL) node = node->left;
	return node;
}

Node* succesor(Node* node) {
	if (node->right != NIL) return treeMinimum(node->right);
	Node* parent = node->parent;
	while (parent != NIL && node == parent->right) {
		node = parent;
		parent = parent->parent;
	}
	return parent;
}

void fixUpDelete(Node* node) {
	while (node != root && node->color == 'b') {
		if (node == node->parent->left) {
			Node* w = node->parent->right;
			if (w->color == 'r') {
				leftRotate(node->parent);
				w = node->parent->right;
			}

			if (w->left->color == 'b' && w->right->color == 'b') {
				w->color = 'r';
				node = node->parent;
			} else {
				if (w->right->color == 'b') {
					w->left->color = 'b';
					w->color = 'r';
					rightRotate(w);
					w = node->parent->right;
				}

				w->color = node->parent->color;
				node->parent->color = 'b';
				w->right->color = 'b';
				leftRotate(node->parent);
				node = root;
			}
		} else {
			Node* w = node->parent->left;
			if (w->color == 'r') {
				w->color = 'b';
				node->parent->color = 'r';
				rightRotate(node->parent);
				w = node->parent->left;
			}

			if (w->right->color == 'b' && w->left->color == 'b') {
				w->color = 'r';
				node = node->parent;
			} else {
				if (w->left->color == 'b') {
					w->right->color = 'b';
					w->color = 'r';
					leftRotate(w);
					w = node->parent->left;
				}

				w->color = node->parent->color;
				node->parent->color = 'b';
				w->left->color = 'b';
				rightRotate(node->parent);
				node = root;
			}
		}
	}
	node->color = 'b';
}

void Delete(Node* node, int key) {
	Node* toDelete = find(root, key);
	if (toDelete != NIL) {
		Node* y = NIL;
		if (toDelete->left == NIL || toDelete->right == NIL) y = toDelete;
		else y = succesor(toDelete);

		Node* x;
		if (y->left != NIL) x = y->left;
		else x = y->right;

		x->parent = y->parent;

		if (y->parent == NIL) root = x;
		else if (y == y->parent->left) y->parent->left = x;
		else y->parent->right = x;

		if (y != toDelete) toDelete->key = y->key;
		if (y->color == 'b') fixUpDelete(x);
		delete y;
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
	cout << (node->color == 'b' ? "[" : "(") << node->key << (node->color == 'b' ? "]" : ")") << endl;
	left_trace[depth] = ' ';
	if (node->right != NIL) {
		right_trace[depth] = '|';
		Print(node->right, depth + 1, '\\');
	}
}

#endif