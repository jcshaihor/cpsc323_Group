// ================================================================================================
// Group Names: Jay Vang, Jesse Shaihor
// Homework 2
// Due Date: Feb 16,2023
// Purpose: This program reads a list of tokens from a text file and will determine whether it is 
// a digit, identifier, or a reserved word
// ================================================================================================

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cctype>

using namespace std;

//function prototypes
void determineToken(string tokenRead);
void tokenDigit(string token);
void tokenId(string token);
void tokenReserved(string token);

//global array of strings for reserved words
string reserved[5] = {"while", "for", "switch", "do", "return"};



// === main =======================================================================================
// Purpose: main will prompt user for the txt file name and open the text file. It will then run 
// the functions get the tokens and determine their properties
// ================================================================================================

int main()
{
    ifstream tokenFile;
    string tempToken;

    //setting the format for the outputs
    cout << left << setw(10) << "Token";
    cout << left << setw(10) << "Number";
    cout << left << setw(10) << "Idenifier";
    cout << left << setw(10) << "Reserved Word\n";

    //open txt file to read from
    tokenFile.open("token.txt");

    //if txt file is open we will attempt to get a line from it
    if (tokenFile.is_open())
        {
        //as long as we get a line from text file we will determine what the string is
        while (getline(tokenFile, tempToken))
            {
                determineToken(tempToken);
            }
        }

    return 0;
}



// === determineToken =============================================================================
// Purpose: Receives a string from main and it will check the string by calling three different
// functions to see what it is. 
// ================================================================================================

void determineToken(string tokenRead)
{
    cout << left << setw(10) << tokenRead;

    //check each function for the token read from the text file
    tokenDigit(tokenRead);
    tokenId(tokenRead);
    tokenReserved(tokenRead);
}



// === tokenDigit =================================================================================
// Purpose: Receives a string from determineToken and will check to see if it a digit. 
// ================================================================================================

void tokenDigit(string token)
{
    int i = 0;
    int check = 1;

    while (i < token.length())
    {
        //if a non-digit is ever read check will become false
        check = isdigit(token[i]);
        ++i;
    }

    if (check)
    {
        cout << left << setw(10) << "yes";
    }
    else
    {
        cout << left << setw(10) << "no";

    }
}



// === tokenId ====================================================================================
// Purpose: Receives a string from determineToken and will check to see if it an identifier. 
// ================================================================================================

void tokenId(string token)
{
    int i = 0;
    int check = 1;

    if (isalpha(token[0]) || token[0] == '_')
    {
        //loop through the string and read each element
        while (i < token.length())
        {
            //if an digit,underscore, or alphabet is not read it is not an identifier
            if(isdigit(token[i]) || isalpha(token[i]) || token[i] == '_')
            {
                check = 1;
            }
            else
            {
                check = 0;
            }

            //if the check ever read false then we output not an identifier and exit the loop
            if (check == 0)
            {
                cout << left << setw(10) << "no";
                break;
            }
            i++;

        }
    }
    else
    {
        cout << left << setw(10) << "no";
    }

    if (check)
    {
        cout << left << setw(10) << "yes";
    }
}



// === tokenReserved ==============================================================================
// Purpose: Receives a string from determineToken and will check to see if it a reserved word. 
// ================================================================================================

void tokenReserved(string token)
{
    int check = 1;

    //compare token to the reserved words in a loop
    for(int i = 0; i < 5; i++)
    {
        //if token ever matches a reserved word check becomes false
        if (token == reserved[i])
        {
            check = 0;
        }
        //if check is ever false we will write it is a reserved word and exit the loop
        if (check == 0)
        {
            cout << left << setw(10) << "yes\n";
            break;
        }
    }

    //if the loop has finished and check is true we will write it is not a reserved word
    if (check)
    {
        cout << left << setw(10) << "no\n";
    }
}


