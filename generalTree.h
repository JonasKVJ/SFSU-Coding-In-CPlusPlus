//  generalTree.h
//  Assignment 7
//  Name: Jonas Vinter-Jensen
//  SFSU ID: 912941515
//  Email: jonaskvj@mail.sfsu.edu
//  Compiler(s): Dev-C++ V5.4.2 and Xcode V7.0.1(7A1001)

#ifndef GeneralTree_h
#define GeneralTree_h

#include <iostream>
#include <cstdlib>

struct Node
{
    Node* left;
    Node* right;
    char value;
    
    Node()
    {
        left = NULL;
        right = NULL;
    }
};

class GeneralTree
{
public:
    GeneralTree();

    GeneralTree(const GeneralTree& other);

    ~GeneralTree();

    GeneralTree& operator=(const GeneralTree& other);

    Node* insert(char value, Node* parent);

    void print() const;

    void copyOther(const GeneralTree& other);

    void clear();

    void printFrom(Node* start) const;

    void copyFrom(Node* start, Node* parent);

    void clearFrom(Node* start);

private:
    Node* start;
};

class NoParentSpaceException : public std::exception
{
public:
    const char *what() const throw()
    {
        return "Each parent may only have up to two children.";
    }
};

class NoParentException : public std::exception
{
public:
    const char *what() const throw()
    {
        return "Given parent was not found.";
    }
};

class NoValueException: public std::exception
{
public:
    const char *what() const throw()
    {
        return "No value received to insert.";
    }
};


#endif /* GeneralTree_h */
