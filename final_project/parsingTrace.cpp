// ================================================================================================
// Group Names: Jay Vang, Jesse Shaihor, Cristian Salinas
// Final Project
// Due Date: 9 May 2023
// Purpose: Given the following CFG and the Predictive Parsing table. Read a txt file and determine
// whether or not the file is properly written based on our Predictive Parsing table.
// ================================================================================================

#include <iostream>
#include <fstream>
#include <stack>
#include <map>
#include <string>
#include <vector>

using namespace std;

// function prototypes
void errorCheck(int errorCode);

// reserved words
const string RESERVED1 = "program";
const string RESERVED2 = "var";
const string RESERVED3 = "begin";
const string RESERVED4 = "end.";
const string RESERVED5 = "integer";
const string RESERVED6 = "display";

// Define the grammar productions as strings
const string PProduction = "program I; var B begin G end.";
const string IProduction = "LX";
const string XProduction = "MX";
const string MProductionDigit = "D";
const string MProductionLetter = "L";
const string BProduction = "C:Z;";
const string CProduction = "IJ";
const string JProduction = ",C";
const string ZProduction = "integer";
const string GProduction = "SK";
const string KProduction = "G";
const string SProductionAssign = "A";
const string SProductionWrite = "W";
const string WProduction = "display O";
const string OProduction = "(H";
const string HProductionInteger = "I);";
const string HProductionValue = "\"value=\", I);";
const string AProduction = "I=E;";
const string EProduction = "TQ";
const string QProductionPlus = "+TQ";
const string QProductionMinus = "-TQ";
const string TProduction = "FR";
const string RProductionMulti = "*FR";
const string RProductionDiv = "/FR";
const string FProductionNum = "N";
const string FProductionInt = "I";
const string FProductionE = "(E)";
const string NProduction = "VDY";
const string YProduction = "DY";
const string VProductionPos = "+";
const string VProductionNeg = "-";
const string DProductionZero = "0";
const string DProductionOne = "1";
const string DProductionTwo = "2";
const string DProductionThree = "3";
const string DProductionFour = "4";
const string DProductionFive = "5";
const string DProductionSix = "6";
const string DProductionSeven = "7";
const string DProductionEight = "8";
const string DProductionNine = "9";
const string LProductionP = "p";
const string LProductionQ = "q";
const string LProductionR = "r";
const string LProductionS = "s";
const string Lambda = "lambda";

// Define a table to represent the predictive parsing table
map<pair<char, char>, string> table = 
{
    {{'P', 'p'}, PProduction},
    {{'I', 'p'}, IProduction},
    {{'I', 'q'}, IProduction},
    {{'I', 'r'}, IProduction},
    {{'I', 's'}, IProduction},
    {{'X', '0'}, XProduction},
    {{'X', '1'}, XProduction},
    {{'X', '2'}, XProduction},
    {{'X', '3'}, XProduction},
    {{'X', '4'}, XProduction},
    {{'X', '5'}, XProduction},
    {{'X', '6'}, XProduction},
    {{'X', '7'}, XProduction},
    {{'X', '8'}, XProduction},
    {{'X', '9'}, XProduction},
    {{'X', 'p'}, XProduction},
    {{'X', 'q'}, XProduction},
    {{'X', 'r'}, XProduction},
    {{'X', 's'}, XProduction},
    {{'X', ')'}, Lambda},
    {{'X', '='}, Lambda},
    {{'X', '*'}, Lambda},
    {{'X', '/'}, Lambda},
    {{'X', '+'}, Lambda},
    {{'X', '-'}, Lambda},
    {{'X', ';'}, Lambda},
    {{'X', ':'}, Lambda},
    {{'X', ','}, Lambda},
    {{'M', '0'}, MProductionDigit},
    {{'M', '1'}, MProductionDigit},
    {{'M', '2'}, MProductionDigit},
    {{'M', '3'}, MProductionDigit},
    {{'M', '4'}, MProductionDigit},
    {{'M', '5'}, MProductionDigit},
    {{'M', '6'}, MProductionDigit},
    {{'M', '7'}, MProductionDigit},
    {{'M', '8'}, MProductionDigit},
    {{'M', '9'}, MProductionDigit},
    {{'M', 'p'}, MProductionLetter},
    {{'M', 'q'}, MProductionLetter},
    {{'M', 'r'}, MProductionLetter},
    {{'M', 's'}, MProductionLetter},
    {{'B', 'p'}, BProduction},
    {{'B', 'q'}, BProduction},
    {{'B', 'r'}, BProduction},
    {{'B', 's'}, BProduction},
    {{'C', 'p'}, CProduction},
    {{'C', 'q'}, CProduction},
    {{'C', 'r'}, CProduction},
    {{'C', 's'}, CProduction},
    {{'J', ','}, JProduction},
    {{'J', ':'}, Lambda},
    {{'Z', 'i'}, ZProduction},
    {{'G', 'p'}, GProduction},
    {{'G', 'q'}, GProduction},
    {{'G', 'r'}, GProduction},
    {{'G', 's'}, GProduction},
    {{'G', 'd'}, GProduction},
    {{'K', 'p'}, KProduction},
    {{'K', 'q'}, KProduction},
    {{'K', 'r'}, KProduction},
    {{'K', 's'}, KProduction},
    {{'K', 'd'}, KProduction},
    {{'K', 'e'}, Lambda},
    {{'S', 'p'}, SProductionAssign},
    {{'S', 'q'}, SProductionAssign},
    {{'S', 'r'}, SProductionAssign},
    {{'S', 's'}, SProductionAssign},
    {{'S', 'd'}, SProductionWrite},
    {{'W', 'd'}, WProduction},
    {{'O', '('}, OProduction},
    {{'H', 'p'}, HProductionInteger},
    {{'H', 'q'}, HProductionInteger},
    {{'H', 'r'}, HProductionInteger},
    {{'H', 's'}, HProductionInteger},
    {{'H', '\"'}, HProductionValue},
    {{'A', 'p'}, AProduction},
    {{'A', 'q'}, AProduction},
    {{'A', 'r'}, AProduction},
    {{'A', 's'}, AProduction},
    {{'E', '0'}, EProduction},
    {{'E', '1'}, EProduction},
    {{'E', '2'}, EProduction},
    {{'E', '3'}, EProduction},
    {{'E', '4'}, EProduction},
    {{'E', '5'}, EProduction},
    {{'E', '6'}, EProduction},
    {{'E', '7'}, EProduction},
    {{'E', '8'}, EProduction},
    {{'E', '9'}, EProduction},
    {{'E', 'p'}, EProduction},
    {{'E', 'q'}, EProduction},
    {{'E', 'r'}, EProduction},
    {{'E', 's'}, EProduction},
    {{'E', '('}, EProduction},
    {{'E', '+'}, EProduction},
    {{'E', '-'}, EProduction},
    {{'Q', ')'}, Lambda},
    {{'Q', '+'}, QProductionPlus},
    {{'Q', '-'}, QProductionMinus},
    {{'Q', ';'}, Lambda},
    {{'T', '0'}, TProduction},
    {{'T', '1'}, TProduction},
    {{'T', '2'}, TProduction},
    {{'T', '3'}, TProduction},
    {{'T', '4'}, TProduction},
    {{'T', '5'}, TProduction},
    {{'T', '6'}, TProduction},
    {{'T', '7'}, TProduction},
    {{'T', '8'}, TProduction},
    {{'T', '9'}, TProduction},
    {{'T', 'p'}, TProduction},
    {{'T', 'q'}, TProduction},
    {{'T', 'r'}, TProduction},
    {{'T', 's'}, TProduction},
    {{'T', '('}, TProduction},
    {{'T', '+'}, TProduction},
    {{'T', '-'}, TProduction},
    {{'R', ')'}, Lambda},
    {{'R', '+'}, Lambda},
    {{'R', '-'}, Lambda},
    {{'R', '*'}, RProductionMulti},
    {{'R', '/'}, RProductionDiv},
    {{'R', ';'}, Lambda},
    {{'F', '0'}, FProductionNum},
    {{'F', '1'}, FProductionNum},
    {{'F', '2'}, FProductionNum},
    {{'F', '3'}, FProductionNum},
    {{'F', '4'}, FProductionNum},
    {{'F', '5'}, FProductionNum},
    {{'F', '6'}, FProductionNum},
    {{'F', '7'}, FProductionNum},
    {{'F', '8'}, FProductionNum},
    {{'F', '9'}, FProductionNum},
    {{'F', 'p'}, FProductionInt},
    {{'F', 'q'}, FProductionInt},
    {{'F', 'r'}, FProductionInt},
    {{'F', 's'}, FProductionInt},
    {{'F', '('}, FProductionE},
    {{'F', '+'}, FProductionNum},
    {{'F', '-'}, FProductionNum},
    {{'N', '0'}, NProduction},
    {{'N', '1'}, NProduction},
    {{'N', '2'}, NProduction},
    {{'N', '3'}, NProduction},
    {{'N', '4'}, NProduction},
    {{'N', '5'}, NProduction},
    {{'N', '6'}, NProduction},
    {{'N', '7'}, NProduction},
    {{'N', '8'}, NProduction},
    {{'N', '9'}, NProduction},
    {{'N', '+'}, NProduction},
    {{'N', '-'}, NProduction},
    {{'Y', '0'}, YProduction},
    {{'Y', '1'}, YProduction},
    {{'Y', '2'}, YProduction},
    {{'Y', '3'}, YProduction},
    {{'Y', '4'}, YProduction},
    {{'Y', '5'}, YProduction},
    {{'Y', '6'}, YProduction},
    {{'Y', '7'}, YProduction},
    {{'Y', '8'}, YProduction},
    {{'Y', '9'}, YProduction},
    {{'Y', ')'}, Lambda},
    {{'Y', '*'}, Lambda},
    {{'Y', '/'}, Lambda},
    {{'Y', '+'}, Lambda},
    {{'Y', '-'}, Lambda},
    {{'Y', ';'}, Lambda},
    {{'V', '0'}, Lambda},
    {{'V', '1'}, Lambda},
    {{'V', '2'}, Lambda},
    {{'V', '3'}, Lambda},
    {{'V', '4'}, Lambda},
    {{'V', '5'}, Lambda},
    {{'V', '6'}, Lambda},
    {{'V', '7'}, Lambda},
    {{'V', '8'}, Lambda},
    {{'V', '9'}, Lambda},
    {{'V', '+'}, VProductionPos},
    {{'V', '-'}, VProductionNeg},
    {{'D', '0'}, DProductionZero},
    {{'D', '1'}, DProductionOne},
    {{'D', '2'}, DProductionTwo},
    {{'D', '3'}, DProductionThree},
    {{'D', '4'}, DProductionFour},
    {{'D', '5'}, DProductionFive},
    {{'D', '6'}, DProductionSix},
    {{'D', '7'}, DProductionSeven},
    {{'D', '8'}, DProductionEight},
    {{'D', '9'}, DProductionNine},
    {{'L', 'p'}, LProductionP},
    {{'L', 'q'}, LProductionQ},
    {{'L', 'r'}, LProductionR},
    {{'L', 's'}, LProductionS}
};


// Function to print the contents of a stack backward
void printStack(stack<char> s, ofstream& stackFile) 
{
    if (s.empty()) 
        return;
        
    char temp = s.top();

    s.pop();
    printStack(s,stackFile);
    stackFile << temp;
}

//Function to trace input strings
bool traceInput(ofstream& stackFile, ifstream& tokenFile) 
{
    bool checkRev1 = false;
    bool checkRev2 = false;
    bool checkRev3 = false;
    bool checkRev4 = false;
    bool checkRev5 = false;
    bool checkRev6 = false;
    bool checkRev7 = false;
    int check = 0;
    string input;
    bool toRead = true;
    stack<char> aStack;
    char token;
    aStack.push('$');
    aStack.push('P');
    stackFile << "\nPush: $, Push: P" << endl;
    
    size_t i = 0;
    tokenFile >> input;
    // Loop until the stack is empty or the input string has been fully read
    while (!aStack.empty() && !tokenFile.eof()) 
    {
        char token = input[i];
        stackFile << "Stack: ";
        printStack(aStack, stackFile);

        char top = aStack.top(); 
        if (top == 'm' && checkRev1)
        {
            for (int x = 6; x >= 0; x--)
            {
                if (input[x] != RESERVED1[x])
                {
                    errorCheck(1);
                }
                aStack.pop();
                top = aStack.top();
                ++i;
            }
            stackFile << "\n\nPop: program" << endl;
            stackFile << "Match with the input string: program\n\n";
            toRead = true;
            checkRev1 = false;
            stackFile << "Pop: " << top << endl;
            aStack.pop();
        }
        else if (top == 'r' && checkRev2) 
        {
            for (int x = 2; x >= 0; x--)
            {
                if (top != RESERVED2[x])
                {
                    errorCheck(2);
                }   
                aStack.pop();
                top = aStack.top();
                ++i;
            }
            stackFile << "\n\nPop: var" << endl;
            stackFile << "Match with the input string: var\n\n";
            toRead = true;
            checkRev2 = false;
            stackFile << "Pop: " << top << endl;
            tokenFile >> input;
            aStack.pop();
        }
        else if (top == 'n' && checkRev3)
        {
            for (int x = 4; x >= 0; x--)
            {
                if (top != RESERVED3[x])
                {
                    errorCheck(3);
                }
                aStack.pop();
                top = aStack.top();
                ++i;
            }
            stackFile << "\n\nPop: begin" << endl;
            stackFile << "Match with the input string: begin\n\n";
            toRead = true;
            checkRev3 = false;
            stackFile << "Pop: " << top << endl;            
            tokenFile >> input;
            aStack.pop();
        }
        else if (top == '.' && checkRev4)
        {
            for (int x = 3; x >= 0; x--)
            {
                if (top != RESERVED4[x])
                {
                    errorCheck(4);
                }
                aStack.pop();
                top = aStack.top();
                ++i;
            }
            stackFile << "\n\nPop: end." << endl;
            stackFile << "Match with the input string: end.\n\n";
            toRead = true;
            checkRev4 = false;
            stackFile << "Pop: " << top << endl;
            aStack.pop();
        }
        else if (top == 'r' && checkRev5)
        {
            for (int x = 6; x >= 0; x--)
            {
                if (top != RESERVED5[x])
                {
                    errorCheck(5);
                }
                aStack.pop();
                top = aStack.top();
                ++i;
            }
            stackFile << "\n\nPop: integer" << endl;
            stackFile << "Match with the input string: integer\n\n";
            toRead = true;
            checkRev5 = false;
            stackFile << "Pop: " << top << endl;
            aStack.pop();
        }
        else if (top == 'y' && checkRev6)
        {
            for (int x = 6; x >= 0; x--)
            {
                if (top != RESERVED6[x])
                {
                    errorCheck(6);
                }
                aStack.pop();
                top = aStack.top();
                ++i;
            }
            stackFile << "\n\nPop: display" << endl;
            stackFile << "Match with the input string: display\n\n" << endl;
            toRead = true;
            checkRev6 = false;
            stackFile << "Pop: " << top << endl;
            aStack.pop();
        }
        else if (top == '=' && checkRev7)
        {
            for (int x = 7; x > 0; x--)
            {
                aStack.pop();
                top = aStack.top();
                ++i;
            }
            stackFile << "\n\nPop: \"value=\"" << endl;
            stackFile << "Match with the input string: \"value=\n\n" << endl;
            toRead = true;
            checkRev7 = false;
            stackFile << "Pop: " << top << endl;
            aStack.pop();
        }
        else
        {
            stackFile << "\n\nPop: " << top << endl;
            aStack.pop();   
        }

        if(i >= (input.length()))
        {
            i = 0;
            tokenFile >> input;
            token = input[i];
        }

        //Print Read: token and Input string: string
        if (toRead) 
        {
            stackFile << "Read: " << token << endl;
            toRead = false;
            stackFile << "Input string : " << input << endl;
        }
        //If a string has matched, move index i to next char, print message matched
        if (top == token) 
        {
            stackFile << "Match with the input string: " << token << endl;
            toRead = true;
            ++i;
        } 
        // Find the production for the current non-terminal and input symbol in the parsing table.
        else if (table.find({top, token}) != table.end()) 
        {
            string prod = table[{top, token}];
            stackFile << "Go to [" << top << ", " << token << "] = " << prod << endl;
            // If the production is not a lambda (empty) production, push its symbols onto the stack in reverse order.
            if (prod != Lambda) 
            {
                for (int j = prod.length() -1; j >= 0;j--) 
                {
                    if (prod[j] != ' ')
                    {   
                        int x = 0;
                        int z = j;
                        if (prod[j] == 'n' && prod[j-2] == 'g')
                        {
                            for(x = 4; x >= 0; x--)
                            {
                                aStack.push(prod[z-x]);
                                j--;
                            }
                            stackFile << "Push: begin, ";
                            checkRev3 = true;
                        }
                        else if (prod[j] == 'm' && prod[j-2] == 'r')
                        {
                            for (x = 6; x >= 0; x--)
                            {
                                aStack.push(prod[z-x]);
                                j--;
                            }
                            stackFile << "Push: program" << endl;
                            checkRev1 = true;
                        }
                        else if (prod[j] == 'r' && prod[j-2] == 'v')
                        {
                            for (x = 2; x >= 0; x--)
                            {
                                aStack.push(prod[z-x]);
                                j--;
                            }
                            stackFile << "Push: var, ";
                            checkRev2 = true;
                        }
                        else if (prod[j] == '.' && prod[j-2] == 'n')
                        {
                            for (x = 3; x >= 0; x--)
                            {
                                aStack.push(prod[z-x]);
                                j--;
                            }
                            stackFile << "Push: end., ";
                            checkRev4 = true;
                        }
                        else if (prod[j] == 'r' && prod[j-2] == 'g')
                        {
                            for (x = 6; x >= 0; x--)
                            {
                                aStack.push(prod[z-x]);
                                j--;
                            }
                            stackFile << "Push: integer\n";
                            checkRev5 = true;
                        }
                        else if (prod[j] == 'y' && prod[j-2] == 'l')
                        {
                            for (x = 6; x >= 0; x--)
                            {
                                aStack.push(prod[z-x]);
                                j--;
                            }
                            stackFile << "Push: display, ";
                            checkRev6 = true;
                        }
                        else if (prod[j] == '\"' && prod[j-2] == 'e')
                        {
                            for (x = 7; x >= 0; x--)
                            {
                                aStack.push(prod[z-x]);
                                j--;
                            }
                            stackFile << "Push: \"value=\", ";
                            checkRev7 = true;
                        }
                        else
                        {
                            aStack.push(prod[j]);
                            if(j == 0)
                                stackFile << "Push: " << prod[j] << endl;
                            else
                                stackFile << "Push: " << prod[j] << ", ";;
                        }
                    }
                }
            }
            if (prod == Lambda)
            {
                top = aStack.top();
            }
        }
        //If the go to a blank, then rejected
        else 
        {
            stackFile << "\n" << input << " is rejected." << endl;
            return false;

        }
            
    }
    stackFile << "\n" << input << " is accepted." << endl;
    return true;

}

void errorCheck (int errorCode)
{
    ofstream errorFile;
    errorFile.open("error.txt");

    switch (errorCode)
    {
    case 1:
        errorFile << "program\tis expected(is missing or is spelled incorrectly)\n";
        break;
    case 2:
        errorFile << "var\tis expected(is missing or is spelled incorrectly)\n";
        break;
    case 3:
        errorFile << "begin\tis expected(is missing or is spelled incorrectly)\n";
        break;
    case 4:
        errorFile << "end.\tis expected(is missing or is spelled incorrectly)\n";
        break;
    case 5:
        errorFile << "integer\tis expected(is missing or is spelled incorrectly)\n";
        break;
    case 6:
        errorFile << "display\tis expected(is missing or is spelled incorrectly)\n";
        break;
    default:
        break;
    }
    
    errorFile.close();

    cout << "Something went wrong check the error.txt\n";
    exit(EXIT_FAILURE);
}

int main() 
{
    bool result = true;
    ifstream tokenFile;
    ofstream stackFile;

    // openning our targeted txt file
    tokenFile.open("finalp2.txt");
    stackFile.open("stack.txt");

    // loop for as long as we have not reached the end of file
    while (!tokenFile.eof() && result)
    {
    result = traceInput(stackFile,tokenFile);
    }

    if (result)
    {
        cout << "*** Your program was ACCEPTED! ***\n";
    }
    else
    {
        cout << "*** Your program was REJECTED! ***\n";
        cout << "Check your error.txt file to see what went wrong\n";
    }
    

    tokenFile.close();
    stackFile.close();
    return 0;
    
}