#ifndef BinTree_H
#define BinTree_H

#include "nodedata.h"
#include <string>
#include <fstream> 
#include <iostream>
using namespace std;

//---------------------------------------------------------------------------
// BinTree class: Takes in data and create a sorted binary search tree (bst)
//   Additional Functions:
//   -- can turn bst into an array, and an array into a bst
//   -- retrieve the address to a specific node
//   -- print out tree in inorder traversal
//   -- get the height of a certain node
//   -- set bst equal to each other
//   -- see if two bsts are equal or not equal
// Implementation and assumptions:
//   -- reads in from a txt file where each line ends "$$"
//   -- array length will not exceed 100 values
//---------------------------------------------------------------------------


class BinTree {				// you add class/method comments and assumptions
    friend ostream& operator<<(ostream &, const BinTree &bst); // Inorder traversal
public:
	BinTree();		
    BinTree(string &str); 						// constructor
	BinTree(const BinTree &other);				// copy constructor
	~BinTree();								// destructor, calls makeEmpty	
	bool isEmpty() const;					// true if tree is empty, otherwise false
	void makeEmpty();						// make the tree empty so isEmpty returns true
 
	BinTree& operator=(const BinTree &other);		// sets current object equal to other object
	bool operator==(const BinTree &other) const;	// checks if current and other object are equal
	bool operator!=(const BinTree &other) const;	// checks if current and other object are not equal

	bool insert(NodeData*);											// true if node added, otherwise false
	bool retrieve(const NodeData &key, NodeData* &address) const;	// true if node found, otherwise false
    int getHeight(const NodeData &node) const;						// return the height of a node

    void bstreeToArray(NodeData* arr[]);			// converts current bst to an array		
    void arrayToBSTree(NodeData* arr[]); 			// converts array to a bst 

	void displaySideways() const;			// provided below, displays the tree sideways

private:
	struct Node {
		NodeData* data;						// pointer to data object
		Node* left;							// left subtree pointer
		Node* right;						// right subtree pointer
	};
	Node* root;								// root of the tree

	void makeEmptyHelper(Node* n);					// recursive helper for makeEmpty()	
    bool equalHelper(Node *lhs, Node *rhs) const;	// recursive helper for overloaded==
    Node *copyHelper(Node *n);						// recursive helper for overloaded=

				
    Node* insertHelper(Node* n, NodeData* info);	// recursive helper for insert()					
	bool retrieveHelper(Node* n, const NodeData &key, NodeData* &info) const;	// recursive helper for retrieve()
	bool contains(Node* data, NodeData* info) const;	// recursive helper for contains()
    
	int heightHelper(Node* n, const NodeData &info) const;	// recursive helper for getHeight() 
	int getHeightHelper(Node* n) const;						// recursive helper to add up height

	void bstreetoArrayHelper(Node* n, NodeData* arr[], int in); // recursive helper for bstreetoArray()

    // utility functions
    void inorderHelper(Node *n) const;			// prints bst in inorder traversal
    void sideways(Node*, int) const;			// provided below, helper for displaySideways()
};
#endif
