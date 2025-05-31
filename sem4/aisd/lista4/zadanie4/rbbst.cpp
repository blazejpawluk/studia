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
	NIL = new Node{0, NIL, NIL, NIL, 'b'};
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

void fixupInsert(Node* x) {
	x->color = 'r';
	while (x != root && read(x->parent)->color == 'r') {
		if (read(x->parent) == read(x->parent->parent->left)) {
			Node* y = read(x->parent->parent->right);
			if (y->color == 'r') {
				read(x->parent)->color = 'b';
				y->color = 'b';
				read(x->parent->parent)->color = 'r';
				x = read(x->parent->parent);
			} else {
				if (x == read(x->parent->right)) {
					x = read(x->parent);
					leftRotate(x);
				}
				read(x->parent)->color = 'b';
				read(x->parent->parent)->color = 'r';
				rightRotate(read(x->parent->parent));
			}
		} else {
			Node* y = read(x->parent->parent->left);
			if (y->color == 'r') {
				read(x->parent)->color = 'b';
				y->color = 'b';
				read(x->parent->parent)->color = 'r';
				x = read(x->parent->parent);
			} else {
				if (x == read(x->parent->left)) {
					x = read(x->parent);
					rightRotate(x);
				}
				read(x->parent)->color = 'b';
				read(x->parent->parent)->color = 'r';
				leftRotate(read(x->parent->parent));
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
		if (compare(key < x->key)) x = read(x->left);
		else x = read(x->right);
	}

	Node* newNode = new Node{key, NIL, NIL, parent, 'r'};
	
	if (parent == NIL) root = read(newNode);
	else if (compare(key < parent->key)) parent->left = read(newNode);
	else parent->right = read(newNode);
	
	fixupInsert(newNode);
}

Node* find(Node* node, int key) {
	if (node == NIL || compare(node->key == key)) return node;
	if (compare(node->key < key)) return find(read(node->right), key);
	return find(read(node->left), key);
}

Node* treeMinimum(Node* node) {
	while (node != NIL && read(node->left) != NIL) node = read(node->left);
	return node;
}

Node* succesor(Node* node) {
	if (read(node->right) != NIL) return treeMinimum(read(node->right));
	Node* parent = read(node->parent);
	while (parent != NIL && node == read(parent->right)) {
		node = parent;
		parent = read(parent->parent);
	}
	return parent;
}

void fixUpDelete(Node* node) {
	while (node != root && node->color == 'b') {
		if (node == read(node->parent->left)) {
			Node* w = read(node->parent->right);
			if (w->color == 'r') {
				leftRotate(read(node->parent));
				w = read(node->parent->right);
			}

			if (read(w->left)->color == 'b' && read(w->right)->color == 'b') {
				w->color = 'r';
				node = read(node->parent);
			} else {
				if (read(w->right)->color == 'b') {
					read(w->left)->color = 'b';
					w->color = 'r';
					rightRotate(w);
					w = read(node->parent->right);
				}

				w->color = read(node->parent)->color;
				read(node->parent)->color = 'b';
				read(w->right)->color = 'b';
				leftRotate(read(node->parent));
				node = root;
			}
		} else {
			Node* w = read(node->parent->left);
			if (w->color == 'r') {
				w->color = 'b';
				read(node->parent)->color = 'r';
				rightRotate(read(node->parent));
				w = read(node->parent->left);
			}

			if (read(w->right)->color == 'b' && read(w->left)->color == 'b') {
				w->color = 'r';
				node = read(node->parent);
			} else {
				if (read(w->left)->color == 'b') {
					read(w->right)->color = 'b';
					w->color = 'r';
					leftRotate(w);
					w = read(node->parent->left);
				}

				w->color = read(node->parent)->color;
				read(node->parent)->color = 'b';
				read(w->left)->color = 'b';
				rightRotate(read(node->parent));
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
		if (read(toDelete->left) == NIL || read(toDelete->right) == NIL) y = toDelete;
		else y = succesor(toDelete);

		Node* x;
		if (read(y->left) != NIL) x = read(y->left);
		else x = read(y->right);

		x->parent = read(read(y->parent));

		if (read(y->parent) == NIL) root = x;
		else if (y == read(y->parent->left)) y->parent->left = read(x);
		else y->parent->right = read(x);

		if (y != toDelete) toDelete->key = y->key;
		if (y->color == 'b') fixUpDelete(x);
		delete y;
	}
}

int Height(Node* node) {
	if (node == NIL) return 0;
	int heightL = Height(read(node->left)), heightR = Height(read(node->right));
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