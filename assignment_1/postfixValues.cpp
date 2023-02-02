/*
Group Names: Jay Vang, Jesse Shaihor, Cristian Salinas
Homework 1
Due Date: Feb 2,2023
Purpose: this program reads an expression in postfix, evaluates the expression
*/
#include <iostream>
#include <stack>
#include <math.h>
 
using namespace std;
 
const int MAX = 100;
int calc_Postfix(string expression);
 
//stack implementation
class Stack 
{
    int topCounter;
public:
    int myStack[MAX];
 
    Stack() { topCounter = -1; }
    int top();
    bool push(int x);
    int pop();
    bool isEmpty();
};
 
bool Stack::push(int item)
{
    if (topCounter >= (MAX - 1))
    {
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
 
    while (choice == 'y')
    {
        string s;
        cout << "Enter a post fix expression with $ at the end: ";
        cin >> s;
        finalValue = calc_Postfix(s);
        cout << "Value = " << finalValue << endl;
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