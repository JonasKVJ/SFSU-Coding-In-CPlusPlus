//  Homework3-Problem4
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

void displayRow(int digit, int y)
{
    if(digit==0)
    {
        if(y==0)             {cout << " @@@@@ ";}
        else if(y>=1 && y<=5){cout << "@@   @@";}
        else if(y==6)        {cout << " @@@@@ ";}
    }
    else if(digit==1)
    {
            if(y==1)        {cout << "  @@@  ";}
            else if(y==6)   {cout << " @@@@@@";}
            else            {cout << "   @@  ";}
    }
    else if(digit==2)
    {
        if(y==0 || y==6)        {cout << "@@@@@@@";}
        else if(y==1)           {cout << "@@   @@";}
        else if(y==2)           {cout << "    @@ ";}
        else if(y==3)           {cout << "   @@  ";}
        else if(y==4)           {cout << "  @@   ";}
        else if(y==5)           {cout << " @@    ";}
    }
    else if(digit==3)
    {
        if(y==0 || y==3 || y==6)             {cout << "@@@@@@@";}
        else if(y==1 || y==2 || y==4 || y==5){cout << "     @@";}
    }
    else if(digit==4)
    {
        if(y==0 || y ==1 || y==2)       {cout << "@@   @@";}
        else if(y==3)                   {cout << "@@@@@@@";}
        else if(y==4 || y==5 || y==6)   {cout << "     @@";}
    }
    else if(digit==5)
    {
        if(y==0 || y == 3 || y == 6)    {cout << "@@@@@@@";}
        else if(y==1)                   {cout << "@@     ";}
        else if(y==2)                   {cout << "@@     ";}
        else if(y==4)                   {cout << "     @@";}
        else if(y==5)                   {cout << "     @@";}
    }
    else if(digit==6)
    {
        if(y==0 || y==3 || y==6)        {cout << "@@@@@@@";}
        else if(y==1 || y==2)           {cout << "@@     ";}
        else if(y==4 || y==5)           {cout << "@@   @@";}

    }
    else if(digit==7)
    {
        if(y==0)     {cout << "@@@@@@@";}
        else if(y==1){cout << "     @@";}
        else if(y==2){cout << "    @@ ";}
        else if(y==3){cout << "   @@  ";}
        else if(y==4){cout << "  @@   ";}
        else if(y==5){cout << " @@    ";}
        else if(y==6){cout << "@@     ";}
    }
    else if(digit==8)
    {
        if(y==0 || y==3 || y==6)                {cout << "@@@@@@@";}
        else if(y==1 || y==2 || y==4 || y==5)   {cout << "@@   @@";}
    }
    else if(digit==9)
    {
        if(y==0 || y==3 || y==6)    {cout << "@@@@@@@";}
        else if(y==1 || y==2)       {cout << "@@   @@";}
        else if(y==4 || y==5)       {cout << "     @@";}
    }
    return;
}

void BigInt(int n)
{
    int loopCount=0;
    vector<int> digits;
    while(n)
    {
        digits.push_back(n%10);
        n /= 10;
    }
    reverse(digits.begin(), digits.end());
    
    if(n<0) {cout << "Only positive numbers allowed."; return;}
    else
    {
        for(int y=0; y<7; y++)
        {
            for (int i=0; i<digits.size(); i++)
            {
                loopCount++;
                displayRow(digits[i], y);
                cout << "  ";
            }
            cout << "\n";
        }
    }
    cout << "\nloopCount: " << loopCount << "\n";
    return;
}

int main(int argc, const char * argv[])
{
    BigInt(1234567890); //Prints a big integer version of the digit arguments
    return 0;
}
//Purpose of the loopcount: To reduce the amount of loop cycles needed to create an optimized program 
