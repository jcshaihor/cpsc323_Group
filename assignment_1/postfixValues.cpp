#include <iostream>
#include <stack>
#include <math.h>

using namespace std;

const int MAX = 100;
int calc_Postfix(string expression);

class Stack
{
    int topCounter;
    public:
    int myStack[MAX];

    Stack() { topCounter = -1;}
    int top();
    bool push(int x);
    int pop();
    bool isEmpty();
};

bool Stack::push(int item)
{
    if (topCounter >= (MAX-1))
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
    int finalValue;
    char choice = 'y';
    string s;

    while (choice == 'y')
    {
        string s;
        cout << "Enter a post fix experssion with $ at the end: ";
        cin >> s;
        finalValue = calc_Postfix(s);
        cout << "Value = " << finalValue << endl;
        cout << "Continue? (y/n)";
        cin >> choice;
    }

    return 0;
}

int calc_Postfix(string expression)
{
    class Stack stack;

    int a = 5;
    int b = 7;
    int c = 2;
    int d = 4;
    int value1;
    int value2;

    for (int i = 0; i < expression.length(); i++)
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

