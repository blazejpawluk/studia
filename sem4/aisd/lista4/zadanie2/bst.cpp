#ifndef BST
#define BST

#include <iostream>
using namespace std;

struct Node {
	int key;
	Node* left;
	Node* right;
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

Node* Insert(Node* node, int key) {
	if (node == nullptr) node = new Node{key, nullptr, nullptr};
	else if (compare(node->key > key)) node->left = read(Insert(read(node->left), key));
	else node->right = read(Insert(read(node->right), key));
	return node;
}

Node* successor(Node* node) {
	node = read(node->right);
	while (node != nullptr && read(node->left) != nullptr) node = read(node->left);
	return node;
}

Node* Delete(Node* node, int key) {
	if (node == nullptr) return nullptr;
	if (compare(node->key > key)) node->left = read(Delete(read(node->left), key));
	else if (compare(node->key < key)) node->right = read(Delete(read(node->right), key));
	else {
		if (read(node->left) == nullptr && read(node->right) == nullptr) node = nullptr;
		else if (read(node->left) == nullptr) node = read(node->right);
		else if (read(node->right) == nullptr) node = read(node->left);
		else {
			Node* succ = successor(node);
			node->key = succ->key;
			node->right = read(Delete(read(node->right), succ->key));
		}
	}
	return node;
}

int Height(Node* node) {
	if (node == nullptr) return 0;
	int heightL = Height(read(node->left)), heightR = Height(read(node->right));
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
	cout << "[" << node->key << "]\n";
	left_trace[depth] = ' ';
	if (node->right != nullptr) {
		right_trace[depth] = '|';
		Print(node->right, depth + 1, '\\');
	}
}

#endif