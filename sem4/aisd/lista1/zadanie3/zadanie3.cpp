#include <iostream>
#include <cstdlib>
using namespace std;

template <typename T>
class List {
private: 
	struct Node {
		T value;
		Node* previous;
		Node * next;

		Node(T value) {
			this->value = value;
			this->previous = nullptr;
			this->next = nullptr;
		}
	};

	int size;
	Node* node;
public: 
	List() {
		this->size = 0;
		this->node = nullptr;
	}

	Node* getNode() {
		return this->node;
	}

	int getSize() {
		return this->size;
	}

	void insert(T value) {
		Node* newNode = new Node(value);

		if(this->size == 0) {
			newNode->previous = newNode;
			newNode->next = newNode;
			this->node = newNode;
		} else {
			newNode->previous = this->node;
			newNode->next = this->node->next;
			this->node->next->previous = newNode;
			this->node->next = newNode;
		}

		this->size++;
	}

	void merge(List l) {
		Node* firstNode = l.getNode();
		Node* lastNode = firstNode->previous;

		if(this->size == 0) {
			this->node = firstNode;
		} else if (l.getSize() != 0) {
			this->node->next->previous = lastNode;
			lastNode->next = this->node->next;
			this->node->next = firstNode;
			firstNode->previous = this->node;
		}

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

	void printBackwards() {
		if(this->size == 0) {
			cout << "empty list";
		} else {
			for(int i = 0; i < this->size; i++) {
				cout << this->node->value << " ";
				this->node = this->node->previous;
			}
		}
		cout << endl;
	}

	pair<bool, int> find(T value) {
		pair<bool, int> p;
		p.first = false;
		p.second = 0;

		if(this->node == nullptr) {
			return p;
		}

		bool direction = rand() % 2;

		for(int i = 0; i < this->size; i++) {
			p.second++;
			if(this->node->value == value) {
				p.first = true;
				return p;
			}
			if(direction) {
				this->node = this->node->next;
			} else {
				this->node = this->node->previous;
			}
		}

		return p;
	}
};

template <typename T>
List<T> insert(List<T> l, int i) {
	l.insert(i);
	return l;
}

template <typename T>
List<T> merge(List<T> l1, List<T> l2) {
	l1.merge(l2);
	return l1;
}

int main() {
	srand(time(NULL));

	// punkt 1
	List<int> l1, l2;
	for(int i = 0; i < 10; i++) {
		l1 = insert(l1, rand() % 90 + 10);
		l2 = insert(l2, rand() % 90 + 10);
	}

	cout << "List 1: ";
	l1.print();
	cout << "List 1 backwards: ";
	l1.printBackwards();

	cout << "List 2: ";
	l2.print();
	cout << "List 2 backwards: ";
	l2.printBackwards();

	l1 = merge(l1, l2);
	cout << "Merged list: ";
	l1.print();
	cout << "Merged list backwards: ";
	l1.printBackwards();
	cout << endl;

	// punkt 2
	int t[10000];
	List<int> l;
	for(int i = 0; i < 10000; i++) {
		t[i] = rand() % 100000;
		l = insert(l, t[i]);
	}

	int sum1 = 0; // suma wartosci z tablicy
	int sum2 = 0; // suma losowych wartosci
	for(int i = 0; i < 1000; i++) {
		sum1 += l.find(t[rand() % 10000]).second;
		sum2 += l.find(rand() % 100000).second;
	}

	cout << "Average number of comparisons when searching values from list: " << 1. * sum1 / 1000 << endl;
	cout << "Average number of comparisons when searching values from range: " << 1. * sum2 / 1000 << endl;

	return 0;
}