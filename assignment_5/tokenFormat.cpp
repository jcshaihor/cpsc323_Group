// ================================================================================================
// Group Names: Jay Vang, Jesse Shaihor, Cristian Salinas
// Homework 2
// Due Date: Mar 2,2023
// Purpose: This program will read from the file h5.txt and tokenize it so that unwanted lines of 
// of code are taken out. It will then write out the new tokenized output written to newh5.txt
// ================================================================================================

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

//function prototypes
int calcToken(string token);
void writeText();



// === main =======================================================================================
// Purpose: Will open and read from the h5.txt file then write to the newh5.txt
// ================================================================================================

int main()
{
    ifstream tokenFile;
    ofstream writeToken;
    string tempToken;
    bool comment = true;
    int outputToken;

    //openning our targeted txt file
    tokenFile.open("h5.txt");
    writeToken.open("newh5.txt");

    //loop for as long as we have not reached the end of file
    while (!tokenFile.eof())
    {
        //copy the string to a variable
        tokenFile >> tempToken;
        outputToken = calcToken(tempToken);     //call calcToken to determine the next step

        switch (outputToken)
        {
            case 1: //if it is the word begin
                writeToken << "\nbegin\n\t";
                break;
            case 2: //if it is the word var
                writeToken << "var\n\t";
                break;
            case 3: //if it is the word end.
                writeToken << "\nend.\n";
                break;
            case 4: //if it is a comment ignore until we find the end of comment
                comment = (!comment);
                break;
            case 5: //if it is a semi-colon 
                writeToken << ";\n\t";
                break;
            case 6: //if anything else just write it with spaces
                if (comment)
                {
                    writeToken << tempToken << ' ';                    
                }
                break;
        }
    }

    //close the files we used
    tokenFile.close();
    writeToken.close();

    //function to output the txt file contents
    writeText();

    return 0;
}

// === calcToken ==================================================================================
// Purpose: this function will determine what will do with the given string.
// ================================================================================================

int calcToken(string token)
{
    int answer;
    string reserved1 = "begin";
    string reserved2 = "var";
    string reserved3 = "end.";

    if (token == reserved1)
    {
        answer = 1;
    }
    else if (token == reserved2)
    {
        answer = 2;
    }
    else if (token == reserved3)
    {
        answer = 3;
    }
    else if (token == "**")
    {
        answer = 4;
    }
    else if (token == ";")
    {
        answer = 5;
    }
    else
    {
        answer = 6;
    }

    return answer;
}

// === writeText ==================================================================================
// Purpose: this function will print out the contents of the 2 text files h5 and newh5
// ================================================================================================

void writeText()
{
    string temp;
    fstream file1;
    fstream file2;

    //openning txt file again to start at the top
    file1.open("h5.txt");
    file2.open("newh5.txt");

    //write out its contents of h5.txt
    cout << "h5.txt\n";
    while (!file1.eof())
    {
        getline(file1, temp);
        cout << temp << endl;
    }

    //write out its contents of newh5.txt
    cout << "\nnewh5.txt\n";
    while (!file2.eof())
    {
        getline(file2, temp);
        cout << temp << endl;
    }

    //close the files we used
    file1.close();
    file2.close();
}