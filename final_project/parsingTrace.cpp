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

// reserved words
const string RESERVED1 = "program";
const string RESERVED2 = "var";
const string RESERVED3 = "begin";
const string RESERVED4 = "end.";
const string RESERVED5 = "integer";
const string RESERVED6 = "display";

// Define the grammar productions as strings
const string PProduction = "program I; var B begin G";
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
const string EProduction = "TQ;";
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
/*    
    {{'P', "program"}, PProduction},
    {{'I', "p"}, IProduction},
    {{'I', "q"}, IProduction},
    {{'I', "r"}, IProduction},
    {{'I', "s"}, IProduction},
    {{'X', "0"}, XProduction},
    {{'X', "1"}, XProduction},
    {{'X', "2"}, XProduction},
    {{'X', "3"}, XProduction},
    {{'X', "4"}, XProduction},
    {{'X', "5"}, XProduction},
    {{'X', "6"}, XProduction},
    {{'X', "7"}, XProduction},
    {{'X', "8"}, XProduction},
    {{'X', "9"}, XProduction},
    {{'M', "0"}, MProductionDigit},
    {{'M', "1"}, MProductionDigit},
    {{'M', "2"}, MProductionDigit},
    {{'M', "3"}, MProductionDigit},
    {{'M', "4"}, MProductionDigit},
    {{'M', "5"}, MProductionDigit},
    {{'M', "6"}, MProductionDigit},
    {{'M', "7"}, MProductionDigit},
    {{'M', "8"}, MProductionDigit},
    {{'M', "9"}, MProductionDigit},
    {{'M', "p"}, MProductionLetter},
    {{'M', "q"}, MProductionLetter},
    {{'M', "r"}, MProductionLetter},
    {{'M', "s"}, MProductionLetter},
    {{'B', "p"}, BProduction},
    {{'B', "q"}, BProduction},
    {{'B', "r"}, BProduction},
    {{'B', "s"}, BProduction},
    {{'C', "p"}, CProduction},
    {{'C', "q"}, CProduction},
    {{'C', "r"}, CProduction},
    {{'C', "s"}, CProduction},
    {{'J', ","}, JProduction},
    {{'J', ":"}, Lambda},
    {{'Z', "integer"}, ZProduction},
    {{'G', "p"}, GProduction},
    {{'G', "q"}, GProduction},
    {{'G', "r"}, GProduction},
    {{'G', "s"}, GProduction},
    {{'G', "display"}, GProduction},
    {{'K', "p"}, KProduction},
    {{'K', "q"}, KProduction},
    {{'K', "r"}, KProduction},
    {{'K', "s"}, KProduction},
    {{'K', "display"}, KProduction},
    {{'K', "end."}, Lambda},
    {{'S', "p"}, SProductionAssign},
    {{'S', "q"}, SProductionAssign},
    {{'S', "r"}, SProductionAssign},
    {{'S', "s"}, SProductionAssign},
    {{'S', "display"}, SProductionWrite},
    {{'W', "display"}, WProduction},
    {{'O', "("}, OProduction},
    {{'H', "p"}, HProductionInteger},
    {{'H', "q"}, HProductionInteger},
    {{'H', "r"}, HProductionInteger},
    {{'H', "s"}, HProductionInteger},
    {{'H', "\'value=\',"}, HProductionValue},
    {{'A', "p"}, AProduction},
    {{'A', "q"}, AProduction},
    {{'A', "r"}, AProduction},
    {{'A', "s"}, AProduction},
    {{'E', "0"}, EProduction},
    {{'E', "1"}, EProduction},
    {{'E', "2"}, EProduction},
    {{'E', "3"}, EProduction},
    {{'E', "4"}, EProduction},
    {{'E', "5"}, EProduction},
    {{'E', "6"}, EProduction},
    {{'E', "7"}, EProduction},
    {{'E', "8"}, EProduction},
    {{'E', "9"}, EProduction},
    {{'E', "p"}, EProduction},
    {{'E', "q"}, EProduction},
    {{'E', "r"}, EProduction},
    {{'E', "s"}, EProduction},
    {{'E', "("}, EProduction},
    {{'E', "+"}, EProduction},
    {{'E', "-"}, EProduction},
    {{'Q', ")"}, Lambda},
    {{'Q', "+"}, QProductionPlus},
    {{'Q', "-"}, QProductionMinus},
    {{'Q', ";"}, Lambda},
    {{'T', "0"}, TProduction},
    {{'T', "1"}, TProduction},
    {{'T', "2"}, TProduction},
    {{'T', "3"}, TProduction},
    {{'T', "4"}, TProduction},
    {{'T', "5"}, TProduction},
    {{'T', "6"}, TProduction},
    {{'T', "7"}, TProduction},
    {{'T', "8"}, TProduction},
    {{'T', "9"}, TProduction},
    {{'T', "p"}, TProduction},
    {{'T', "q"}, TProduction},
    {{'T', "r"}, TProduction},
    {{'T', "s"}, TProduction},
    {{'T', "("}, TProduction},
    {{'T', "+"}, TProduction},
    {{'T', "-"}, TProduction},
    {{'R', ")"}, Lambda},
    {{'R', "*"}, RProductionMulti},
    {{'R', "/"}, RProductionDiv},
    {{'R', ";"}, Lambda},
    {{'F', "0"}, FProductionNum},
    {{'F', "1"}, FProductionNum},
    {{'F', "2"}, FProductionNum},
    {{'F', "3"}, FProductionNum},
    {{'F', "4"}, FProductionNum},
    {{'F', "5"}, FProductionNum},
    {{'F', "6"}, FProductionNum},
    {{'F', "7"}, FProductionNum},
    {{'F', "8"}, FProductionNum},
    {{'F', "9"}, FProductionNum},
    {{'F', "p"}, FProductionInt},
    {{'F', "q"}, FProductionInt},
    {{'F', "r"}, FProductionInt},
    {{'F', "s"}, FProductionInt},
    {{'F', "("}, FProductionE},
    {{'F', "+"}, FProductionNum},
    {{'F', "-"}, FProductionNum},
    {{'N', "0"}, NProduction},
    {{'N', "1"}, NProduction},
    {{'N', "2"}, NProduction},
    {{'N', "3"}, NProduction},
    {{'N', "4"}, NProduction},
    {{'N', "5"}, NProduction},
    {{'N', "6"}, NProduction},
    {{'N', "7"}, NProduction},
    {{'N', "8"}, NProduction},
    {{'N', "9"}, NProduction},
    {{'N', "+"}, NProduction},
    {{'N', "-"}, NProduction},
    {{'Y', "0"}, YProduction},
    {{'Y', "1"}, YProduction},
    {{'Y', "2"}, YProduction},
    {{'Y', "3"}, YProduction},
    {{'Y', "4"}, YProduction},
    {{'Y', "5"}, YProduction},
    {{'Y', "6"}, YProduction},
    {{'Y', "7"}, YProduction},
    {{'Y', "8"}, YProduction},
    {{'Y', "9"}, YProduction},
    {{'Y', ")"}, Lambda},
    {{'Y', "*"}, Lambda},
    {{'Y', "/"}, Lambda},
    {{'Y', "+"}, Lambda},
    {{'Y', "-"}, Lambda},
    {{'Y', ";"}, Lambda},
    {{'N', "0"}, Lambda},
    {{'N', "1"}, Lambda},
    {{'N', "2"}, Lambda},
    {{'N', "3"}, Lambda},
    {{'N', "4"}, Lambda},
    {{'N', "5"}, Lambda},
    {{'N', "6"}, Lambda},
    {{'N', "7"}, Lambda},
    {{'N', "8"}, Lambda},
    {{'N', "9"}, Lambda},
    {{'N', "+"}, VProductionPos},
    {{'N', "-"}, VProductionNeg},
    {{'D', "0"}, DProductionOne},
    {{'D', "1"}, DProductionTwo},
    {{'D', "2"}, DProductionThree},
    {{'D', "3"}, DProductionFour},
    {{'D', "4"}, DProductionFive},
    {{'D', "6"}, DProductionSix},
    {{'D', "7"}, DProductionSeven},
    {{'D', "8"}, DProductionEight},
    {{'D', "9"}, DProductionNine},
    {{'L', "p"}, LProductionP},
    {{'L', "q"}, LProductionQ},
    {{'L', "r"}, LProductionR},
    {{'L', "s"}, LProductionS}
*/
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
    {{'N', '0'}, Lambda},
    {{'N', '1'}, Lambda},
    {{'N', '2'}, Lambda},
    {{'N', '3'}, Lambda},
    {{'N', '4'}, Lambda},
    {{'N', '5'}, Lambda},
    {{'N', '6'}, Lambda},
    {{'N', '7'}, Lambda},
    {{'N', '8'}, Lambda},
    {{'N', '9'}, Lambda},
    {{'N', '+'}, VProductionPos},
    {{'N', '-'}, VProductionNeg},
    {{'D', '0'}, DProductionOne},
    {{'D', '1'}, DProductionTwo},
    {{'D', '2'}, DProductionThree},
    {{'D', '3'}, DProductionFour},
    {{'D', '4'}, DProductionFive},
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
    string input;
    string tokenTemp;
    bool toRead = true;
    stack<char> aStack;
    stack<string> bStack;
    aStack.push('$');
    aStack.push('P');
    stackFile << "\nPush: $, Push: P" << endl;
    
    size_t i = 0;
    tokenFile >> input;
    // Loop until the stack is empty or the input string has been fully read
    while (!aStack.empty() && !tokenFile.eof()) 
    {
        if(i > input.length() -1)
        {
            tokenFile >> input;
            i = 0;
        }
        char token = input[i];
        stackFile << "Stack: ";
        printStack(aStack, stackFile);

        char top = aStack.top(); 
        if (top == 'p')
        {
            for (int x = 0; x < 7; x++)
            {
                aStack.pop();
                top = aStack.top();
                stackFile << "\n\nPop: " << top << endl;
                ++i;
            }
            stackFile << "Match with the input string: " << token << endl;
            toRead = true;
        }
        else if (top == 'v') 
        {
            for (int x = 0; x < 3; x++)
            {
                aStack.pop();
                top = aStack.top();
                stackFile << "\n\nPop: " << top << endl;
                ++i;
            }
            stackFile << "Match with the input string: " << token << endl;
            toRead = true;
        }
        else if (top == 'b')
        {
            for (int x = 0; x < 5; x++)
            {
                aStack.pop();
                top = aStack.top();
                stackFile << "\n\nPop: " << top << endl;
                ++i;
            }
            stackFile << "Match with the input string: " << token << endl;
            toRead = true;
        }
        else if (top == 'e')
        {
            for (int x = 0; x < 4; x++)
            {
                aStack.pop();
                top = aStack.top();
                stackFile << "\n\nPop: " << top << endl;
                ++i;
            }
            stackFile << "Match with the input string: " << token << endl;
            toRead = true;
        }
        else if (top == 'i')
        {
            for (int x = 0; x < 7; x++)
            {
                aStack.pop();
                top = aStack.top();
                stackFile << "\n\nPop: " << top << endl;
                ++i;
            }
            stackFile << "Match with the input string: " << token << endl;
            toRead = true;
        }
        else if (top == 'd')
        {
            for (int x = 0; x < 7; x++)
            {
                aStack.pop();
                top = aStack.top();
                stackFile << "\n\nPop: " << top << endl;
                ++i;
            }
            stackFile << "Match with the input string: " << token << endl;
            toRead = true;
        }
        else
        {
            stackFile << "\n\nPop: " << top << endl;
            aStack.pop();
            ++i;   
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
        else if (table.find({top, input[0]}) != table.end()) 
        {
            string prod = table[{top, input[0]}];
            stackFile << "Go to [" << top << ", " << input << "] = " << prod << endl;
            // If the production is not a lambda (empty) production, push its symbols onto the stack in reverse order.
            if (prod != Lambda) 
            {
                for (int j = prod.length() - 1; j >= 0; j--) 
                {
                    if (prod[j] != ' ')
                    {   
                        aStack.push(prod[j]);
                        if(j == 0)
                            stackFile << "Push: " << prod[j] << endl;
                        else
                            stackFile << "Push: " << prod[j] << ", ";
                    }
                }
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

int main() 
{
    ifstream tokenFile;
    ofstream stackFile;

    // openning our targeted txt file
    tokenFile.open("finalp2.txt");
    stackFile.open("stack.txt");

    // loop for as long as we have not reached the end of file
    while (!tokenFile.eof())
    {
    traceInput(stackFile,tokenFile);
    }

    tokenFile.close();
    stackFile.close();
    return 0;
    
}




