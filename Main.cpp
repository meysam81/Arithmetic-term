#include <iostream>
#include <QException>
#include <string.h>
#include <string>
#include <iomanip>
#include <cstdio>
#include <vector>
#include <stdexcept>
using namespace std;
vector<string> in2post(vector<string>);
vector<string> in2pre(vector<string>);
vector<string> post2in(vector<string>);
vector<string> pre2in(vector<string>);
vector<string> getListOfOps(string);
void printTerm(vector<string>);
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
             << "4. Exit." << endl
             << "Enter your selection: ";
        int input;
        cin >> input;
        if (input == 4)
            return 0;

        cout << "Enter your arithmetic term: ";
        cin.ignore();
        string term;
        getline(cin, term);
        vector<string> queue;
        try
        {
            queue = getListOfOps(term);
        }
        catch (const invalid_argument &ex)
        {
            cerr << ex.what() << endl;
            return 1;
        }
        printTerm(queue);

//        vector<string> pre_2_in = pre2in(queue);
//        vector<string> post_2_in = post2in(queue);
//        vector<string> in_2_pre = in2pre(queue);
//        vector<string> in_2_post = in2post(queue);
//        vector<string> pre_2_post = in2post(pre_2_in);
//        vector<string> post_2_pre = in2pre(post_2_in);

//        switch (input)
//        {
//        case 1:
//            cout << "The equivalent infix term: ";
//            printTerm(pre_2_in);
//            cout << "The equivalent postfix term: ";
//            printTerm(pre_2_post);
//            break;
//        case 2:
//            cout << "The equivalent prefix term: ";
//            printTerm(in_2_pre);
//            cout << "The equivalent postfix term: ";
//            printTerm(in_2_post);
//            break;
//        case 3:
//            cout << "The equivalent prefix term: ";
//            printTerm(post_2_pre);
//            cout << "The equivalent infix term: ";
//            printTerm(post_2_in);
//            break;
//        default:
//            cout << "WRONG Selection!!!" << endl;
//            break;
//        }
        cout << pressKey;
        cin.get();
    } while (true);
    return 0;
}
vector<string> getListOfOps(string str)
{
    vector<string> result;
    string tmp = "";
    short openParantheses = 0;
    for (int i = 0; i < str.size(); i++)
    {
        char localTmp = str[i];
        string lastOp = "";
        if (result.size() > 0)
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
                if (result.size() == 0)
                    throw invalid_argument("operand in the beginning of the input at position " + i);
                else if (lastOp == "+" || lastOp == "-" ||
                         lastOp == "*" || lastOp == "/")
                    throw invalid_argument("operand after operand at position " + i);
                else if (lastOp == "(")
                    throw invalid_argument("operand after '(' at position " + i);
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
    if (openParantheses > 0)
        throw invalid_argument("number of '(' more that ')' at the end of the input");
    return result;
}

void printTerm(vector<string> trm)
{
    for(vector<string>::iterator iter = trm.begin(); iter != trm.end(); iter++)
        cout << *iter << setw(2);
    cout << endl;
}

//vector<string> in2post(vector<string> trm)
//{
//    vector<string> trm_post;
//    char stack[100];
//    int stackCounter = 0;
//    for (int i = 0; i < trm.size(); i++)
//    {
//        string a = trm[i];
//        int num = NULL;
//        try
//        {
//            num = stoi(a);
//        }
//        catch (...)
//        {

//        }
//        if (a == "+" || a == "-" || a == "*" ||
//                a == "/" || a == "(" || a == ")")
//        {
//            if (stackCounter == 0)
//                stack[stackCounter++] = trm[i];
//            else
//            {
//                int c = stack[stackCounter];
//                if (a == 40 || a == 94)
//                    stack[++stackCounter] = trm[i];
//                else if (a == 43 || a == 45 || a == 42 || a == 47)
//                {
//                    if (c == 42 || c == 47 || c == 94)
//                    {
//                        while (c != 43 && c != 45 && c != 40 && stackCounter != 0)
//                        {
//                            trm_post += stack[stackCounter--];
//                            c = stack[stackCounter];
//                        }
//                        stack[++stackCounter] = trm[i];
//                    }
//                    else
//                        stack[++stackCounter] = trm[i];
//                }
//                else if (a == 41)
//                {
//                    while (c != 40 && stackCounter != 0)
//                    {
//                        trm_post += stack[stackCounter--];
//                        c = stack[stackCounter];
//                    }
//                    stackCounter--;
//                }
//            }
//        }
//    }
//    while (stackCounter != 0)
//    {
//        int c = stack[stackCounter];
//        if (c != 40)
//        {
//            trm_post += stack[stackCounter--];
//        }
//        else
//        {
//            stackCounter--;
//            trm_post += stack[stackCounter--];
//        }
//    }
//    return trm_post;
//}
//string in2pre(string trm)
//{
//    string trm_pre, temp2, temp1, stack_operand[100];
//    char stack_operation[100];
//    int  counter_operand = 0, counter_operation = 0;
//    stack_operand[counter_operand] = "";
//    for (int i = 0; i < trm.length(); i++)
//    {
//        int a = trm[i];
//        if ((a >= 97 && a <= 122) || (a >= 65 && a <= 90))
//        {
//            ++counter_operand;
//            stack_operand[counter_operand] = trm[i];
//        }
//        else if (a == 40 || a == 94 || a == 43 || a == 45 || a == 42 || a == 47 || a == 41)
//        {
//            if (counter_operation == 0)
//                stack_operation[++counter_operation] = trm[i];
//            else
//            {
//                int c = stack_operation[counter_operation];
//                if (a == 40 || a == 94)
//                    stack_operation[++counter_operation] = trm[i];
//                else if (a == 43 || a == 45 || a == 42 || a == 47)
//                {
//                    if (c == 42 || c == 47 || c == 94)
//                    {
//                        temp2 = stack_operand[counter_operand--];
//                        temp1 = stack_operand[counter_operand--];
//                        stack_operand[++counter_operand] = stack_operation[counter_operation--];
//                        stack_operand[counter_operand] += temp1;
//                        stack_operand[counter_operand] += temp2;
//                        stack_operation[++counter_operation] = trm[i];
//                    }
//                    else
//                        stack_operation[++counter_operation] = trm[i];
//                }
//                else if (a == 41)
//                {
//                    while (c != 40 && counter_operation != 0)
//                    {
//                        temp2 = stack_operand[counter_operand--];
//                        temp1 = stack_operand[counter_operand--];
//                        stack_operand[++counter_operand] = stack_operation[counter_operation--];
//                        stack_operand[counter_operand] += temp1;
//                        stack_operand[counter_operand] += temp2;
//                        c = stack_operation[counter_operation];
//                    }
//                    counter_operation--;
//                }
//            }
//        }
//    }
//    while (counter_operation != 0)
//    {
//        int c = stack_operation[counter_operation];
//        if (c != 40)
//        {
//            temp2 = stack_operand[counter_operand--];
//            temp1 = stack_operand[counter_operand--];
//            stack_operand[++counter_operand] = stack_operation[counter_operation--];
//            stack_operand[counter_operand] += temp1;
//            stack_operand[counter_operand] += temp2;
//        }
//        else
//        {
//            counter_operation--;
//        }
//    }
//    trm_pre = stack_operand[counter_operand];
//    return trm_pre;
//}
//string post2in(string trm)
//{
//    string trm_in, stack[100], temp1, temp2;
//    int counter = 0;
//    for (int i = 0; i < trm.length(); i++)
//    {
//        int a = trm[i];
//        if (a >= 48 && a <= 57)
//        {
//            return "CAN'T CONTINUE WITH DIGITS!!!";
//        }
//        else if ((a >= 97 && a <= 122) || (a >= 65 && a <= 90))
//        {
//            stack[++counter] = trm[i];
//        }
//        else
//        {
//            temp2 = stack[counter--];
//            temp2 += ")";
//            temp1 = "(";
//            temp1 += stack[counter--];
//            ++counter;
//            stack[counter] = temp1;
//            stack[counter] += trm[i];
//            stack[counter] += temp2;
//        }
//    }
//    trm_in = stack[1];
//    return trm_in;
//}
//string pre2in(vector<string> trm)
//{
//    string trm_in, stack_operand[100], temp1, temp2, stack_operation[100];
//    int counter_operation = 0, counter_operand = 0;
//    for (int i = 0; i < trm.length(); i++)
//    {
//        int a = trm[i], b = trm[i - 1];
//        if (a >= 48 && a <= 57)
//        {
//            return "CAN'T CONTINUE WITH DIGITS!!!";
//        }
//        else if ((a >= 97 && a <= 122) || (a >= 65 && a <= 90))
//        {
//            stack_operand[++counter_operand] = trm[i];
//            if ((b >= 97 && b <= 122) || (b >= 65 && b <= 90))
//            {
//                temp2 = stack_operand[counter_operand--];
//                temp2 += ")";
//                temp1 = "(";
//                temp1 += stack_operand[counter_operand--];
//                temp1 += stack_operation[counter_operation--];
//                stack_operand[++counter_operand] = temp1 + temp2;
//            }
//        }
//        else
//        {
//            stack_operation[++counter_operation] = trm[i];
//        }
//    }
//    while (counter_operand != 0)
//    {
//        temp2 = stack_operand[counter_operand--];
//        temp2 += ")";
//        temp1 = "(";
//        temp1 += stack_operand[counter_operand--];
//        temp1 += stack_operation[counter_operation--];
//        stack_operand[++counter_operand] = temp1 + temp2;
//    }
//    trm_in = stack_operand[counter_operand];
//    return trm_in;
//}
