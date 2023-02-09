/*
Group Names: Jay Vang, Jesse Shaihor, Cristian Salinas
Homework 1
Due Date: Feb 2,2023
Purpose: this program reads an expression in postfix, evaluates the expression
*/
#include <iostream>
#include <cstring>
#include <math.h>
 
using namespace std;
 
const int MAX = 500;
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
        cout << item << endl;
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
    int finalValue; //Where postfix calculation will be stored
    char choice = 'y';
    string s; //Where postfix expression will be stored
 
    while (choice == 'y' || choice == 'Y')
    {
        string s;
        cout << "Enter a post fix expression with $ at the end: ";
        cin >> s;
        covertString(s);
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
 
    //Integers used to calculate postfix expression
    int value1;
    int value2;

    for (int i = 0; i < expression.length(); i++)   //Loop through string and push to stack based on char
    {
        switch (expression[i])
        {
        case 'a':
            stack.push(5);
            break;
        case 'b':
            stack.push(7);
            break;
        case 'c':
            stack.push(2);
            break;
        case 'd':
            stack.push(4);
            break;
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
    return stack.top();
}