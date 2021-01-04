// HW1 by Leah Luo

#include <iostream>
using namespace std;

class Node {
public:
	int value;
	Node* next;
	Node* previous;
	Node(int i) { value = i; next = previous = nullptr; }
	Node() { next = previous = nullptr; }
};

class DoublyLinkedList {
public:
	Node* head;
	Node* tail;
	DoublyLinkedList() { head = tail = nullptr; }
	void makeRandomList(int m, int n);
	void printForward();
	void printBackward();

	//inplement the following member functions:
	void group();
	void groupBo();
	/*
	Group all occurances of the same numbers together accourding to the order of appearance.
	For a list with values
	7 6 12 4 33 12 6 6 7 ,
	after grouping, it becomes
	7 7	6 6 6 12 12 4 33
	Note that in the original sequence, 7 appears before 6 before 12 before 4 before 33
	*/
};

void DoublyLinkedList::group() {
	// If the linked list has no node / only one node 
	if (!head || !head->next) return;
	Node* p1 = head; 

	// Loop through the linked list using two pointers: p1, p2
	while (p1) {
		Node* p2 = p1->next;
		// If p2->value equals p1->value, move to the next node and continue checking 
		if (p2 != nullptr && p2->value == p1->value) {
			p1 = p2; 
			continue;
		}

		// Traverse the list to find the node that has the same value of p1
		while (p2 != nullptr && p2->value != p1->value) {
			p2 = p2->next; 
		}

		// End of traversing. Move to the next node 
		if (p2 == nullptr) {
			p1 = p1->next; 
			continue;
		}
		// If we find the node that has the same value of p1
		else {
			// Case 1: p2 is the tail 
			if (p2 == tail) {
				tail = tail->previous;
				tail->next = nullptr;

				p2->next = p1->next;
				p1->next->previous = p2;
				p1->next = p2;
				p2->previous = p1;
			}
			// Case 2: p2 is a node in the middle of the linked list
			else {
				p2->previous->next = p2->next;
				p2->next->previous = p2->previous;

				p2->previous = p1;
				p2->next = p1->next;
				p1->next->previous = p2;
				p1->next = p2;
			}
			p1 = p1->next;
		}
	}
}


void DoublyLinkedList::makeRandomList(int m, int n) {

	for (int i = 0; i < m; i++) {
		Node* p1 = new Node(rand() % n);
		p1->previous = tail;
		if (tail) tail->next = p1;
		tail = p1;
		if (!head) head = p1;
	}
}

void DoublyLinkedList::printForward() {
	cout << endl;
	Node* p1 = head;
	while (p1) {
		cout << p1->value << " ";
		p1 = p1->next;
	}
}

void DoublyLinkedList::printBackward() {
	cout << endl;
	Node* p1 = tail;
	while (p1) {
		cout << p1->value << " ";
		p1 = p1->previous;
	}
}

int main() {
	DoublyLinkedList d1;
	d1.makeRandomList(50, 20);
	d1.printForward();
	d1.printBackward();
	
	d1.group();
	d1.printForward();
	d1.printBackward();

	getchar();
	getchar();
	return 0;
}