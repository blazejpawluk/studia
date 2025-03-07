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

	pair<bool, int> find(int value) {
		pair<bool, int> p;
		p.second = 0;
		for(int i = 0; i < this->size; i++) {
			p.second++;
			if(this->node->value == value) {
				p.first = true;
				return p;
			}
			this->node = this->node->next;
		}
		p.first = false;
		return p;
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
	// punkt 1
	List l1, l2;
	for(int i = 0; i < 10; i++) {
		l1 = insert(l1, rand() % 100 + 10);
		l2 = insert(l2, rand() % 100 + 10);
	}

	cout << "List 1: ";
	l1.print();

	cout << "List 2: ";
	l2.print();

	l1 = merge(l1, l2);
	cout << "Merged list: ";
	l1.print();
	cout << endl;

	// punkt 2
	int t[10000];
	List l;
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