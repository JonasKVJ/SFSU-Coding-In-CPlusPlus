//  main.cpp
//  Assignment 7
//  Name: Jonas Vinter-Jensen
//  SFSU ID: 912941515
//  Email: jonaskvj@mail.sfsu.edu
//  Compiler(s): Dev-C++ V5.4.2 and Xcode V7.0.1(7A1001)

#include "generalTree.h"
#include <sstream>

using namespace std;

void parseRecursive(stringstream& ss, GeneralTree& gt, Node* parent)
{
	char nextChar;
	while (true) {
		ss >> nextChar;
		if (ss.fail())
			return;

		if (nextChar == ')')
			return;

		if (nextChar == '(') {
			Node* newNode = gt.insert(' ', parent);
			parseRecursive(ss, gt, newNode);
		} else {
			gt.insert(nextChar, parent);
		}
	}
}

void parseExpression(const string& expr, GeneralTree& gt)
{
	stringstream ss;
	ss << expr;

	parseRecursive(ss, gt, NULL);
}

int main()
{
	// This should print:
	// (c(ab))
	GeneralTree gt;
    
    //insert(char value, Node* parent)
	Node* grandparent = gt.insert('.', NULL);

    Node* parent1 = gt.insert('c', grandparent);
    Node* parent2 = gt.insert('.', grandparent);
    Node* kid1 = gt.insert('a', parent2);
    Node* kid2 = gt.insert('b', parent2);

    cout << "---gt---" << '\n';
	gt.print();
    cout << '\n' << '\n';

	// This should print:
	// (abab(cd)d(ef(g(h))))
	GeneralTree gt2;
    
    try
    {
        parseExpression("(abab(cd)d(ef(g(h))))", gt2);
    }
    catch(NoParentSpaceException& npsException)
    {
        cout << "EXCEPTION: " << npsException.what() << '\n' << '\n';
    }

    cout << "---gt2---" << '\n';
	gt2.print();
    cout << '\n' << '\n';

	// This should print:
	// (c(ab))
	GeneralTree gt3 = gt;
    cout << "---gt3---" << '\n';
	gt3.print();
    cout << '\n' << '\n';

	// This should print:
	// (abab(cd)d(ef(g(h))))
	GeneralTree gt4(gt2);
    cout << "---gt4---" << '\n';
	gt4.print();
    cout << '\n' << '\n';

	return 0;
}

