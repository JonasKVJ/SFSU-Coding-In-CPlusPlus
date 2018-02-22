//  graph.h
//  Assignment 8
//  Name: Jonas Vinter-Jensen
//  SFSU ID: 912941515
//  Email: jonaskvj@mail.sfsu.edu
//  Compiler(s): Dev-C++ V5.4.2 and Xcode V7.0.1(7A1001)

#ifndef _GRAPH_H
#define _GRAPH_H

#include <cstdlib>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <deque>
#include <stdexcept>

/*
 * Exception for trying to find
 * a path between two nodes if
 * at least one of the nodes
 * doesn't exist.
 */
class NonExistentNodeException : public std::exception
{
public:
    virtual const char* what() const throw() {
        return "At least one of those nodes doesn't exist!";
    }
};

/*
 * Exception for trying to find
 * a path between two nodes when
 * no path exists.
 */
class NoPathException : public std::exception
{
public:
    virtual const char* what() const throw() {
        return "No path exists between those two nodes!";
    }
};

/*
 * Node
 * -----
 * Represents a node in a graph. T is
 * the type of value held in the node.
 */
template <typename T>
class Node
{
public:
    Node(const T& value);
    
    /*
     * Why wouldn't this do what we want?
     *
     * Hint: what is the new node connected to?
     */
    /*
     
     Node<T>* copy(const Node& other) {
     return new Node<T>(value);
     }
     
     */
    
    /*
     * Why not a vector for the list of adjacent
     * nodes?
     */
    std::unordered_set<Node<T>*> adjacents;
    T value;
    bool marked;
};

/*
 * Graph
 * -----
 * Represents a bi-directional (undirected)
 * graph. Nodes can have any value. The
 * graph does not have to be connected. Values
 * must be unique.
 */
template <typename T>
class Graph
{
public:
    Graph();
    
    /*
     * Since we dynamically allocate each node,
     * we need the big 3!
     *
     * - destructor
     * - copy constructor
     * - assignment operator
     */
    ~Graph();
    
    Graph(const Graph<T>& other);
    
    Graph<T>& operator=(const Graph<T>& other);
    
    /*
     * Common graph operations.
     */
    Node<T>* insert(const T& value);
    
    // Two versions of connect! One that takes
    // node pointers, another that takes node
    // values.
    void connect(Node<T>* first, Node<T>* second);
    
    void connect(const T& first, const T& second);
    
    void unmarkAll();
    
    void print();
    
    std::vector<Node<T>*> shortestPath(const T& start, const T& end);

    
    // Need to connect the values here!
    // Connecting iter->second and *neighborsIter
    // would re-connect the nodes in the old graph
    // (so this would do nothing)
    std::unordered_map<T, Node<T>*> nodes;  // for uniqueness and lookup
    
    void copyOther(const Graph<T>& other);
    
    void clear();
};

#endif

