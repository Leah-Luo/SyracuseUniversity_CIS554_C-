//HW2 by Leah Luo

#include <iostream>
using namespace std;
int m = 50;
class Node {
public:
	int value;
	Node* l_child;
	Node* r_child;
	Node() : l_child(nullptr), r_child(nullptr) {}
	Node(int i) :value(i), l_child(nullptr), r_child(nullptr) {}
};

class Tree { //an n-level full binary tree of 2^n - 1 nodes
public:
	Node* root;
	Tree() : root(nullptr) {}
	Node* makeTree(int n);
	void printTree1(Node* p); //in-order printing
	void printTree2(Node* p); //pre-order printing
	void printTree3(Node* p); //post-order printing
	//*************
	//Design and implement the following two member functions, Func1 and Func2, using recursion.
	//Loop structures (such for, while, etc) are not allowed.
	//You are also required to do in-place implementation.
	//That is, you are not allowed to copy values to external structures, and process and copy them back to the trees.

	//Function 1, Func1, which will re-structure the subtree rooted at a node pointed by a pointer such that
	//at every node,  value(l_child) >= value(r_child) >= value(parent).
	//Will draw example diagrams in class.

	//Function 2, Func2, which will re-structure the subtree rooted at a node pointed by a pointer such that
	//at every node, value(parent) <= value(l_child) and value(parent) <= value(r_child).
	//In addition, for every subtree, the largest value  is at the bottom right node of the subtree.
	//Will draw example diagrams in class.
	Node* Func1(Node*& p);
	Node* Func2(Node*& p);

};

Node*
Tree::Func1(Node*& p) {

	if (p == nullptr || (p->l_child == nullptr && p->r_child == nullptr)) return p;

	// Bottom-up subtree traversal
	p->l_child = Func1(p->l_child);
	p->r_child = Func1(p->r_child);

	// Process the current level 
	if (p->l_child != nullptr && p->r_child != nullptr) {
		Node* ll = p->l_child->l_child;
		Node* lr = p->l_child->r_child;
		Node* rl = p->r_child->l_child;
		Node* rr = p->r_child->r_child;

		// parent > left > right 
		if (p->value > p->l_child->value && p->l_child->value > p->r_child->value) {
			Node* newRoot = p->r_child;
			Node* right = p->l_child;
			Node* left = p;

			newRoot->l_child = left;
			newRoot->r_child = right;

			left->l_child = ll;
			left->r_child = lr;
			right->l_child = rl;
			right->r_child = rr;

			p = Func1(newRoot);
		}
		// parent > right >= left
		else if (p->value > p->r_child->value && p->r_child->value >= p->l_child->value) {
			Node* newRoot = p->l_child;
			Node* left = p;
			Node* right = p->r_child;

			newRoot->l_child = left;
			newRoot->r_child = right;

			left->l_child = ll;
			left->r_child = lr;
			right->l_child = rl;
			right->r_child = rr;

			p = Func1(newRoot);
		}
		// right > left >= parent 
		else if (p->r_child->value > p->l_child->value && p->l_child->value >= p->value) {
			Node* newRoot = p;
			Node* left = p->r_child;
			Node* right = p->l_child;

			newRoot->l_child = left;
			newRoot->r_child = right;

			left->l_child = ll;
			left->r_child = lr;
			right->l_child = rl;
			right->r_child = rr;

			p = Func1(newRoot);
		}
		// right >= parent > left
		else if (p->r_child->value >= p->value && p->value > p->l_child->value) {
			Node* newRoot = p->l_child;
			Node* left = p->r_child;
			Node* right = p;

			newRoot->l_child = left;
			newRoot->r_child = right;

			left->l_child = ll;
			left->r_child = lr;
			right->l_child = rl;
			right->r_child = rr;

			p = Func1(newRoot);
		}
		// left >= parent > right
		else if (p->l_child->value >= p->value && p->value > p->r_child->value) {
			Node* newRoot = p->r_child;
			Node* left = p->l_child;
			Node* right = p;

			newRoot->l_child = left;
			newRoot->r_child = right;

			left->l_child = ll;
			left->r_child = lr;
			right->l_child = rl;
			right->r_child = rr;

			p = Func1(newRoot);
		}
	}
	return p; 
}


Node* Tree::Func2(Node*& p) {
	if (p == nullptr || (p->l_child == nullptr && p->r_child == nullptr)) return p;

	// Bottom -> Up subtree traverse
	Node* leftNode = Func2(p->l_child);
	Node* rightNode = Func2(p->r_child);


	// Process current level
	if (p->value >= p->l_child->value && p->l_child->value > p->r_child->value) {    // root >= l > r
		int tmp = p->value;
		p->value = p->r_child->value;
		p->r_child->value = tmp;
		Func2(p);
	}
	else if (p->value >= p->r_child->value && p->r_child->value > p->l_child->value) {  // root >= r > l
		int tmp = p->value;
		p->value = p->l_child->value;
		p->l_child->value = p->r_child->value;
		p->r_child->value = tmp;
		Func2(p);

	}
	else if (p->value > p->l_child->value && p->l_child->value >= p->r_child->value) {  // root > l >= r
		int tmp = p->value;
		p->value = p->r_child->value;
		p->r_child->value = tmp;
		Func2(p);

	}
	else if (p->l_child->value > p->r_child->value && p->r_child->value > p->value) {  // l > r >= root
		int tmp = p->r_child->value;
		p->r_child->value = p->l_child->value;
		p->l_child->value = tmp;
		Func2(p);

	}
	else if (p->l_child->value > p->value && p->value > p->r_child->value) {  // l > root > r
		int tmp = p->value;
		p->value = p->r_child->value;
		p->r_child->value = p->l_child->value;
		p->l_child->value = tmp;
		Func2(p);

	}
	else if (p->r_child->value > p->value && p->value > p->l_child->value) {  // r > root > l
		int tmp = p->value;
		p->value = p->l_child->value;
		p->l_child->value = tmp;
		Func2(p);
	}

	// Process to rearrange right bottom nodes of current node
	if (leftNode->r_child != nullptr)
		leftNode = Func2(leftNode->r_child);

	if (rightNode->r_child != nullptr)
		rightNode = Func2(rightNode->r_child);


	if (leftNode->value > rightNode->value) {
		int tmp = leftNode->value;
		leftNode->value = rightNode->value;
		rightNode->value = tmp;
	}

	return p->r_child;
}



Node* Tree::makeTree(int n) { //Create an n-level full binary tree with 
							  //with random values between 0 ... m-1
							  //and returns a pointer to the root.

	Node* p = new Node(rand() % m);
	if (n == 1) return p;
	p->l_child = makeTree(n - 1);
	p->r_child = makeTree(n - 1);
	return p;
}
void Tree::printTree1(Node* p) { //in-order printing
	if (p == nullptr) return;
	printTree1(p->l_child);
	cout << p->value << " ";

	printTree1(p->r_child);
}
void Tree::printTree2(Node* p) { //pre-order printing

	if (p == nullptr) return;
	cout << p->value << " ";
	printTree2(p->l_child);
	printTree2(p->r_child);
}
void Tree::printTree3(Node* p) { //post-order printing
	if (p == nullptr) return;
	printTree3(p->l_child);
	printTree3(p->r_child);
	cout << p->value << " ";
}


int main() {
	Tree T1;
	T1.root = T1.makeTree(5);
	T1.printTree1(T1.root);
	cout << endl;
	T1.printTree2(T1.root);
	cout << endl;
	T1.printTree3(T1.root);
	cout << endl;
	T1.Func1(T1.root);
	T1.printTree1(T1.root);
	cout << endl;
	T1.printTree2(T1.root);
	cout << endl;
	T1.printTree3(T1.root);
	cout << endl;
	cout << endl;
	Tree T2;
	T2.root = T2.makeTree(5);
	T2.printTree1(T2.root);
	cout << endl;
	T2.printTree2(T2.root);
	cout << endl;
	T2.printTree3(T2.root);
	cout << endl;
	T2.Func2(T2.root);
	T2.printTree1(T2.root);
	cout << endl;
	T2.printTree2(T2.root);
	cout << endl;
	T2.printTree3(T2.root);
	cout << endl;

	return 0;
}