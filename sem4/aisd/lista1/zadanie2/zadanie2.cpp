#include <iostream>
#include <cstdlib>
using namespace std;

class List {
private:
	struct Node {
		int value;
		Node* next;

		Node(int value) {
			this->value = value;
		}
	};

	Node* node;
	int size;

public:
	List() {
		this->node = nullptr;
		this->size = 0;
	}

	Node* getNode() {
		return this->node;
	}

	int getSize() {
		return this->size;
	}

	void insert(int value) {
		Node* newNode = new Node(value);

		if(this->size == 0) {
			newNode->next = newNode;
			this->node = newNode;
		} else {
			newNode->next = this->node->next;
			this->node->next = newNode;
		}
		this->size++;
	}

	void merge(List l) {
		Node* nextNode = this->node->next;
		this->node->next = l.getNode();

		Node* currentNode = l.getNode();
		for(int i = 0; i < l.getSize() - 1; i++) {
			currentNode = currentNode->next;
		}
		currentNode->next = nextNode;
		this->size += l.getSize();
	}

	void print() {
		if(this->size == 0) {
			cout << "empty list";
		} else {
			for(int i = 0; i < this->size; i++) {
				cout << this->node->value << " ";
				this->node = this->node->next;
			}
		}
		cout << endl;
	}
};

List insert(List l, int i) {
	l.insert(i);
	return l;
}

List merge(List l1, List l2) {
	l1.merge(l2);
	return l1;
}

int main() {
	List l1;
	List l2;

	for(int i = 0; i < 5; i++) {
		l1 = insert(l1, rand() % 10 + 1);
		l2 = insert(l2, rand() % 10 + 1);
	}

	l1.print();
	l2.print();

	l1 = merge(l1, l2);
	l1.print();

	return 0;
}