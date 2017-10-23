#pragma once
//-----------------------------------------------------------------------------
// Author: Natnael Tezera
// created date: 4/10/2017
// Last modified data: 
//
//-----------------------------------------------------------------------------
// Purpose: This file specifies the functions for BinTree.cpp. It is writeen 
//			the assumption of 
//
//-----------------------------------------------------------------------------

#include <iostream>
#include "nodedata.h"
//#include <fstream>
#include <vector>


using namespace std;

class BinTree {	
	friend ostream& operator<<(ostream &output, const BinTree& b);

private:
	struct Node {
		NodeData* data;						// pointer to data object
		Node* left;							// left subtree pointer
		Node* right;						// right subtree pointer

	};
	Node* root;								// root of the tree

	// Helps to overload operator==
	friend bool operator== (Node const &lhs, Node const &rhs) {
		return lhs.data == rhs.data
			&& ((lhs.left == NULL && rhs.left == NULL)
				|| (lhs.left != NULL && rhs.left != NULL &&
					*lhs.left == *rhs.left))
			&& ((lhs.right == NULL && rhs.right == NULL)
				|| (lhs.right != NULL && rhs.right != NULL &&
					*lhs.right == *rhs.right));
	}

	// utility functions
	void copyTree(Node* &, Node*);						// copy helper
	void makeEmptyHelper(Node* &);						// makeEmpty helper
	void sideways(Node*, int) const;					// displaySideways helper
	bool insertHelper(Node* &, NodeData*);				// insertion helper
	int heightAssistTwo(Node *) const;					// getHeight helper 2
	void inorderHelper(ostream &, Node *) const;		// helps to print
	Node* arrayToBSTHelper(NodeData*[], int, int);		// arrayToBS helper
	Node* findNode(const NodeData &, Node*) const;		// find node
	int heightHelper(const NodeData&, Node*) const;		// getHeight Helper 1
	void bsTreeToArrayHelper(NodeData*[], int&, Node*);	// bSTreeToArray Helper
	//retrive helper
	bool retrieveHelper(Node*, const NodeData&, NodeData*&)const;
	int playHelper(Node* curr, int n) const;
	
	
	
	
	


public:
	BinTree();								// constructor
	BinTree(const BinTree &);				// copy constructor
	~BinTree();								// destructor, calls makeEmpty	
	bool isEmpty() const;					// true if tree is empty, otherwise false
	void makeEmpty();						// make the tree empty so isEmpty returns true
	BinTree& operator=(const BinTree &);	// Assignment operator
	bool operator==(const BinTree &) const; // equality operator
	bool operator!=(const BinTree &) const; // unequality operator
	bool insert(NodeData*);					//insert new NodeData in the binary tree
	bool retrieve(const NodeData &, NodeData *&) const;
	void displaySideways() const;			// provided below, displays the tree sideways
	int getHeight(const NodeData&) const;	// get height
	void bsTreeToArray(NodeData* []);		// changes from binary tree to array
	void arrayToBSTree(NodeData*[]);		// changes array to balanced tree
	void printInorder(ostream &) const;     // provides public interface for operator <<
	int play() const;
};


