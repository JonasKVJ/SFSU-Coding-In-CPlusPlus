//  generalTree.cpp
//  Assignment 7
//  Name: Jonas Vinter-Jensen
//  SFSU ID: 912941515
//  Email: jonaskvj@mail.sfsu.edu
//  Compiler(s): Dev-C++ V5.4.2 and Xcode V7.0.1(7A1001)

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "GeneralTree.h"

using namespace std;

// A default constructor. This should explicitly set
// the start node to be NULL.
GeneralTree::GeneralTree()
{
    start = NULL;
}

// A copy constructor. This should also explicitly
// set the start node to be NULL, and then it should
// copy the contents of other into the current tree.
// this = other iff this=NULL
GeneralTree::GeneralTree(const GeneralTree& other)
{
    this->start = NULL;
    copyOther(other);
}

// A destructor. This should traverse the tree, freeing
// all nodes. Remember to free children before you
// free parents!
GeneralTree::~GeneralTree()
{
    clear();
}

// An assignment operator. This should behave like the
// example I gave in class. If other is not the same
// as the current tree, remove everything from the current
// tree and copy the contents of other into the current
// tree.
// assignment operator: this = other iff this != NULL
GeneralTree& GeneralTree::operator=(const GeneralTree& other)
{
    if(this != &other)
    {
        clear();
        copyOther(other);
    }
                  
    return *this;
}

// An insert method. This method is tricky. If the parent
// given is NULL and the start node of the current tree
// is not NULL, you should throw an exception called
// NoParentException that you define in the header
// file. MAKE SURE THAT NO MEMORY GETS LEAKED HERE!
// If you created a node already and you’re about to
// throw an exception, delete the node first!
//
// If the parent given is NULL and the start node
// of the current tree is also NULL, this is fine. You
// should just create a new node with the given value
// and make it the start node.
//
// If the parent given is not NULL, make a new node with
// the given value and add it to the parent node’s children.
// Return the node you just inserted.

//parent is updated every time a new value is inserted into Tree B
//in pre-order traversal pattern.
//start in insert(): root Node in Tree B.
//start in copyFrom(): traversal Node containing value
//insert(start, parent) is called: TreeB.insert(TreeA_Start, TreeB_parent) in main.
Node* GeneralTree::insert(char value, Node* parent)
{
	//cout << '\n' << "start is currently: " << start << '\n';
	
    //If no char value was received before function call
    if(value == '\0')
    {
    	throw NoValueException();
    }  
	//If start && parent are NULL, create a new start node in Tree B containing value
    if(parent == NULL && start == NULL)
    {
        Node* insNode = new Node();
        insNode->value = value;
        start = insNode;
        return insNode;
    }
    //If the parent given is NULL and the start node of the current tree
    //is not NULL, you should throw an exception called NoParentException
    else if(parent == NULL && start != NULL)
    {
        //If node was created, delete it here
        
        throw NoParentException();
    }
    //If start of Tree B was picked as the parent, make insNode the root node
    if(parent != NULL && start == NULL)
    {
        Node* insNode = new Node();
        insNode->value = value;
        start = insNode;
        return insNode;
    }

    //Parent: current parent Node to be inserted under
    if(parent != NULL && start != NULL)
    {
        //Node* current = start;
        
        //pre-order insertion of Tree A tree structure subset under parent if space is
        //available. 
        if(parent->left == NULL)
        {
            Node* insNode = new Node();
            insNode->value = value;
            parent->left = insNode;
            return insNode;
        }
        else if(parent->right == NULL)
        {
            Node* insNode = new Node();
            insNode->value = value;
            parent->right = insNode;
            return insNode;
        }
        else
        {
            //Parent may only have up to two children. This exception is only possible during
            //first insertion of the pre-order traversal stack.
            throw NoParentSpaceException();
        }
    }
    //Insert nodes in pre-order traversal order in such a way that
    //they retain their original data structure

    return parent;
}

// A method to print the tree. You should print it using the
// following syntax: for non-leaf nodes (nodes that have
// more than zero children), print an open parenthesis, then
// the node’s children, then a close parenthesis. For leaf
// nodes (nodes with zero children), just print the node’s
// character value. This should appear all on one line,
// with a newline at the end.
//
// If a tree looks like this:
//
//           .
//          / \
//         /   \
//        "c"   .
//             /|\
//            / | \
//           /  |  \
//          /   |   \
//         "x" "y"  "z"
//
// then it will be printed like this:
//
// (c(xyz))
//
// Notice that the character values of non-leaf nodes
// are ignored, so the periods never get printed.
// Main call: Tree_X.print()
void GeneralTree::print() const
{
    printFrom(start);
}

// Recursively copy into the current tree from another tree.
// The starting point for the other tree is start. The parent
// argument is the argument to be passed to a call to insert().
//
// In case of copy constructor:
//   - Format: Tree Parent = Tree Start, gt3 = gt
//   - Tree Parent is empty in this case
//   - The variable “start” corresponds to a node in the tree
//     you are copying FROM which is the root Node of a Tree that is not empty
//   - The variable “parent” corresponds to a node in the
//     tree you are copying TO and it is start, which is NULL in the case of
//     of a copy constructor call.
// Basically the same as in my example. Just make a call to
// copyFrom (see below - copyFrom looks different!).
void GeneralTree::copyOther(const GeneralTree& other)
{
        Node* thisStart = other.start;
        //The parent where other will be inserted at.
        Node* otherParent = start;
        copyFrom(thisStart, otherParent);
}

// Also same as the example. Make a call to clearFrom
// (again, see below).
void GeneralTree::clear()
{
    clearFrom(start);
}

// Recursively print a subtree whose root is the given start node.
// Use the notation described above for print().
void GeneralTree::printFrom(Node* start) const
{
    if (start == NULL)
    {
        return;
    }
    
    //If current node is does not have a left and right Node and it contains
    //a character value, then it is a leaf Node.
    //Iff it is a leaf Node, print its character value.
    if(start->left == NULL && start->right == NULL && start->value != '\0')
    {
        cout << start->value;
        return;
    }
    
    //pre-order traversal of Tree
    //If Node above was neither NULL nor a leaf Node, then it must be a Node which is not
    //a leaf node. Double check that current Node contains a value to confirm that it is not
    //a NULL node.
    if(start->value != '\0')
    {
        cout << "(";
    }
    printFrom(start->left);
    printFrom(start->right);
    
    if(start->value != '\0')
    {
        cout << ")";
    }
    
    return;
}

// Recursively copy into the current tree from another tree.
// The starting point for the other tree is start. The parent
// argument is the argument to be passed to a call to insert().
//
// Just to clarify:
//   - The variable “start” corresponds to a node in the tree
//     you are copying FROM.
//   - The variable “parent” corresponds to a node in the
//     tree you are copying TO.
void GeneralTree::copyFrom(Node* start, Node* parent)
{
    if (start == NULL)
    {
        return;
    }
    
    //Tree A: tree to be inserted from. Tree B: tree to be inserted to.
    //pre-order traversal insertion into Tree B. Only the subtree beneath start located in
    //Tree A will be copied into Tree B.
    
    //currentParent: the latest Node that was inserted into Tree B.
    Node* currentParent = insert(start->value, parent);
    copyFrom(start->left, currentParent);
    copyFrom(start->right, currentParent);
}

// Recursively delete all nodes in the tree. post-order traversal.
void GeneralTree::clearFrom(Node* start)
{
    if(start == NULL)
    {
        return;
    }
    
    clearFrom(start->left);
    clearFrom(start->right);
    delete start;
}
