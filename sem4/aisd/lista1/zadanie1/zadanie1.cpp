#include <iostream>
#include <cstdlib>
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
		int value = firstNode->value;
		delete(firstNode);
		this->size--;

		if(this->size == 0) {
			this->end = nullptr;
		}
		return value;
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
	int testCount = 50;

	// queue
	Queue queue;
	cout << "queue test:" << endl;
	
	cout << "\tadding values to queue" << endl;
	for(int i = 0; i < testCount; i++) {
		int randomValue = rand() % 100 + 1;
		cout << "\t\tadding " << randomValue << " to queue" << endl;
		queue.add(randomValue);
	}

	cout << "printing whole queue: ";
	queue.print();
	cout << endl;

	cout << "\tremoving values from queue" << endl;
	for(int i = 0; i < testCount + 1; i++) {
		int droppedValue = queue.drop();
		if(droppedValue > -1) {
			cout << "\t\tremoved " << droppedValue << " from queue" << endl;
		} else {
			cout << "\t\tqueue is empty" << endl;
		}
	}

	// stack
	Stack stack;
	cout << endl << "stack test:" << endl;

	cout << "\tadding values to stack" << endl;
	for(int i = 0; i < testCount; i++) {
		int randomValue = rand() % 100 + 1;
		cout << "\t\tadding " << randomValue << " to stack" << endl;
		stack.push(randomValue);
	}

	cout << "printing whole stack: ";
	stack.print();
	cout << endl;

	cout << "\tremoving values from stack" << endl;
	for(int i = 0; i < testCount + 1; i++) {
		int poppedValue = stack.pop();
		if(poppedValue > -1) {
			cout << "\t\tremoved " << poppedValue << " from stack" << endl;
		} else {
			cout << "\t\tstack is empty" << endl;
		}
	}

	return 0;
}