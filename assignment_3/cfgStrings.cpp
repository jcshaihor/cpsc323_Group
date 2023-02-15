// ================================================================================================
// Group Names: Jay Vang, Jesse Shaihor
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

// === main =======================================================================================
// Purpose: will ask the user for the input string and call a function to trace the string.  
// ================================================================================================

int main()
{
    string input;
    string choice = "y";

    while (choice[0] == 'y')
    {
        cout << "Please enter a string with $ at the end: ";
        getline(cin, input);
        readCFG(input);
        cout << "Would you like to continue(y/n): ";
        getline(cin, choice);
    }
    return 0;

}



// === readCFG ====================================================================================
// Purpose: will try to trace the input string if possible and output if it is rejected or accepted
// to the user.
// ================================================================================================

void readCFG(string expression)
{

}