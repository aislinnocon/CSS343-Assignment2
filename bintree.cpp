#include "bintree.h"

//----------------------------------------------------------------------------
// Default Constructor
// Default Construcor: ensures that root = nullptr
BinTree::BinTree()
{
    this->root = nullptr;   
}

//----------------------------------------------------------------------------
// Constructor(string str)
// Constructor(string str): inserts a node containing the passed in string value
BinTree::BinTree(string &str)
{
    NodeData* n = new NodeData(str);
    this->insert(n);
}

//----------------------------------------------------------------------------
// Copy Constructor
// Copy Constructor: sets the current object to the values of the other object
BinTree::BinTree(const BinTree &other)
{
    this->root = nullptr; 
    *this = other; 
}

//----------------------------------------------------------------------------
// Destructor
// Destructor: deletes entire binary search tree
BinTree::~BinTree() 
{
    this->makeEmpty(); 
}

//----------------------------------------------------------------------------
// isEmpty()
// isEmpty(): checks if binary search tree is empty
bool BinTree::isEmpty() const
{
    return root == nullptr; 
}

//----------------------------------------------------------------------------
// makeEmpty()
// makeEmpty(): deletes an entire binary search tree
void BinTree::makeEmpty()
{
    makeEmptyHelper(root);
    this->root = nullptr; 
}

//----------------------------------------------------------------------------
// makeEmptyHelper()
// makeEmptyHelper(): recursive helper to delete an entire binary search tree
void BinTree::makeEmptyHelper(BinTree::Node* n)
{
    if (n == nullptr)
    {
        return;
    }
    makeEmptyHelper(n->left);
    makeEmptyHelper(n->right);
    delete n; 
}

//----------------------------------------------------------------------------
// overloaded= 
// overloaded=: sets current object equal to other object
BinTree& BinTree::operator=(const BinTree &other)
{
    if (other == *this)
    { 
        return *this; 
    } 
    this->makeEmpty(); 
    this->root = copyHelper(other.root);
    return *this; 
}

//----------------------------------------------------------------------------
// copyHelper()
// copyHelper(): recursive helper to set the current object equal to the other 
// object
BinTree::Node *BinTree::copyHelper(Node* n)
{
    if (n == nullptr)
    {
        return nullptr; 
    }
    Node *temp = new Node(); 
    if (n != nullptr)
    {
        temp->data = n->data; 
        temp->left = copyHelper(n->left);
        temp->right = copyHelper(n->right);
    }
    return temp; 
}

//----------------------------------------------------------------------------
// overloaded== 
// overloaded==: checks if current object is the same as the other object
bool BinTree::operator==(const BinTree &other) const
{
    return equalHelper(this->root, other.root); 
}

//----------------------------------------------------------------------------
// equalHelper()
// equalHelper(): recursive helper to check if current object is the same as the 
// other object
bool BinTree::equalHelper(Node *lhs, Node *rhs) const
{
    if (lhs == nullptr && rhs == nullptr)
    {
        return true;
    }
    else if (lhs != nullptr && rhs != nullptr)
    {
        return (lhs->data == rhs->data && equalHelper(lhs->left, rhs->left) &&
            equalHelper(lhs->right, rhs->right)); 
    }
    return false; 
}

//----------------------------------------------------------------------------
// overloaded!= 
// overloaded!=: checks if current object is not the same as the other object
bool BinTree::operator!=(const BinTree &other) const
{
    return !(*this == other);
}

//----------------------------------------------------------------------------
// insert()
// insert(): adds a node containing specific data to the binary search tree
bool BinTree::insert(NodeData* info)
{
    if (this->contains(root, info))
    {
        return false;
    }
    if (root == nullptr)
    {
        root = new Node(); 
        root->data = info;
        root->left = nullptr;
        root->right = nullptr; 
        return true;
    }
    insertHelper(root, info);
    return true;

}

//----------------------------------------------------------------------------
// insertHelper()
// insertHelper(): recursive helper to add an node containing specific data to 
// the binary search tree
BinTree::Node* BinTree::insertHelper(Node* n, NodeData* info)
{   
    if (n == nullptr)
    {
        n = new Node(); 
        n->data = info;
        n->left = nullptr;
        n->right = nullptr; 

    }
    else if (*n->data > *info)  
    {
        n->left = insertHelper(n->left, info);
    }
    else //if (*n->data < *info)
    {
        n->right = insertHelper(n->right, info);
    }
    return n; 
}

//----------------------------------------------------------------------------
// contains()
// contains(): recursively checks if a value is within a binary search tree
bool BinTree::contains(Node* n, NodeData* info) const
{
    if (n == nullptr)
    {
        return false;
    }
    else if (*n->data == *info)
    {
        return true;
    }
    else if (*info < *n->data)
    {
        return contains(n->left, info);
    } 
    else if (*info > *n->data)
    {
        return contains(n->right, info);
    }  
    else
    {
        return false; 
    } 
}

//----------------------------------------------------------------------------
// retrieve()
// retrieve(): checks if value exists in a binary search tree and returns address
bool BinTree::retrieve(const NodeData &key, NodeData* &info) const
{
    return retrieveHelper(root, key, info); 
}

//----------------------------------------------------------------------------
// retrieveHelper()
// retrieveHelper(): recursive helper to check if value exists in a binary 
// search tree and returns address
bool BinTree::retrieveHelper(Node* n, const NodeData &key, NodeData* &info) const
{
    if (n == nullptr)
    {
        info = nullptr; 
        return false;
    }
    else if (*n->data == key)
    {
        info = n->data; 
        return true;
    }
    else if (key < *n->data)
    {
        return retrieveHelper(n->left, key, info);
    } 
    else if (key > *n->data)
    {
        return retrieveHelper(n->right, key, info);
    }  
    else
    {
        return false; 
    }
}

//----------------------------------------------------------------------------
// getHeight()
// getHeight(): finds the height of a node with a given value 
int BinTree::getHeight(const NodeData &info) const
{
    return heightHelper(root, info); 
}

//----------------------------------------------------------------------------
// heightHelper()
// heightHelper(): recursive helper for finding the height of a given node
int BinTree::heightHelper(Node *n, const NodeData &info) const
{
    if (n == nullptr)
    {
      return 0;  
    }
    else if (*n->data == info)
    {
        return getHeightHelper(n); 
    }
    else 
    {
        int left = heightHelper(n->left, info);
        int right = heightHelper(n->right, info);
        return max(left, right); 
    }
}

//----------------------------------------------------------------------------
// getHeightHelper()
// getHeightHelper(): recursive helper for returning the height of a given node
int BinTree::getHeightHelper(Node* n) const
{
    if (n == nullptr)
    {
        return 0;
    }
    else
    {
        return 1 + getHeightHelper(n->right) + getHeightHelper(n->left);
    }
}

//----------------------------------------------------------------------------
// bstreetoArray()
// bstreetoArray(): turns a bst into an array in inorder traversal
void BinTree::bstreeToArray(NodeData* arr[])
{   
    int index = 0;
    cout << "inorder traversal = " << *this << endl; 
    bstreetoArrayHelper(root, arr, index);
    this->makeEmpty(); 
    int i = 0; 
    // "and, eee, ff, iii, jj, m, not, ooo, pp, r, sssss, tttt, y, z"
    while (arr[i+1] != nullptr)
    {
        cout << " arr[" << i << "] = " << *arr[i];
        i++; 
    }
    cout << " arr[" << i << "] = " << *arr[i];
    cout << endl;
}

//----------------------------------------------------------------------------
// bstreetoArrayHelper()
// bstreetoArrayHelper(): recursively goes through bst and adds values to the arr[]
void BinTree::bstreetoArrayHelper(Node* n, NodeData* arr[], int index)
{ 
  
    if (n != nullptr)
    {
        
        while (arr[index] != nullptr)
        {
            index++; 
        }
        arr[index] = n->data;
        bstreetoArrayHelper(n->left, arr, index);
        bstreetoArrayHelper(n->right, arr, index);

    }
}

//----------------------------------------------------------------------------
// arraytoBSTree()
// arraytoBSTree(): converst an array into a BSTree
void BinTree::arrayToBSTree(NodeData* arr[])
{   
    int index = 0; 
    while (arr[index] != nullptr)
    {
        this->insert(arr[index]);
        index++; 
        arr[index-1] == nullptr; 
    }
}

//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::displaySideways() const {
	sideways(root, 0);
}

//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::sideways(Node* current, int level) const {
	if (current != NULL) {
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}

		cout << *current->data << endl;        // display information of object
		sideways(current->left, level);
	}
}

//----------------------------------------------------------------------------
// overloaded<<
// overloaded<<: prints out the binary search tree in inorder traversal
ostream& operator<<(ostream &output, const BinTree &bst) 
{
    if (bst.root == nullptr)
    {
        return output;
    }
    bst.inorderHelper(bst.root);
    output << endl;
    return output;  
}

//----------------------------------------------------------------------------
// inorderHelper()
// inorderHelper(): prints out the binary search tree in inorder traversal
void BinTree::inorderHelper(Node *n) const
{
    if (n == nullptr)
    {
        return;
    }
    if (n != nullptr && n->data != nullptr)
    {    
        inorderHelper(n->left); 
        cout << *n->data << " " ; 
        inorderHelper(n->right);
    }
} 


