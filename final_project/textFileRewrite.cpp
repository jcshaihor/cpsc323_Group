// ================================================================================================
// Group Names: Jay Vang, Jesse Shaihor, Cristian Salinas
// Final Project
// Due Date: 9 May 2023
// Purpose: This program will read from the file finalp1.txt and tokenize it so that unwanted lines
// of code are taken out. It will then write out the new tokenized output written to finalp2.txt
// ================================================================================================

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

// Global strings for the reserved words
const string RESERVED1 = "program";
const string RESERVED2 = "var";
const string RESERVED3 = "begin";
const string RESERVED4 = "end.";
const string RESERVED5 = "integer";
const string RESERVED6 = "display";

// function prototypes
void calcToken(string token, ofstream& writeToken);
void writeText();



// === main =======================================================================================
// Purpose: Will open and read from the h5.txt file then write to the newh5.txt
// ================================================================================================

int main()
{
    ifstream tokenFile;
    ofstream writeToken;
    string tempToken;
    bool commentBool = false;
    int commentIndex = 0;

    // openning our targeted txt file
    tokenFile.open("finalp1.txt");
    writeToken.open("finalp2.txt");

    // loop for as long as we have not reached the end of file
    while (!tokenFile.eof())
    {
        // copy the string to a variable
        getline(tokenFile,tempToken);
        commentBool = false;

        // see if we are reading a comment in the string
        if (tempToken.find("//") != std::string::npos) 
        {
            // if the comment is at the start or back then skip the line
            if ((tempToken[0] == '/') || ((tempToken[tempToken.size() - 2]) == '/'))
            {
                commentBool = true;
            }
            // a comment within the string
            else
            {
                commentIndex = tempToken.find("//");
                tempToken = tempToken.erase(commentIndex);
            }
        }

        // call the function to write if it is not a comment line
        if (!commentBool)
        {
            calcToken(tempToken,writeToken);     //call calcToken to determine the next step
        }

    }

    //close the files we used
    tokenFile.close();
    writeToken.close();

    //function to output the txt file contents
    //writeText();

    return 0;
}

// === calcToken ==================================================================================
// Purpose: this function will determine what will do with the given string.
// ================================================================================================

void calcToken(string token, ofstream& writeToken)
{
    char reserveArr[10];
    bool quoteMark = true;
    unsigned char c;
    unsigned char prev;
    
    // loop through the string to break it into parts and write it to our txt file
    for(int i = 0; i < token.size(); ++i)
    {

        if (i == 0)
        {
            c = token[i];
        }
        else
        {
            if (c != ' ' || c == '\t' || c == '\n' ||
                            c == '\r' || c == '\f' || c == '\v')
            {
                prev = c;
            }
                c = token[i];
        }

            // when we read any of the syntax
            if ((c == ',' || c == ':' || c == '=' || c == '(' || c == ')'
                          || c == '*' || c == '+' || c == '-') && quoteMark)
            {
                if (prev == ',' || prev == ':' || prev == '=' || prev == '(' || prev == ')'
                                || prev == '*' || prev == '+' || prev == '-')
                {
                    writeToken << c << ' ';
                }
                else
                {
                    writeToken << ' ' << c << ' ';
                }
            }
            else if (c == ';')
            {
                if (prev == ',' || prev == ':' || prev == '=' || prev == '(' || prev == ')'
                                || prev == '*' || prev == '+' || prev == '-')
                {
                    writeToken << c << endl;
                }
                else
                {
                    writeToken << ' ' << c << endl;
                }
        }
        else if (c == ' ' || c == '\t' || c == '\n' ||
                             c == '\r' || c == '\f' || c == '\v')
        { 
            // do nothing
        }
        else if (c == '\"')
        {
            writeToken << c;
            quoteMark = (!quoteMark);
        }
        else 
        {
            if (c == 'm')
            {
                writeToken << c << ' ';
            }
            else if (c == 'r' && prev =='a')
            {
                writeToken << c << endl;
            }
            else if (c == 'n' && token[i-3] == 'e')
            {
                writeToken << c << endl;
            }
            else
            {
                writeToken << c;
            }
        }
  
    }
}