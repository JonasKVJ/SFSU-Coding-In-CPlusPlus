//  main.cpp
//  Assignment 6 Question 1
//  Name: Jonas Vinter-Jensen
//  SFSU ID: 912941515
//  Email: jonaskvj@mail.sfsu.edu
//  Compiler(s): Dev-C++ V5.4.2 and Xcode V7.0.1(7A1001)

#include <cstdlib>
#include <iostream>

using namespace std;

class Exception_ID_Not_Found : public exception
{
public:
    const char *what() const throw()
    {
        return "Product ID was not found!";
    }
};

int getProductID(int ids[], string names[], int numProducts, string target)
{
    for (int i=0; i < numProducts; i++)
        
    {
        
        if (names[i] == target)
            
            return ids[i];
        
    }
    
    throw Exception_ID_Not_Found(); // not found
}



int main() // Sample code to test the getProductID function

{
    
    int productIds[]= {4, 5, 8, 10, 13};
    
    string products[] = { "computer", "flash drive", "mouse", "printer", "camera" };
    
    try
    {
        cout << getProductID(productIds, products, 5, "mouse") << endl;
        
        cout << getProductID(productIds, products, 5, "camera") << endl;
        
        cout << getProductID(productIds, products, 5, "laptop") << endl;
    } //Exception_ID_Not_Found& derived from exception, exception& could have been used instead
    catch (Exception_ID_Not_Found& e)
    {
        cout << "Exception_ID_Not_Found: " << e.what() << endl;
    } catch (...) {
        cout << "ERROR: Unrecognized exception." << endl;
    }
    
    return 0;
    
}
