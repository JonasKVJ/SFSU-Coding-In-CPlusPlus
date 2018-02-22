//  main.cpp
//  Assignment 6 Question 2
//  Name: Jonas Vinter-Jensen
//  SFSU ID: 912941515
//  Email: jonaskvj@mail.sfsu.edu
//  Compiler(s): Dev-C++ V5.4.2 and Xcode V7.0.1(7A1001)

#include <cstdlib>
#include <iostream>
#include "Account.h"

using namespace std;

int main(int argc, const char * argv[])
{
    double correctAmount = 4.0;
    double initialDeposit = 20.0;
    double overdrawAmount = 40.0;
    double negativeAmount = -40.0;
    
    Account myAccount(initialDeposit);
    cout << "Account Balance: " << myAccount.getBalance() << "$\n\n";
    
    //Test: negative withdrawal exception
    try
    {
        cout << "Withdrawing: " << negativeAmount << "$" << endl;
        myAccount.withdraw(negativeAmount);
    }
    catch(Exception_Negative_Withdraw& negWithException)
    {
        cout << "Negative Withdraw Exception: " << negWithException.what() << endl;
    }
    
    //Test: negative deposit exception
    try
    {
        cout << "Depositing: " << negativeAmount << "$" << endl;
        myAccount.deposit(negativeAmount);
    }
    catch (Exception_Negative_Deposit& e)
    {
        cout << "Negative Deposit Exception: " << e.what() << endl;
    }
    
    //Test: overdraw exception
    try
    {
        cout << "Withdrawing: " << overdrawAmount << "$" << endl;
        myAccount.withdraw(overdrawAmount);
    }
    catch (Exception_Overdraw& e)
    {
        cout << "Overdraw Exception: " << e.what() << endl;
    }
    
    //Test: acceptable scenarios
    try
    {
        cout << "Withdrawing: " << correctAmount << "$" << endl;
        cout << "New balance: " << myAccount.withdraw(correctAmount) << "$" << endl;
        cout << "Depositing: " << correctAmount << "$" << endl;
        cout << "New balance: " << myAccount.deposit(correctAmount) << "$" << endl;
    } catch (...) {
        cout << "Unexpected error. Closing program..." << endl;
        EXIT_FAILURE;
    }

    return 0;
}
