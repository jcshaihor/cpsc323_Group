// ================================================================================================
// Group Names: Jay Vang, Jesse Shaihor, Cristian Salinas
// Final Project
// Due Date: 9 May 2023
// Purpose: After checking the text file with parsingTrace.cpp and seeing that it is okay we will
// input the text file into a c++ ready program.
// ================================================================================================

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

int main()
{
    ifstream inputFile;
    ofstream convertFile;
    string input;
    bool pCheck = false;
    bool bCheck = false;
    bool eCheck = false;
    bool vCheck = false;
    bool iCheck = false;
    bool dCheck = false;

    // open the targeted files
    inputFile.open("finalp2.txt");
    convertFile.open("finalp2Convert.txt");

    // adds the standard c++ headers
    convertFile << "#include <iostream>\nusing namespace std;\nint main()\n{\n";

    // loop until we converted everything
    while(!inputFile.eof())
    {
        int counter = 0;

        // get the whole line of input
        getline(inputFile,input);

        // a check to see if we have these strings in the input
        if (input.find("program") != std::string::npos)
        {
            pCheck = true;
        }
        if (input.find("begin") != std::string::npos)
        {
            bCheck = true;
        }
        if (input.find("end.") != std::string::npos)
        {
            eCheck = true;
        }
        if (input.find("var") != std::string::npos)
        {
            vCheck = true;
        }
        if (input.find("integer") != std::string::npos)
        {
            iCheck = true;
        }
        if (input.find("display") != std::string::npos)
        {
            dCheck = true;
        }

        // When program, begin, and end. is not read we will output the contents
        if (pCheck || bCheck || eCheck || vCheck || iCheck || dCheck)
        {
            // when the integer dec-list is found convert it to correct format
            if (iCheck)
            {
                convertFile << "\tint ";
                // write until we hit the ':' and then end it with a ';'
                for (counter = 0; input[counter] != ':'; counter++)
                {
                    convertFile << input[counter];
                }
                convertFile << ";\n";
            }
            
            // when a display function is found
            if (dCheck)
            {   
                int index = 0;

                convertFile << "\tcout <<";

                // find where the display values starts
                index = input.find("(");

                counter = index + 1;
                    
                // write until we finish whats inside the display function
                for (counter; input[counter] != ')'; counter++)
                {
                    if (input[counter] != ',')
                    {
                        convertFile << input[counter]; 
                    }
                    else
                    {
                        convertFile << "<<";
                    }
                }

                // when finished end it with this statement
                convertFile << " << endl ;\n";                
            }
        }
        else
        {
            // output what is read exactly
            convertFile << "\t" << input << endl;
        }
        
        // set all checks back to false
        pCheck = false;
        bCheck = false;
        eCheck = false;
        vCheck = false;
        iCheck = false;
        dCheck = false;
    }

    // end it with a right bracket
    convertFile << "\treturn 0;\n}" << endl;

    //close the targeted files
    inputFile.close();
    convertFile.close();

    return 0; // end of main
}


