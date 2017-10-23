//-----------------------------------------------------------------------------
// Author: Natnael Tezera
// created date: 4/10/2017
// Last modified data: 4/21/2017
//
//-----------------------------------------------------------------------------
// Purpose: This file contains the implimentation for methods specified in 
//			bintree.h. It is a program2 assiggnment for CSS 343 on Spring 2017
// Assumption: the buildTree method in the driver class will be used to test 
//			the implimentations of this class
//-----------------------------------------------------------------------------

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include "bintree.h"
#include "nodedata.h"

//-----------------------------Overload Operator<<-----------------------------
// operator <<: prints out the values in the linked list inorder way
// precondtion: None
// postcondition: the values in the bnt are outputed
//-----------------------------------------------------------------------------
ostream& operator<<(ostream &output, const BinTree& bnt) {
	bnt.printInorder(output);
	return output;
}

//-----------------------------printInorder------------------------------------
// printInOrder: provides public access to inorderHelper in order to print the
//			elements in the tree
// precondtion: None
// postcondition: the values in the bnt are outputed
//-----------------------------------------------------------------------------
void BinTree::printInorder(ostream& output) const {
	inorderHelper(output, root);
}

//-----------------------------inorderHelper-----------------------------------
// inorderHelper: helps to output the binary tree
// precondtion: None
// postcondition: the values in the bnt are outputed
//-----------------------------------------------------------------------------
void BinTree::inorderHelper(ostream &output, Node *oRoot) const {
	if (oRoot != NULL) {
		inorderHelper(output, oRoot->left);
		output << " " <<*oRoot->data;
		inorderHelper(output, oRoot->right);
	}
}

//-----------------------------Default Constructor-----------------------------
// Constructs: creates an empty tree
//-----------------------------------------------------------------------------
BinTree::BinTree() {
	root = NULL;
}

//-----------------------------Copy Constructor--------------------------------
// Copy Constructs: creates a copy of b
//-----------------------------------------------------------------------------
BinTree::BinTree(const BinTree & b) {
	if (b.root == NULL) {	// check if original tree is empty
		root = NULL;
	}
	else {
		copyTree(root, b.root);
	}
}

//-----------------------------operator=---------------------------------------
// overload operator=: Assigns lhs to rhs
// Precondition: None
// Postcondition: a copy of binary tree is made
//-----------------------------------------------------------------------------
BinTree &BinTree::operator=(const BinTree & rhs) {
	if (this != &rhs) {			// Check for self assignment
		if (root != NULL) {
			makeEmpty();		// empty the left hand side
		}
		if (rhs.root == NULL) {
			root = NULL;
		}
		else {
			copyTree(root, rhs.root);	//  make a copy
		}
	 }
	return *this;
}

//-----------------------------operator==--------------------------------------
// overload operator==: checks if the two binary tree are equal
// Precondition: None
// Postcondition: a copy of binary tree is made
//-----------------------------------------------------------------------------
bool BinTree::operator==(const BinTree & otherTree) const {
	return (root == NULL && otherTree.root == NULL)
		|| (root != NULL && otherTree.root != NULL && *root == *otherTree.root);
}

//-----------------------------operator==--------------------------------------
// overload operator!=: returns true if the two binary tree are not equal
// Precondition: None
// Postcondition: returns true if the two binary tree are different
//-----------------------------------------------------------------------------
bool BinTree::operator!=(const BinTree & otherTree) const {
	if (*this == otherTree){
		return false;
	}
	else{
		return true;
	}
}


//-----------------------------copyTree()--------------------------------------
// copyTree: helps the copy constructor
// Precondition:
// Postcondition: a copy of binary tree is made
//-----------------------------------------------------------------------------

void BinTree::copyTree(Node* &oRoot, Node* other) {

	if (other == NULL) {
		oRoot = NULL;		// set the root to NULL
	}
	
	else {
		oRoot = new Node;
		oRoot->data = other->data;
		copyTree(oRoot->left, other->left);		// copy left of the tree
		copyTree(oRoot->right, other->right);	// copy right side of the tree
	}
	
}

//-----------------------------Destructor--------------------------------------
// Destructor: distroy the binary tree
//-----------------------------------------------------------------------------
BinTree::~BinTree() {
	makeEmpty();
}

//-----------------------------isEmpty()---------------------------------------
// isEmptry(): returns true if the tree is empty or falase otherwise
// Precondition: None
// Postcondition: the status of the binary tree is discovered
//-----------------------------------------------------------------------------
bool BinTree::isEmpty() const {
	if (root == NULL) {
		return true;
	}
	else {
		false;
	}
}

//-----------------------------makeEmpty()-------------------------------------
// makeEmptry(): make the binary tree empty
// Precondition: there is at least 1 element 
// Postcondition: make the binary tree empty
//-----------------------------------------------------------------------------
void BinTree::makeEmpty() {
	makeEmptyHelper(root);
}


//-----------------------------makeEmptyHelper()-------------------------------
// makeEmptyHelper(Node *root): Helps to make the tree empty
// Precondition: root is pointing to a binary tree
// Postcondition: the binary tree is emptyied
//-----------------------------------------------------------------------------
void BinTree::makeEmptyHelper(Node*&root) {
	if (root == NULL) {
		return;
	}
	else {
		// delete everything recursively
		makeEmptyHelper(root->left);
		makeEmptyHelper(root->right);
		
		// delete node if it is the leaf of the tree
		if (root->left == NULL && root->right == NULL) { 
			delete root;
			root = NULL;
		}	
	}
	delete root;
	root = NULL;
}

//-----------------------------insert()----------------------------------------
// insert: inserts a node in the binary tree
// Precondition: nd is a nodeData that contains 
// Postcondition: a node containing nd is inserted in the binary tree
//-----------------------------------------------------------------------------
bool BinTree::insert(NodeData* newData) {
		if(insertHelper(root, newData)){
			return true;
		}else{
			return false;
		}
}

//-----------------------------insertHelper()----------------------------------
// insertHelper(): Helps to insert a new node in the tree
// Precondition: None 
// Postcondition: a new node inseted in the binary search tree
//-----------------------------------------------------------------------------
bool BinTree::insertHelper(Node *&root, NodeData* newDataPtr) {
	if (root == NULL) {			// set if it is empty
		root = new Node;
		root->data = newDataPtr;
		root->left = NULL;
		root->right = NULL;
		return true;
	}
	else if (*newDataPtr < *root->data) {
		// insert on the left side of subtree 
		return insertHelper(root->left, newDataPtr);
	}
	else if(*newDataPtr > *root->data){	
		// insert on the right side of subtree
		return insertHelper(root->right, newDataPtr);
	}
	else{
		return false;
	}

}

//-----------------------------getHeight()-------------------------------------
// getHeight: returns the height of a node
// Precondition: None 
// Postcondition: the height of a node containing NodeData is returnse 
//-----------------------------------------------------------------------------
int BinTree::getHeight(const NodeData& key) const {
			return heightHelper(key, root);
		
}

//-----------------------------heightHelper()----------------------------------
// heightHelper: helps to get the height of node containing NodeData
// Precondition: None 
// Postcondition: the height of a node containing NodeData is returnse 
//-----------------------------------------------------------------------------
int BinTree::heightHelper(const NodeData& key, Node* oRoot) const{
	 Node* itemNode = findNode(key, oRoot);
	 return heightAssistTwo(itemNode);

}

//-----------------------------heightAssit()----------------------------------
// heightAssist: helps to get the height of node containing NodeData
// Precondition: None 
// Postcondition: the height of a node containing NodeData is returnse 
//-----------------------------------------------------------------------------
int BinTree::heightAssistTwo(Node *oRoot) const {
	int leftHeight = 0;
	int rightHeight = 0;
	int height = 0;

	if (oRoot == NULL) {
		return 0;
	}
	else
	{
		// count the left and right height of the tree
		leftHeight = heightAssistTwo(oRoot->left);
		rightHeight = heightAssistTwo(oRoot->right);
	}

	// compare the left and the right height and return the highest
	if (leftHeight > rightHeight) {
		height = 1 + leftHeight;
	}
	else {
		height = 1 + rightHeight;
	}
	return height;
}

//------------------------- retrieve()-----------------------------------------
// retrieve(): returns true if key is found and points to it by nodPtr
// precondition: there is a binary tree
// postcondition: the existance of the key is known and pointed by ndPtr
//-----------------------------------------------------------------------------
bool BinTree::retrieve(const NodeData& key, NodeData *& nodPtr) const {
	// retrive
	if (retrieveHelper(root, key, nodPtr)) {
		return true;
	}
	else {
		return false;
	}
}

//------------------------- retrieveHelper()-----------------------------------
// retrieve(): Helps the retrieve
// precondition: there is a binary tree
// postcondition: the data is retrieved in the binary tree
//-----------------------------------------------------------------------------
bool BinTree::retrieveHelper(Node* root, const NodeData& key, 
								NodeData*& itemPtr) const{
	if (root == NULL) {		// check if the tree is empty
		itemPtr = NULL;
		return false;
	}
	else if (key == *root->data) {	// check if key is equal to the root data
		itemPtr = root->data;		// assign the root data to item ptr
		return true;
	}
	else if (key < *root->data) {	// check left subtree
		return retrieveHelper(root->left, key, itemPtr);
	}
	else{							// check right subtree
		return retrieveHelper(root->right, key, itemPtr);
	}
}

//--------------------------bsTreeToArray--------------------------------------
// bsTreeToArray: stores the datas in the binary tree in to array using 
//				using inorder and make the binary tree empty
// precondition: the ndArrayPtr has enough storage
// postcondition: the data in the binary tree in the binary tree stored in the
//				ndArray
//-----------------------------------------------------------------------------
void BinTree::bsTreeToArray(NodeData *ndArrayPtr[]) {
	int index = 0;
	bsTreeToArrayHelper(ndArrayPtr, index, root);
	makeEmpty();		// destroy the tree
}

//--------------------------bsTreeToArrayHelper--------------------------------
// bsTreeToArrayHelper: does the recurssive work for bsTreeToArray
// precondition: index starts at 0, oRoot is not NULL
// postcondition: The recusrive work for bsTreeToArray has been done
//-----------------------------------------------------------------------------
void BinTree::bsTreeToArrayHelper(NodeData*ndArrayPtr[], int& index, Node* oRoot){

	if (oRoot != NULL) {
		// using preorder assign each values in the tree to the array
		bsTreeToArrayHelper(ndArrayPtr, index, oRoot->left);
		ndArrayPtr[index] = oRoot->data;
		index++;
		bsTreeToArrayHelper(ndArrayPtr, index, oRoot->right);
		
	}
}

//--------------------------arrayToBSTree--------------------------------------
// arrayToBST: builds a balanced search tree from a sorted array of ndArrayPtr
//			and set values in each index of ndArrayPtr to NULL
// precondition: ndArrayPtr is a sorted array
// postcondition: a balance array is built using the data in ndArrayPtr array
//-----------------------------------------------------------------------------
void BinTree::arrayToBSTree(NodeData *ndArrayPtr[]) {
		int counter = 0;

		// count the number of occupied places in the array
		while(*ndArrayPtr != NULL){
			counter++;
			ndArrayPtr++;
		}

		// Set count number to second counter
		int secondCounter = counter;

		// make the array pointer points to the beggining of the array
		while (secondCounter != 0) {
			ndArrayPtr--;
			secondCounter--;
		}
		// set the beginning and the end of the array
		int start = 0;
		int last = counter - 1;
		root = arrayToBSTHelper(ndArrayPtr, start, last);
		ndArrayPtr = NULL;
}
//--------------------------arrayToBSTreeHelper--------------------------------
// arrayToBSTreeHelper: Helps builds a balanced search tree from a sorted array 
//					of ndArrayPtr
// precondition: ndArrayPtr is a sorted array
// postcondition: a balance array is built using the data in ndArrayPtr array
//-----------------------------------------------------------------------------
BinTree::Node* BinTree::arrayToBSTHelper(NodeData*nd[] , int start, int last){
		if (start > last) {
			nd[start] = NULL;	// set the array at the start to NULL
			return NULL;
		}
			// build the balanced tree
			int mid = (start + last)/2;		// find the mid of the array
			Node* root = new Node;
				root->data = nd[mid];		// set the Nodedata at mid to root
				root->left = arrayToBSTHelper(nd, start, mid - 1);
				root->right = arrayToBSTHelper(nd, mid+ 1, last);
				return root;
}

//--------------------------displaySideways -----------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
//-----------------------------------------------------------------------------
void BinTree::displaySideways() const {
	sideways(root, 0);
}

//---------------------------- Sideways ---------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
//-----------------------------------------------------------------------------
void BinTree::sideways(Node* current, int level) const {
	if (current != NULL) {
		level++;
		sideways(current->right, level);

		//indent for readability, 4 spaces per depth level
		for (int i = level; i >= 0; i--) {
		cout << "    ";
	}

	cout << *current->data << endl;        // display information of object
	sideways(current->left, level);
	}
}

//--------------------------findNode-------------------------------------------
// findNode: retrurns a pointer to a node that contains key, i
// Preconditions: oRoot is a head of sub tree, key is a string defined by the 
//				convention in NodeData class
// Postconditions: a pointer to a node containing key is returned
//-----------------------------------------------------------------------------

BinTree::Node* BinTree::findNode(const NodeData & key, Node * oRoot)const{
	
	if (oRoot != NULL) {	// check the root
		if (*oRoot->data == key) {
			return oRoot;
		}
		else {
			if (key < *oRoot->data) {	// check the left side of subtree
				return findNode(key, oRoot->left);
			}
			else{
				return findNode(key, oRoot->right); // check the left side 
													// of subtree
			}
		}

	}
	else {
		return NULL;
	}
}

int BinTree::playHelper(Node* curr, int n) const {
	if (curr == NULL) {
		return n;
	}
	if (curr->right != NULL || curr->left != NULL) {
		return 1 + playHelper(curr->left, n + 2) + playHelper(curr->right, n + 1);
	}
	else {
		return 0;
	}
}

int BinTree::play() const {
	int n = 0;
	return playHelper(root, n);
}