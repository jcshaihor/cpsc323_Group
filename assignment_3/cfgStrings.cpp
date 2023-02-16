// ================================================================================================
// Group Names: Jay Vang, Jesse Shaihor, Cristian Salinas
// Homework 2
// Due Date: Feb 16,2023
// Purpose: This program will determine whether an input string is accepted or rejected by the 
// grammar.
// ================================================================================================

#include <iostream>
#include <cstring>

using namespace std;

//function prototypes
void readCFG(string expression);
string translation(char token, char match);

//global variables
const int MAX = 20; //max size of the user input

// === main =======================================================================================
// Purpose: will ask the user for the input string and call a function to trace the string.  
// ================================================================================================

int main()
{
    string input;
    string choice = "y";

    //loop until user says no
    while (choice[0] == 'y')
    {
        //get the input string
        cout << "Please enter a string with $ at the end: ";
        getline(cin, input);

        //call readCFG to trace the input string
        readCFG(input);

        //ask if your would like to continue
        cout << "\nWould you like to continue(y/n): ";
        getline(cin, choice);
        cout << endl;
    }
    return 0;

}



// === readCFG ====================================================================================
// Purpose: will try to trace the input string if possible and output if it is rejected or accepted
// to the user.
// ================================================================================================

void readCFG(string expression)
{
    int counter = 0;
    char cfgChange;     
    char trace[MAX] = "S";  //the trace array initialized with S
    string temp = "0";    //holds the change needed to be made to trace

    //loop for duration of the input size
    while (counter < expression.length())
    {
        //the char we want to match from the input string
        cfgChange = expression[counter];

        //a switch to decide what we will translate
        switch (trace[counter])
        {
            case 'S':
                temp = translation('S', cfgChange);
                break;
            case 'B':
                temp = translation('B', cfgChange);
                break;
            case 'C':
                temp = translation('C', cfgChange);
                break;
            case 'D':
                temp = translation('D', cfgChange);
                break;
        }
        
        //if temp is ever '0' then we will break out of the loop and let the user know it is rejected
        if (temp == "0")
        {
            cout << "***Input string is REJECTED by the grammar***\n";
            break;
        }

        //if we got a valid return then we will change the string to match
        trace[counter] = temp[0];
        trace[counter + 1] = temp[1];
        counter++;
    }

    //if valid is true then let the user know
    if (temp != "0")
    {
        cout << "***Input string is ACCEPTED by the grammar***\n";
    }

}



// === translation ================================================================================
// Purpose: this function will see if the varaible can be translated into the correct char and if 
// it is tracable. 
// ================================================================================================

string translation(char token, char match)
{
    string change;      //the translation for the trace to perform

    //enter this block if 'S' is the token
    if (token == 'S')
    {
        //the possible translations for 'S'
        switch (match)
        {
            case 'a':
                change = "aS";
                break;
            case 'b':
                change = "bB";
                break;
            case 'c':
                change = "cC";
                break;
            case '$':  
                change = "0";
                break;
            default:
                change = "0";
                break;
        }
    }

    //enter this block if 'B' is the token
    if (token == 'B')
    {
        //the possible translations for 'B'
        switch (match)
        {
            case 'a':
                change = "aC";
                break;
            case 'b':
                change = "bB";
                break;
            case 'c':
                change = "cD";
                break;
            case '$':
                change = "$";
                break;
            default:
                change = "0";
                break;
        }
    }

    //enter this block if 'C' is the token
    if (token == 'C')
    {
        //the possible translations for 'C'
        switch (match)
        {
            case 'a':
                change = "aS";
                break;
            case 'b':
                change = "bD";
                break;
            case 'c':
                change = "cD";
                break;
            case '$':
                change = "$";
                break;
            default:
                change = "0";
                break;
        }
    }

    //enter this block if 'D' is the token
    if (token == 'D')
    {
        //the possible translations for 'D'
        switch (match)
        {
            case 'a':
                change = "aB";
                break;
            case 'b':
                change = "bD";
                break;
            case 'c':
                change = "cC";
                break;
            case '$':
                change = "0";
                break;
            default:
                change = "0";
                break;
        }
    }
    //if change is ever "0" then it means the input was rejected
    return change;

}
