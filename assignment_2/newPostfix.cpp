/*
Group Names: Jay Vang, Jesse Shaihor, Cristian Salinas
Homework 1
Due Date: Feb 2,2023
Purpose: this program reads an expression in postfix, evaluates the expression
*/
#include <iostream>
#include <sstream>
#include <cstring>
#include <math.h>
#include <cctype>
 
using namespace std;
 
const int MAX = 100; //stack max value

int calc_Postfix(string expression);
 
//stack implementation
class Stack 
{
    //position in the stack array
    int topCounter;
public:
    //stack size
    int myStack[MAX];
    
    
    Stack() { topCounter = -1; } //when a stack is made it is intialized at -1
    int top();                   //current position in stack
    bool push(int x);            //add an element into the array and move the position forward 1
    int pop();                   //remove an element from the array and move position back 1
    bool isEmpty();              //check to see if array is empty
};
 
bool Stack::push(int item)
{
    if (topCounter >= (MAX - 1))
    {
        //if there is no more space in the array 
        cout << "Stack Overflow!";
        return false;
    }
    else
    {
        myStack[++topCounter] = item;
        return true;
    }
}
 
int Stack::pop()
{
    if (topCounter < 0)
    {
        cout << "Stack Underflow!";
        return 0;
    }
    else
    {
        int item = myStack[topCounter--];
        return item;
    }
}
 
int Stack::top()
{
    if (topCounter == -1)
    {
        return 0;
    }
    else
    {
        return myStack[topCounter];
    }
}
 
bool Stack::isEmpty()
{
    return (topCounter < 0);
}



int main()
{
    int finalValue;    //Where postfix calculation will be stored
    char choice = 'y'; 
    string s;          //Where postfix expression will be stored
 
    while (choice == 'y') //Continue with loop or exit
    {
        string s;
        cout << "Enter a post fix expression with $ at the end: ";
        getline(cin,s);
        finalValue = calc_Postfix(s);
        cout << "   Expressions value is " << finalValue << endl;
        cout << "Continue? (y/n)";
        cin >> choice;
    }
 
    return 0;
}
 
int calc_Postfix(string expression) //Calculate Postfix expression 
{
    class Stack stack;
 
    int value1;     //Integers used to calculate postfix expression
    int value2;
    string s1;      //Strings to hold the post expression in parts
    string s2;

    while (expression[0] != '$')    //loop as long as we don't hit $
    {
        int num;    //temp integer to hold values that we will push to the stack

        size_t pos = expression.find_first_of(' ');     //finds the first whitepace in the string
        s1 = expression.substr(0, pos);                 //copys everything before that whitespace
        s2 = expression.substr(pos + 1);                //copys everything after that whitespace
      
        if (s1[0] >= '0' && s1[0] <= '9')  //if it is a digit we will convert it into a integer
        {
            num = stoi(s1);
            stack.push(num);
        }
        else if (s1[0] >= 'a' && s1[0] <= 'z')  //if it is a char we will ask the user to enter a value
        {
            cout << "Enter the value of " << s1 << ": ";
            cin >> num;
            stack.push(num);
        }
        else  //means we hit a postfix operator
        {
            switch (s1[0])
            {  
            case '+':
                value1 = stack.top();
                stack.pop();
                value2 = stack.top();
                stack.pop();
                stack.push(value2 + value1);
                break;
            case '-':
                value1 = stack.top();
                stack.pop();
                value2 = stack.top();
                stack.pop();
                stack.push(value2 - value1);
                break;
            case '*':
                value1 = stack.top();
                stack.pop();
                value2 = stack.top();
                stack.pop();
                stack.push(value2 * value1);
                break;
            case '/':
                value1 = stack.top();
                stack.pop();
                value2 = stack.top();
                stack.pop();
                stack.push(value2 / value1);
                break;
            }
        }
        expression = s2;
    }
    return stack.top();
}