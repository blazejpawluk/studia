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

void fixupDelete(Node* x) {
	while (x != root && x->color == 'b') {
		if (x == x->parent->left) {
			Node* w = x->parent->right;
			if (w->color == 'r') {
				w->color = 'b';
				w->parent->color = 'r';
				leftRotate(x->parent);
				w = x->parent->right;
			}

			if (w->left->color == 'b' && w->right->color == 'b') {
				w->color = 'r';
				x = x->parent;
			} else {
				if (w->right->color == 'b') {
					w->left->color = 'b';
					w->color = 'r';
					rightRotate(w);
					w = x->parent->right;
				}

				x->color = x->parent->color;
				x->parent->color = 'b';
				x->right->color = 'b';
				leftRotate(x->parent);
				x = root;
			}
		} else {
			Node* w = x->parent->left;
			if (w->color == 'r') {
				w->color = 'b';
				x->parent->color = 'r';
				rightRotate(x->parent);
				w = x->parent->left;
			}

			if (w->right->color == 'b' && w->left->color == 'b') {
				w->color = 'r';
				x = x->parent;
			} else {
				if (w->left->color == 'b') {
					w->right->color = 'b';
					w->color = 'r';
					leftRotate(w);
					w = x->parent->left;
				}

				w->color = x->parent->color;
				x->parent->color = 'b';
				w->left->color = 'b';
				rightRotate(x->parent);
				x = root;
			}
		}
	}
	x->color = 'b';
}

Node* find(Node* node, int key) {
	if (node == NIL) return NIL;
	if (node->key == key) return node;
	if (node->key < key) return find(node->right, key);
	return find(node->left, key);
}

Node* successor(Node* node) {
	if (node->right != NIL) {
		while (node != NIL && node->right != NIL) node = node->right;
		return node;
	}

	Node* parent = node->parent;
	while (parent != NIL && node == parent->right) {
		node = parent;
		parent = parent->right;
	}
	return parent;
}

void Delete(Node* node, int key) {
	Node *x = NIL, *y = NIL;
	Node* delNode = find(root, key);

	if (delNode == NIL) return;

	if (delNode->left == NIL || delNode->right == NIL) y = delNode;
	else y = successor(delNode);

	if (y->left != NIL) x = y->left;
	else x = y->right;

	x->parent = y->parent;

	if (y->parent == NIL) root = x;
	else if (y == y->parent->left) y->parent->left = x;
	else y->parent->right = x;

	if (y != delNode) delNode->key = y->key;

	if (y->color == 'b') fixupDelete(x);
	delete y;
}

int height(Node* node) {
	if (node == NIL) return 0;
	int heightL = height(node->left), heightR = height(node->right);
	return (heightL > heightR ? heightL : heightR) + 1;
}

char left_trace[30];
char right_trace[30];
void Print(Node* node, int depth, char prefix) {
	if (node == nullptr) return;
	if (node->left != nullptr) Print(node->left, depth + 1, '/');
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
	if (node->right != nullptr) {
		right_trace[depth] = '|';
		Print(node->right, depth + 1, '\\');
	}
}

#endif