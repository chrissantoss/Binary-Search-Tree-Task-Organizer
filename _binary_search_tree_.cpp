#include <iostream>
#include "_binary_search_tree.hpp"
#include <algorithm>

using namespace std;

// PURPOSE: Default/empty constructor
BinarySearchTree::BinarySearchTree() : root(NULL), size(0) {
}

void BinarySearchTree::delete_nodes(BinarySearchTree::TaskItem* cur) {
	if (!cur) return;
	delete_nodes(cur->left);
	delete_nodes(cur->right);
	delete cur;
}
// PURPOSE: Explicit destructor of the class BinarySearchTree
BinarySearchTree::~BinarySearchTree() {
	delete_nodes(root);
	root = nullptr;
	size = 0;
}



// PURPOSE: Returns the number of nodes in the tree
unsigned int BinarySearchTree::get_size() const {

	return size;
}

// PURPOSE: Returns the maximum value of a node in the tree
BinarySearchTree::TaskItem BinarySearchTree::max() const {
	if (!root)
		return BinarySearchTree::TaskItem(-1, "N/A");

	else {
		TaskItem* cur = root;
		while (cur->right) {
			cur = cur->right;
		}
		return *cur;
	}
}

// PURPOSE: Returns the minimum value of a node in the tree
BinarySearchTree::TaskItem BinarySearchTree::min() const {
	if (!root)
		return BinarySearchTree::TaskItem(-1, "N/A");

	else {
		TaskItem* cur = root;
		while (cur->left) {
			cur = cur->left;
		}
		return *cur;
	}
}


int BinarySearchTree::height_helper(BinarySearchTree::TaskItem* cur)const {
	if (cur == NULL) return -1;

	else
		return 1 + std::max(height_helper(cur->left), height_helper(cur->right));

}
// PURPOSE: Returns the tree height
unsigned int BinarySearchTree::height() const {
	if (height_helper(root) <= 0)
		return 0;
	else
		return (height_helper(root));
}


void BinarySearchTree::print_helper(BinarySearchTree::TaskItem* node) const {
	cout << node->priority << endl << node->avlBalance << endl <<
		node->description << endl;

}

void BinarySearchTree::in_order_print(BinarySearchTree::TaskItem* cur) const { //inorder tree traversal
	if (cur == NULL) return;
	in_order_print(cur->left);
	print_helper(cur); //print or other processing
	in_order_print(cur->right);

}

// PURPOSE: Prints the contents of the tree; format not specified
void BinarySearchTree::print() const {

	in_order_print(root);
}

// PURPOSE: Returns true if a node with the value val exists in the tree	
// otherwise, returns false
bool BinarySearchTree::exists(BinarySearchTree::TaskItem val) const {
	TaskItem* cur = root;
	while (cur) {
		if (cur->priority == val.priority &&
			cur->description == val.description) {
			return true;
		}
		else if (cur->priority > val.priority) {
			cur = cur->left;
		}
		else {
			cur = cur->right;
		}

	}
	return false;

}

// PURPOSE: Optional helper function that returns a pointer to the root node
BinarySearchTree::TaskItem* BinarySearchTree::get_root_node() {
	return NULL;
}

// PURPOSE: Optional helper function that returns the root node pointer address
BinarySearchTree::TaskItem** BinarySearchTree::get_root_node_address() {
	return NULL;
}

int BinarySearchTree::balance_factor(BinarySearchTree::TaskItem* N) {
	if (N == NULL)
		return 0;
	return height_helper(N->left) - height_helper(N->right);
}

// PURPOSE: Optional helper function that gets the maximum depth for a given node
int BinarySearchTree::get_node_depth(BinarySearchTree::TaskItem* n) const {
	return 0;
}

// PURPOSE: Inserts the value val into the tree if it is unique
// returns true if successful; returns false if val already exists
bool BinarySearchTree::insert(BinarySearchTree::TaskItem val) {
	TaskItem* node = new TaskItem(val);

	TaskItem* cur = root;

	TaskItem* temp = NULL;

	while (cur != NULL) {
		temp = cur;
		if (val.priority < cur->priority)
			cur = cur->left;
		else
			cur = cur->right;
	}

	if (temp == NULL) {
		temp = node;
		root = temp;
	}

	else if (val.priority < temp->priority)
		temp->left = node;

	else
		temp->right = node;

	size++;
	return true;
}


BinarySearchTree::TaskItem* BinarySearchTree::min_value_from_node(TaskItem* n) {
	TaskItem* cur = n;
	while (cur && cur->left != NULL)
		cur = cur->left;

	return cur;
}

// PURPOSE: Removes the node with the value val from the tree
bool BinarySearchTree::remove(BinarySearchTree::TaskItem val) {
	TaskItem* cur = root;
	TaskItem* parent = NULL;
	if (exists(val) == false)
		return false;
	else if (root == NULL) {
		size = 0;
		return false;
	}

	else if (cur->right == NULL && cur->left == NULL) {
		root = NULL;
		size = 0;
		return true;
	}


	while (cur->priority != val.priority) {

		if (cur->priority > val.priority && cur->left != NULL) {
			parent = cur;
			cur = cur->left;
		}
		else if (cur->priority < val.priority && cur->right != NULL) {
			parent = cur;
			cur = cur->right;
		}
	}

	if (cur->right == NULL && cur->left == NULL) {

		delete cur;
		cur = NULL;
		if (parent->priority > val.priority) {
			parent->left = NULL;
		}
		else
			parent->right = NULL;
		size--;
		return true;

	}

	else if (cur->right == NULL || cur->left == NULL) {  //case 2	
		TaskItem* child = (cur->left) ? cur->left : cur->right;

		if (cur != root)
		{
			if (cur == parent->left)
				parent->left = child;
			else
				parent->right = child;
		}

		else {
			root = child;

		}
		delete(cur);
		return true;
	}

	
	else {
		TaskItem* parent = NULL;
		TaskItem* temp;

		temp = cur->right;
		while (temp->left != NULL) {
			parent = temp;
			temp = temp->left;
		}
	

		if (parent != NULL) {
			parent->left = temp->right;
		}

		else {
			cur->right = temp->right;

		}

		cur->priority = temp->priority;
		cur->description = temp->description;
		delete(temp);
		temp = NULL;

	}
	size--;
	return true;
}



void AVLTree::rotate_right(TaskItem* node) {

	TaskItem* p = node;

	TaskItem* parent = NULL;
	TaskItem* cur = root;

	while (cur->priority != node->priority) {

		if (cur->priority > node->priority && cur->left != NULL) {
			parent = cur;
			cur = cur->left;
		}
		else if (cur->priority < node->priority && cur->right != NULL) {
			parent = cur;
			cur = cur->right;
		}
	}


	p = cur;
	TaskItem* q = p->left;
	TaskItem* T2 = q->right;
	p->left = q->right;
	q->right = p;
	if (p != root && parent != NULL)
		parent->left = q;

}

void AVLTree::rotate_left(TaskItem* node) {


	TaskItem* p = node;

	TaskItem* parent = NULL;
	TaskItem* cur = root;

	while (cur->priority != node->priority) {

		if (cur->priority > node->priority && cur->left != NULL) {
			parent = cur;
			cur = cur->left;
		}
		else if (cur->priority < node->priority && cur->right != NULL) {
			parent = cur;
			cur = cur->right;
		}
	}


	p = cur;

	TaskItem* q = node->right;
	TaskItem* T2 = q->left;
	p->right = q->left;
	q->left = p;
	if (p != root && parent != NULL)
		parent->right = q;

}




bool AVLTree::is_balanced(TaskItem* node) {
	if (balance_factor(node) <= 1 || balance_factor(node) >= -1)
		return true;
	else
		return false;
}


// PURPOSE: Inserts the value into the tree while keeping the tree balanced
// returns true if successful; returns false if val already exists
bool AVLTree::insert(BinarySearchTree::TaskItem val) {
	BinarySearchTree::insert(val);
	if (is_balanced(root) == true)
		return true;

	int balance = balance_factor(root);
	if (balance > 1) { 
		if (balance_factor(root->left) < 0) { 
			rotate_left(root->left); 
			rotate_right(root);
		}
		else
			rotate_right(root);
	}
	else if (balance < -1) { 
		if (balance_factor(root->right) > 0) { 
			rotate_right(root->right);
			rotate_left(root);
		}
		else
			rotate_left(root);

	}
	return true;
}

	//if node has +2 check if left child node has +1 
	//if left child node is +1, single right
	//if sign is -, then do left-right rotation
	//if node has -2 and right child node has -1
	//if yes single left
	//if sign of child node is positive, double right left


/*
BINARY SEARCH TREE TESTING RESULTS
**********************************
Test1: New tree is valid
TEST PASSED
Test2: Test a tree with one node
TEST PASSED
Test3: Insert, remove, and size on linear list formation with three elements
TEST PASSED
Test4: Test removal of a node with one child
TEST PASSED
Test5: Insert multiple elements and remove till nothing remains
TEST PASSED
Test6: Test removal of root node when both children of root have two children
TEST PASSED
Test7: Test depth with many inserts and some removes
TEST PASSED
Test8: Lots of inserts and removes
TEST PASSED
Test9: Perform single AVL rotations
TEST PASSED
Test10: Perform double AVL rotations
TEST PASSED
*/
