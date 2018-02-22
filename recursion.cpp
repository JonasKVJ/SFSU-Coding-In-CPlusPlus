//  recursion.cpp
//  Assignment 9 Xcode
//  Name: Jonas Vinter-Jensen
//  SFSU ID: 912941515
//  Email: jonaskvj@mail.sfsu.edu
//  Compiler(s): Dev-C++ V5.4.2 and Xcode V7.1.1(7B1005)

#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

bool savedInitWTC = false;
bool isEven = false;
bool LLeftRightComplete = false;
bool LRCall = false;
bool LRightLeftComplete = false;
bool isSComplete = false;
bool RLCall = false;

int longStepAttempt = 2;
int result = 0;
int shortStepAttempt = 1;
int stepsToReplace = 0;
int initWTC = 0;

//string shortStepAttempt = "short";
//string longStepAttempt = "long";
vector<int> stepsTaken;
vector<vector<int>> stepSequences;

//Problem 1
string findReverseString(const string &start)
{
    
    //If the last letter position has been surpassed
    if (start.size()==0)
    {
        return start;
    }
    
    return findReverseString(start.substr(1)) + start.at(0);
}

//Problem 1
bool isPalindrome(string word)
{
    string reverseString;
    
    cout << "Is " << word << " a palindrome? ";
    
    reverseString = findReverseString(word);
    
    if (word == reverseString)
    {
        //clear and reallocate both
        reverseString = "";
        return true;
    }
    
    reverseString = "";
    return false;
}

//Problem 2
int digitSum(int input)
{
    //If there is no remainder left
    if(input == 0)
    {
        return result;
    }
    
    //Adds all digits from left to right with recursion
    result += input%10;
    
    //div(input, 10) removes rightmost digit from input by truncating
    return digitSum(input/10);
}



//Problem 3
int waysToClimb(int numStairs)
{
    if(savedInitWTC == false)
    {
        initWTC = numStairs;
        savedInitWTC = true;
    }
    
    //If numStairs is even after no steps have been taken
    if(numStairs%2==0 && stepsTaken.size() ==0)
    {
        isEven = true;
    }
    
    //Called after first waysToClimb() call as an all short-step combination, all-S combination
    if(numStairs==0 && stepsTaken.size() !=0)
    {
        //The staircase route containing all short steps is completed
        isSComplete = true;
        //A new way to climb the stairs was found.
        result += 1;
        stepsToReplace = result;
        //Save all the different stepSequences to memory - only works for somewhat small
        //staircases
        stepSequences.push_back(stepsTaken);
        
        return 0;
    }
    
    //Replaces all short steps with long steps from right to left. L-right-left replacement.
    if(isSComplete==true && LRightLeftComplete==false)
    {
        int rightLeftIndex = numStairs;
        int firstIndex = 0;
        int lastIndex = stepsTaken.size()-1;
        
        //If last index and second last index contain short steps, replace both with a long step
        if(isEven==true && (rightLeftIndex-2)==firstIndex && stepsTaken[rightLeftIndex-1]==1)
        {
            //Replace the last two short steps with a long step in stepsTalen
            LRightLeftComplete = true;
            stepsTaken[numStairs-2] = 2;
            int eraseIndex = numStairs-1;
            //Left-shifts previous lastindex by one
            stepsTaken.erase(stepsTaken.begin()+eraseIndex);
            stepSequences.push_back(stepsTaken);
            result +=1;
            return 0;
        }
        //if isEven, then last stepSequence will be one S followed by all L's
        if(isEven==false && stepsTaken[rightLeftIndex-1]==stepsTaken.front() && stepsTaken[rightLeftIndex]==2)
        {
            LRightLeftComplete = true;
            return 0;
        }
        
        if(stepsTaken[rightLeftIndex]==1)
        {
            if(stepsTaken[rightLeftIndex-1]==1)
            {
                stepsTaken[rightLeftIndex-1] = 2;
                int eraseIndex = rightLeftIndex;
                //Left-shifts previous lastindex by one
                stepsTaken.erase(stepsTaken.begin()+eraseIndex);
                //Add new step sequence, for example SSSL or SLL
                stepSequences.push_back(stepsTaken);
                result +=1;
                waysToClimb(numStairs-1);
            }
        }


    }
    
    //Replaces all short steps with long steps from right to left. L-left-right replacement.
    if(isSComplete==true && LRightLeftComplete==true && LRCall==true)
    {
        int lastIndex = stepsTaken.size()-1;
        int leftRightIndex = (stepsTaken.size()-1)-numStairs;
        
        //if isEven, then last stepSequence will be all L's. Skip this, because all L
        //combination was already completed at during L-right-left replacement.
        if(isEven==true && leftRightIndex+2==lastIndex && stepsTaken[leftRightIndex+1]==1)
        {
            LLeftRightComplete = true;
            return 0;
        }
        
        //if isEven, then last stepSequence will be all L's followed by one S
        if(isEven==false && stepsTaken[leftRightIndex+1]==stepsTaken.back() && stepsTaken[leftRightIndex]==2)
        {
            LLeftRightComplete = true;
            return 0;
        }

        if(stepsTaken[leftRightIndex]==1)
        {
            if(stepsTaken[leftRightIndex+1]==1)
            {
                stepsTaken[leftRightIndex+1] = 2;
                int eraseIndex = leftRightIndex;
                //Left-shifts previous lastindex by one
                stepsTaken.erase(stepsTaken.begin()+eraseIndex);
                //Add new step sequence, for example SSSL or SLL
                stepSequences.push_back(stepsTaken);
                result +=1;
                waysToClimb(numStairs-1);
            }

        }

    }
    
    if(isSComplete==false)
    {
        stepsTaken.push_back(shortStepAttempt);
        //All short step combination
        waysToClimb(numStairs-shortStepAttempt);
    }
 
    //Right-left replacement recursive first call
    if(isSComplete==true && LRightLeftComplete==false && RLCall==false)
    {
        RLCall = true;
        
        //After all short step is completed, replace each "short" step in stepsTaken with on
        //"left"
        //entry for each recursive function call. Example: S="Short step". L="Long step".
        //StepsTaken start: SSSSSSS. StepsTaken after Recursive Call 1 (top of stack): SSSSSL
        //Call 2: SSSLL, Call 3: SLLL. Save each combination in stepSequences.
        //L-right-left
        if(numStairs!=initWTC)
        {
            numStairs = initWTC;
        }
        
        waysToClimb(numStairs-1);
    }
    
    //Left-right replacement recursive first call
    if(isSComplete==true && LRightLeftComplete==true && LLeftRightComplete==false && LRCall==false)
    {
        LRCall = true;
        
        //Step 1:
            //Reset to all S again in stepsTaken
            //Reset all entries to S, the first stepSequence taken
            stepsTaken=stepSequences[0];
        //Step 2:
            //Replace each entry with L from left to right
            //L-right-left
        if(numStairs!=initWTC)
        {
            numStairs = initWTC;
        }
        
        waysToClimb(numStairs-1);
    }
    
    //Result only matters for the function call at the bottom of stack after the top
    //of stack has finished executing
    if(isSComplete==true && LRightLeftComplete==true && LLeftRightComplete==true)
    {
        return result;
    }
    else
    {
        return 0;
    }
}

int main(int argc, const char * argv[])
{
    //Problem 1
    cout << "--Problem 1--\n";
    string palindromeWord = "civic";
    string notPalindromeWord = "car";
    
    if(isPalindrome(palindromeWord)==1)
    {
        cout << "True" << endl;
    }
    else
    {
        cout << "False" << endl;
    }
    
    if(isPalindrome(notPalindromeWord)==1)
    {
        cout << "True" << endl;
    }
    else
    {
        cout << "False" << endl;
    }
    
    //Problem 2
    int test = 3405;
    cout << "\n--Problem 2--\n";
    cout << "digitSum(" << test << ") = " << digitSum(test) << endl;
    
     
    //Problem 3
    int scLen = 3;
    int WTC = waysToClimb(scLen);
    cout << "\n--Problem 3--\n";
    cout << "Ways to climb for staircase length " << scLen << ": " << WTC << endl;
    scLen = 4;
    WTC = waysToClimb(scLen);
    cout << "Ways to climb for staircase length " << scLen << ": " << WTC << endl;
    
    return 0;
}
