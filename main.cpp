#include <iostream>
#include <string.h>
#include <string>
#include <iomanip>
#include <cstdio>
#include <vector>
#include <stdexcept>
using namespace std;
#include "stack.cpp"
vector<string> in2post(vector<string>&);
vector<string> in2pre(vector<string>&);
string post2in(vector<string>);
string pre2in(vector<string>);
vector<string> stringToInfix(string&);
vector<string> stringToVector(string&);
void printTerm(vector<string>&);
bool isDigit(const string& str)
{
    string::const_iterator iter = str.begin();
    for(; isdigit(*iter) && iter != str.end(); iter++);
    return !str.empty() && iter == str.end();

}
bool isOperator(const string& str)
{
    string::const_iterator iter = str.begin();
    return !str.empty() && str.size() == 1 &&
            (*iter == '*' || *iter == '+' || *iter == '-' || *iter == '/');
}
bool precedeOperator(const string& first, const string& second)
{
    if (first == "+" || first == "-")
        return second == "*" || second == "/" || second == "^";
    else if (first == "*" || first == "/")
        return second == "*" || second == "/";
    else if (first == "^")
        return second == "^";
}
vector<string> getReverse(vector<string>& str)
{
    vector<string> z;
    for (int i = str.size() - 1; i >= 0; i--)
    {
        if (str[i] == "(")
            z.push_back(")");
        else if (str[i] == ")")
            z.push_back("(");
        else
            z.push_back(str[i]);
    }
    return z;
}
int main()
{
    do
    {
        string head(76, '*'), middle(25, '*');
        string pressKey = "Press any key to continue...\n";
        system("clear");
        cout << head << endl;
        cout << middle << " Prefix   Infix   Postfix " << middle << endl;
        cout << head << endl;
        cout << "1. I want to enter a prefix term." << endl
             << "2. I want to enter an infix term." << endl
             << "3. I want to enter a postfix term." << endl
             << "default. Exit." << endl
             << "Enter your selection: ";
        int input;
        cin >> input;
        try
        {
            string term;
            vector<string> inputTerm;
            vector<string> inToPre, inToPost;
            string postToIn, preToIn;
            switch (input)
            {
            case 1:
                cout << "Enter your prefix term: ";
                cin.ignore();
                getline(cin, term);
                inputTerm = stringToVector(term);

                cout << "Equivalent infix term:\n";
                preToIn = pre2in(inputTerm);
                inputTerm = stringToInfix(preToIn);
                printTerm(inputTerm);

                cout << "Equivalent postfix term:\n";
                inToPost = in2post(inputTerm);
                printTerm(inToPost);


                break;

            case 2:
                cout << "Enter your infix term: ";
                cin.ignore();
                getline(cin, term);
                inputTerm = stringToInfix(term);

                cout << "Equivalent prefix term:\n";
                inToPre = in2pre(inputTerm);
                printTerm(inToPre);

                cout << "Equivalent postfix term:\n";
                inToPost = in2post(inputTerm);
                printTerm(inToPost);

                break;

            case 3:
                cout << "Enter your postfix term: ";
                cin.ignore();
                getline(cin, term);
                inputTerm = stringToVector(term);

                cout << "Equivalent infix term:\n";
                postToIn = post2in(inputTerm);
                inputTerm = stringToInfix(postToIn);
                inputTerm = getReverse(inputTerm);
                printTerm(inputTerm);

                cout << "Equivalent prefix term:\n";
                inToPre = in2pre(inputTerm);
                printTerm(inToPre);

                break;

            default:
                return 0;
            }
        }
        catch (const invalid_argument &ex)
        {
            cerr << ex.what() << endl;
            return 1;
        }
        cout << pressKey;
        cin.get();
    } while (true);
}
vector<string> stringToInfix(string& str)
{
    vector<string> result;
    string tmp = "";
    short openParantheses = 0;
    for (int i = 0; i < str.size(); i++)
    {
        char localTmp = str[i];
        string lastOp = "";
        if (!result.empty())
            lastOp = *(result.end() - 1);
        if (localTmp >= '0' && localTmp <= '9')
        {
            if (lastOp == ")")
                throw invalid_argument("number after ')' at position " + i);
            tmp += localTmp;
        }
        else if (localTmp == '+' || localTmp == '-' ||
                 localTmp == '/' || localTmp == '*')
        {
            if (tmp == "")
            {
                if (result.empty())
                    throw invalid_argument("operator in the beginning of the input at position " + i);
                else if (lastOp == "+" || lastOp == "-" ||
                         lastOp == "*" || lastOp == "/")
                    throw invalid_argument("operator after operator at position " + i);
                else if (lastOp == "(")
                    throw invalid_argument("operator after '(' at position " + i);
            }
            else // if (tmp != "")
            {
                result.push_back(tmp);
                tmp = "";
            }
            result.push_back(string(1, localTmp));
        }
        else if (localTmp == '(')
        {
            openParantheses++;
            if (tmp != "")
                throw invalid_argument("'(' after number at position " + i);
            else if (lastOp == ")")
                throw invalid_argument("'(' after ')' at position " + i);
            result.push_back(string(1, localTmp));
        }
        else if (localTmp == ')')
        {
            if (openParantheses == 0)
                throw invalid_argument("number of ')' is more that '(' at position" + i);
            if (tmp != "")
            {
                result.push_back(tmp);
                tmp = "";
            }
            result.push_back(string(1, localTmp));
            openParantheses--;
        }
    }
    if (tmp != "")
        result.push_back(tmp);
    if (openParantheses > 0)
        throw invalid_argument("number of '(' more that ')' at the end of the input");
    return result;
}

vector<string> stringToVector(string& str)
{
    vector<string> result;
    string tmp = "";
    short openParantheses = 0;
    for (int i = 0; i < str.size(); i++)
    {
        char localTmp = str[i];
        string lastOp = "";
        if (!result.empty())
            lastOp = *(result.end() - 1);
        if (localTmp == ' ' || localTmp == '\t')
        {
            if (tmp != "")
            {
                result.push_back(tmp);
                tmp = "";
            }
            continue;
        }
        else if (localTmp >= '0' && localTmp <= '9')
        {
            tmp += localTmp;
        }
        else if (localTmp == '+' || localTmp == '-' ||
                 localTmp == '/' || localTmp == '*')
        {
            if (tmp != "")
            {
                result.push_back(tmp);
                tmp = "";
            }
            result.push_back(string(1, localTmp));
        }
        else if (localTmp == '(')
        {
            openParantheses++;
            result.push_back(string(1, localTmp));
        }
        else if (localTmp == ')')
        {
            if (tmp != "")
            {
                result.push_back(tmp);
                tmp = "";
            }
            result.push_back(string(1, localTmp));
            openParantheses--;
        }
    }
    if (tmp != "")
        result.push_back(tmp);
    if (openParantheses > 0)
        throw invalid_argument("number of '(' more that ')' at the end of the input");
    return result;
}

void printTerm(vector<string>& input)
{
    for (unsigned int i = 0; i < input.size(); i++)
        cout << input[i] << setw(2);
    cout << endl;
}

// ========================================== infix to others ===================================================
vector<string> in2post(vector<string>& x)
{
    vector<string> y; // the equivalent postfix expression
    stack<string> opStack;

    // step 1: Push “(“onto Stack, and add “)” to the end of X.
    opStack.push("(");
    x.push_back(")");

    // step 2: Scan X from left to right and repeat Step 3 to 6 for each element of X until the Stack is empty.
    for (vector<string>::const_iterator iter = x.begin();
         iter != x.end();
         iter++)
    {
        // step 3: If an operand is encountered, add it to Y.
        if (isDigit(*iter))
            y.push_back(*iter);

        // step 4: If a left parenthesis is encountered, push it onto Stack.
        else if (*iter == "(")
            opStack.push(*iter);

        // step 5: If an operator is encountered ,then:
        else if (isOperator(*iter))
        {

            // step 5.1: Repeatedly pop from Stack and add to Y each operator (on the top of Stack)
            // which has the same precedence as or higher precedence than operator.
            while (true)
            {
                string lastOperator = opStack.top();
                if (precedeOperator(*iter, lastOperator))
                {
                    y.push_back(lastOperator);
                    opStack.pop();
                }
                else
                    break;
            }
            // step 5.2: Add operator to Stack.
            opStack.push(*iter);
        }

        // step 6: If a right parenthesis is encountered ,then:
        else if (*iter == ")")
        {
            // step 6.1: Repeatedly pop from Stack and add to Y each operator (on the top of Stack)
            // until a left parenthesis is encountered.
            while (true)
            {
                string lastOperator = opStack.top();
                if (lastOperator != "(")
                {
                    y.push_back(lastOperator);
                    opStack.pop();
                }
                else
                    break;
            }
            // step 6.2: Remove the left Parenthesis.
            opStack.pop();
        }
    }
    while (!opStack.isEmpty())
    {
        string lastOperator = opStack.top();
        if (lastOperator != "(")
            y.push_back(lastOperator);
        opStack.pop();
    }
    // END
    return y;
}

vector<string> in2pre(vector<string>& x)
{
    /* 1. get the infix expression
     * 2. reverse the infix notation
     * 3. get the equivalent postfix notation of result from step 2 (in2post)
     * 4. reverse the expression from step 3 to some y
     * 5. the result is in y and can be used accordingly
     */
    vector<string> reverse = getReverse(x);
    vector<string> y = in2post(reverse);
    return getReverse(y);
}
string post2in(vector<string> x)
{
    /* Algorithm
    1.While there are input symbol left
        1.1 Read the next symbol from the input.
    2.If the symbol is an operand
        2.1 Push it onto the stack.
    3.Otherwise,
        3.1 the symbol is an operator.
        3.2 Pop the top 2 values from the stack.
        3.3 Put the operator, with the values as arguments and form a string.
        3.4 Push the resulted string back to stack.
    4.If there is only one value in the stack
        4.1 That value in the stack is the desired infix string. */
    stack<string> opStack;
    for (vector<string>::const_iterator iter = x.begin(); iter != x.end(); iter++)
    {
        if (isDigit(*iter)) // step 2
            opStack.push(*iter);
        else if (isOperator(*iter)) // step 3
        {
            string op1 = opStack.top();
            opStack.pop();
            string op2 = opStack.top();
            opStack.pop();
            string result = "(" + op1 + *iter + op2 + ")";
            opStack.push(result);
        }
    }
    if (opStack.getSize() == 1)
        return opStack.top();

}

string pre2in(vector<string> x)
{
    /* 1. Read the Prefix expression in reverse order (from right to left)
       2. If the symbol is an operand, then push it onto the Stack
       3. If the symbol is an operator, then pop two operands from the Stack
       4. Create a string by concatenating the two operands and the operator between them.
       5. string = (operand1 + operator + operand2)
       6. And push the resultant string back to Stack
       7. Repeat the above steps until end of Prefix expression.*/
    x = getReverse(x);
    stack<string> opStack;
    for (vector<string>::const_iterator iter = x.begin(); iter != x.end(); iter++)
    {
        if (isDigit(*iter))
            opStack.push(*iter);
        else if (isOperator(*iter))
        {
            string op1 = opStack.top();
            opStack.pop();
            string op2 = opStack.top();
            opStack.pop();
            string res = "(" + op1 + *iter + op2 + ")";
            opStack.push(res);
        }
    }
    if (opStack.getSize() == 1)
        return opStack.top();
}
