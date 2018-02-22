//  graph.cpp
//  Assignment 8
//  Name: Jonas Vinter-Jensen
//  SFSU ID: 912941515
//  Email: jonaskvj@mail.sfsu.edu
//  Compiler(s): Dev-C++ V5.4.2 and Xcode V7.0.1(7A1001)

#include <cstdlib>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <deque>
#include <stdexcept>

#include "graph.h"

using namespace std;


template <typename T>
Node<T>::Node(const T& value)
{
    this->value = value;
}

template <typename T>
Graph<T>::Graph()
{
    
}

/*
 * Since we dynamically allocate each node,
 * we need the big 3!
 *
 * - destructor
 * - copy constructor
 * - assignment operator
 */
template <typename T>
Graph<T>::~Graph()
{
    clear();
}

template <typename T>
Graph<T>::Graph(const Graph<T>& other)
{
    copyOther(other);
}

template <typename T>
Graph<T>& Graph<T>::operator=(const Graph<T>& other)
{
    if (this != &other) {
        clear();
        copyOther(other);
    }
    return *this;
}


/*
 * Common graph operations.
 */
template <typename T>
Node<T>* Graph<T>::insert(const T& value)
{
    if (nodes.find(value) != nodes.end())
    {
        return NULL;
    }
    
    Node<T>* newNode = new Node<T>(value);
    nodes[value] = newNode;
    return newNode;
}

// Two versions of connect! One that takes
// node pointers, another that takes node
// values.
template <typename T>
void Graph<T>::connect(Node<T>* first, Node<T>* second)
{
    first->adjacents.insert(second);
    second->adjacents.insert(first);
}

template <typename T>
void Graph<T>::connect(const T& first, const T& second)
{
    if (nodes.find(first) == nodes.end() ||
        nodes.find(second) == nodes.end()) {
        throw NonExistentNodeException();
    }
    
    connect(nodes[first], nodes[second]);
}

template <typename T>
void Graph<T>::unmarkAll() {
    for (auto iter = nodes.begin();
         iter != nodes.end();
         iter++) {
        iter->second->marked = false;
    }
}

template <typename T>
void Graph<T>::print() {
    for (auto iter = nodes.begin();
         iter != nodes.end();
         iter++) {
        std::cout << iter->first << ": ";
        
        for (auto neighborsIter = iter->second->adjacents.begin();
             neighborsIter != iter->second->adjacents.end();
             neighborsIter++) {
            
            std::cout << (*neighborsIter)->value << " ";
        }
        std::cout << std::endl;
    }
}

template <typename T>
std::vector<Node<T>*> Graph<T>::shortestPath(const T& start, const T& end)
{
    // Make sure both nodes exist! If one doesn't, throw
    // the appropriate exception.
    try
    {
        if (start==NULL)
        {
            throw new NonExistentNodeException();
        }
        else if (end==NULL)
        {
            throw new NonExistentNodeException();
        }
    }
    catch(NonExistentNodeException& e)
    {
        cout << "NonExistentNodeException: " << e.what() << '\n';
        //Close the program while indicating failure
        EXIT_FAILURE;
    }
    // Ok, both nodes exist. Get the node pointers from
    // your unordered_map!
    
    
    // You will need some way to store partial paths.
    // I highly recommend representing a partial
    // path as a vector of node pointers, since this
    // is what you will ultimately be returning.
    
    
    // I would ALSO recommend using a deque to store
    // all your partial paths. (A deque is
    // shorthand for double-ended queue. It's part
    // of the STL.
    //
    // If you choose to use a deque (which you should),
    // you'll have a deque of vectors, where each vector
    // in turn contains node pointers. Kind of
    // complicated! But effective!
    
    
    // Don't forget to unmark your nodes!
    
    
    // Your first partial path will just contain one
    // node - the start node. Not much of a path, but
    // you have to start somewhere!
    
    
    // Now, repeatedly do the following:
    //    1. Get the topmost partial path.
    //    2. Look at every node you can get to from
    //       the end of that partial path (ignoring
    //       nodes you've already seen).
    //    3. Create a partial path that has the same
    //       nodes as the current partial path, PLUS
    //       one more node (the node that you're
    //       looking at).
    //    4. Store those partial paths at the end.
    //
    // You stop when:
    //    - You see the end node in step 2. Put the
    //      end node at the end of the current partial
    //      path, and then return the partial (now
    //      complete) path!
    //    - You run out of partial paths to look at.
    //      If this ever happens, that means there is
    //      no path to the end node. Throw the
    //      appropriate exception.
    
    
    // This method returns an empty vector for now.
    // Get rid of this line!
    return std::vector<Node<T>*>();
}

template <typename T>
void Graph<T>::copyOther(const Graph<T>& other)
{
    for (auto iter = other.nodes.begin();
         iter != other.nodes.end();
         iter++) {
        insert(iter->first);
    }
    
    for (auto iter = other.nodes.begin();
         iter != other.nodes.end();
         iter++) {
        auto adjacents = iter->second->adjacents;
        for (auto neighborsIter = adjacents.begin();
             neighborsIter != adjacents.end();
             ++neighborsIter) {
            // Need to connect the values here!
            // Connecting iter->second and *neighborsIter
            // would re-connect the nodes in the old graph
            // (so this would do nothing)
            connect(iter->first, (*neighborsIter)->value);
        }
    }
}

template <typename T>
void Graph<T>::clear()
{
    for (auto iter = nodes.begin();
         iter != nodes.end();
         iter++) {
        delete iter->second;
    }
    
    nodes.clear();
}

