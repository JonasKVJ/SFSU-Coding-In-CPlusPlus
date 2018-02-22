//  Account.cpp
//  Assignment 6 Question 2
//  Name: Jonas Vinter-Jensen
//  SFSU ID: 912941515
//  Email: jonaskvj@mail.sfsu.edu
//  Compiler(s): Dev-C++ V5.4.2 and Xcode V7.0.1(7A1001)


#include <stdio.h>
#include "Account.h"

Account::Account():balance(0)
{
    
}

Account::Account(double initialDeposit):balance( initialDeposit)
{
    
}

double Account::getBalance()
{
    
    return balance;
}

// returns new balance or -1 if error

double Account::deposit(double amount)
{
    
    if (amount > 0)
    {
        balance += amount;
    } //Negative ammounts cannot be deposited
    else if(amount < 0)
    {
        throw Exception_Negative_Deposit(); // code indicating error
    }
    
    //If amount == 0, return balance
    return this->getBalance();
}

// returns new balance or -1 if invalid amount

double Account::withdraw(double amount)
{
    if(amount > balance)
    {
        throw Exception_Overdraw();
    }
    else if(amount < 0)
    {
        throw Exception_Negative_Withdraw();
    }
    else if(amount <= balance)
    {
        balance -= amount;
    }
    
    return this->getBalance();
}


