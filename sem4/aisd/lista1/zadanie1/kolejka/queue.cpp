#include <iostream>
#include <string>
using namespace std;

class Queue {
private: 
	struct Node {
		int value;
		Node* next;
		Node(int value) {
			this->value = value;
			this->next = nullptr;
		}
	};

	Node* begin;
	Node* end;
	int size;

public:
	Queue() {
		this->begin = nullptr;
		this->end = nullptr;
		this->size = 0;
	}

	int getSize() {
		return this->size;
	}

	void add(int value) {
		Node* newNode = new Node(value);

		if(this->size == 0) {
			this->begin = newNode;
			this->end = newNode;
			this->size = 1;
		} else {
			this->end->next = newNode;
			this->end = newNode;
			this->size++;
		}
	}

	int drop() {
		if(this->size == 0) {
			return -1;
		} 

		Node* firstNode = this->begin;
		this->begin = this->begin->next;
		delete(firstNode);
		this->size--;

		if(this->size == 0) {
			this->end = nullptr;
		}
		return 0;
	}

	bool isEmpty() {
		return this->size == 0;
	}

	void print() {
		Node* currentNode = this->begin;

		if(currentNode != nullptr) {
			while(currentNode != nullptr) {
				cout << currentNode->value << " ";
				currentNode = currentNode->next;
			}
		} else {
			cout << "empty queue";
		}
	}

	~Queue() {
		while(!isEmpty()) {
			drop();
		}
	}
};

int main() {
	Queue queue;

	

	return 0;
}