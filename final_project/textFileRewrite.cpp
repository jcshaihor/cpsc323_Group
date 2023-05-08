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

using namespace std;

// Global strings for the reserved words
const string RESERVED1 = "program";
const string RESERVED2 = "var";
const string RESERVED3 = "begin";
const string RESERVED4 = "end.";
const string RESERVED5 = "integer";
const string RESERVED6 = "display";

// function prototypes
void calcToken(string token);
void writeText();



// === main =======================================================================================
// Purpose: Will open and read from the h5.txt file then write to the newh5.txt
// ================================================================================================

int main()
{
    ifstream tokenFile;
    string tempToken;
    bool comment = false;

    // openning our targeted txt file
    tokenFile.open("finalp1.txt");

    // loop for as long as we have not reached the end of file
    while (!tokenFile.eof())
    {
        // copy the string to a variable
        tokenFile >> tempToken;

        cout << tempToken << endl;

        // see if we are reading a comment
        if (tempToken.find("//") != std::string::npos) 
        {
            comment = (!comment);
        }

        // call the function to write if it is not a comment
        if (!comment)
        {
            calcToken(tempToken);     //call calcToken to determine the next step
        }

    }

    //close the files we used
    tokenFile.close();

    //function to output the txt file contents
    //writeText();

    return 0;
}

// === calcToken ==================================================================================
// Purpose: this function will determine what will do with the given string.
// ================================================================================================

void calcToken(string token)
{
    ofstream writeToken;

    //openning our targeted txt file
    writeToken.open("finalp2.txt");

    if (token == RESERVED1 || token == RESERVED5 || token == RESERVED6)
    {
        writeToken << token;
    }
    else if (token == RESERVED2 || token == RESERVED3 || token == RESERVED4)
    {
        writeToken << token << endl;
    }  
    else 
    {
        // loop through the string to break it into parts and write it to our txt file
        for(int i = 0; i < token.size(); ++i)
        {
            // when we read any of the syntax we will write a space and itself followed by whitespace
            if (token[i] == ',' || token[i] == ':' || token[i] == '='
                                || token[i] == '(' || token[i] == ')'
                                || token[i] == '*' || token[i] == '+'
                                || token[i] == '-')
            {
                writeToken << ' ' << token[i] << ' ';
            }
            else if (token[i] == ';')
            {
                writeToken << ' ' << token[i] << endl;
            }
            else 
            {
                writeToken << token[i];
            }

        }
    }

    writeToken << ' ';


    // close the txt files we used
    writeToken.close();

}

// === writeText ==================================================================================
// Purpose: this function will print out the contents of the 2 text files h5 and newh5
// ================================================================================================
/*
void writeText()
{
    string temp;
    fstream file1;
    fstream file2;

    //openning txt file again to start at the top
    file1.open("finalp1.txt");
    file2.open("finalp2.txt");

    //write out its contents of h5.txt
    cout << "\nfinalp1.txt\n";
    while (!file1.eof())
    {
        getline(file1, temp);
        cout << temp << endl;
    }

    //write out its contents of newh5.txt
    cout << "\nfinalp2.txt\n";
    while (!file2.eof())
    {
        getline(file2, temp);
        cout << temp << endl;
    }

    //close the files we used
    file1.close();
    file2.close();
} */