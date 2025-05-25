#ifndef BST
#define BST

#include <iostream>
using namespace std;

struct Node{
	int key;
	Node* left;
	Node* right;
};

Node* root;

Node* Insert(Node* node, int key) {
	if (node == nullptr) node = new Node{key, nullptr, nullptr};
	else if (node->key > key) node->left = Insert(node->left, key);
	else node->right = Insert(node->right, key);
	return node;
}

Node* successor(Node* node) {
	node = node->right;
	while (node != nullptr && node->left != nullptr) node = node->left;
	return node;
}

Node* Delete(Node* node, int key) {
	if (node == nullptr) return nullptr;
	if (node->key > key) node->left = Delete(node->left, key);
	else if (node->key < key) node->right = Delete(node->right, key);
	else {
		if (node->left == nullptr && node->right == nullptr) node = nullptr;
		else if (node->left == nullptr) node = node->right;
		else if (node->right == nullptr) node = node->left;
		else {
			Node* succ = successor(node);
			node->key = succ->key;
			node->right = Delete(node->right, succ->key);
		}
	}
	return node;
}

int Height(Node* node) {
	if (node == nullptr) return 0;
	int heightL = Height(node->left), heightR = Height(node->right);
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