//  Account.h
//  Account.h
//  Assignment 6 Question 2
//  Name: Jonas Vinter-Jensen
//  SFSU ID: 912941515
//  Email: jonaskvj@mail.sfsu.edu
//  Compiler(s): Dev-C++ V5.4.2 and Xcode V7.0.1(7A1001)

#ifndef Account_h
#define Account_h

#include <iostream>
#include <cstdlib>

class Account
{
private:
    double balance;
    
public:
    Account();
    
    Account(double initialDeposit);
    
    double getBalance();
    
    // returns new balance or -1 if error
    double deposit(double amount);
    
    // returns new balance or -1 if invalid amount
    double withdraw(double amount);
};

class Exception_Overdraw : public std::exception
{
public:
    const char *what() const throw()
    {
        return "Withdrawal of given amount will result in an overdraw.";
    }

};

//
class Exception_Negative_Deposit : public std::exception
{
public:
    const char *what() const throw()
    {
        return "Deposited amount has to be positive.";
    }
};

class Exception_Negative_Withdraw : public std::exception
{
public:
    const char *what() const throw()
    {
        return "Withdrawn amount has to be positive.";
    }
};


    
#endif /* Account_h */

