#include <iostream>
using namespace std;

class Stack {
private:
	struct Node {
		int value;
		Node* next;
		Node(int value) {
			this->value = value;
		}
	};

	Node* top;
public:
	Stack() {
		this->top = nullptr;
	}

	void push(int value) {
		Node* newNode = new Node(value);
		newNode->next = this->top;
		this->top = newNode;
	}

	int pop() {
		if(this->top == nullptr) {
			return -1;
		}

		Node* prevTop = this->top;
		this->top = prevTop->next;
		int topValue = prevTop->value;
		delete(prevTop);
		return topValue;
	}

	bool isEmpty() {
		return this->top == nullptr;
	}

	void print() {
		if(isEmpty()) {
			cout << "empty stack";
		} else {
			Node* currentNode = this->top;
			while(currentNode != nullptr) {
				cout << currentNode->value << " ";
				currentNode = currentNode->next;
			}
		}
	}

	~Stack() {
		while(!isEmpty()) {
			pop();
		}
	}
};

int main() {
	Stack stack;

	

	return 0;
}