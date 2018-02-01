#include<iostream>
#include<conio.h>
#include<string.h>
#include<string>
#include<iomanip>
#include<cstdio>
using namespace std;
string in2post(string);
string in2pre(string);
string post2in(string);
string pre2in(string);
int main()
{
	string head(76, '*'), middle(25, '*');
	cout << head << endl;
	cout << middle << " Prefix   Infix   Postfix " << middle << endl;
	cout << head << endl;
	int input;
	string term;
	bool y = 1;
	do
	{
		system("cls");
		cout << head << endl;
		cout << middle << " Prefix   Infix   Postfix " << middle << endl;
		cout << head << endl;
		cout << "1. I want to enter a prefix term." << endl
			<< "2. I want to enter an infix term." << endl
			<< "3. I want to enter a postfix term." << endl
			<< "10. Exit." << endl
			<< "Enter your selection: ";
		cin >> input;
		if (input == 10)
			y = 0;
		if (y)
		{
			cout << "Enter your arithmetic term: ";
			cin >> term;
			string pre_2_in = pre2in(term);
			string post_2_in = post2in(term);
			string in_2_pre = in2pre(term);
			string in_2_post = in2post(term);
			string pre_2_post = in2post(pre_2_in);
			string post_2_pre = in2pre(post_2_in);
			switch (input)
			{
			case 1:
				system("cls");
				cout << head << endl;
				cout << middle << " Prefix   Infix   Postfix " << middle << endl;
				cout << head << endl;
				cout << "The equivalent infix term: " << pre_2_in << endl;
				cout << "The equivalent postfix term: " << pre_2_post << endl;
				_getch();
				break;
			case 2:
				system("cls");
				cout << head << endl;
				cout << middle << " Prefix   Infix   Postfix " << middle << endl;
				cout << head << endl;
				cout << "The equivalent prefix term: " << in_2_pre << endl;
				cout << "The equivalent postfix term: " << in_2_post << endl;
				_getch();
				break;
			case 3:
				system("cls");
				cout << head << endl;
				cout << middle << " Prefix   Infix   Postfix " << middle << endl;
				cout << head << endl;
				cout << "The equivalent prefix term: " << post_2_pre << endl;
				cout << "The equivalent infix term: " << post_2_in << endl;
				_getch();
				break;
			case 10:
				y = 0;
				break;
			default:
				cout << "WRONG Selection!!!" << endl;
				_getch();
				break;
			}
		}
	} while (y);
	return 0;
}
string in2post(string trm)
{
	string trm_post;
	char stack[100];
	int counter = 0;
	for (int i = 0; i < trm.length(); i++)
	{
		int a = trm[i];
		if ((a >= 48 && a <= 57) || (a >= 97 && a <= 122) || (a >= 65 && a <= 90))
		{
			trm_post += trm[i];
		}
		else
		{
			if (counter == 0)
				stack[++counter] = trm[i];
			else
			{
				int c = stack[counter];
				if (a == 40 || a == 94)
					stack[++counter] = trm[i];
				else if (a == 43 || a == 45 || a == 42 || a == 47)
				{
					if (c == 42 || c == 47 || c == 94)
					{
						while (c != 43 && c != 45 && c != 40 && counter != 0)
						{
							trm_post += stack[counter--];
							c = stack[counter];
						}
						stack[++counter] = trm[i];
					}
					else
						stack[++counter] = trm[i];
				}
				else if (a == 41)
				{
					while (c != 40 && counter != 0)
					{
						trm_post += stack[counter--];
						c = stack[counter];
					}
					counter--;
				}
			}
		}
	}
	while (counter != 0)
	{
		int c = stack[counter];
		if (c != 40)
		{
			trm_post += stack[counter--];
		}
		else
		{
			counter--;
			trm_post += stack[counter--];
		}
	}
	return trm_post;
}
string in2pre(string trm)
{
	string trm_pre, temp2, temp1, stack_operand[100];
	char stack_operation[100];
	int  counter_operand = 0, counter_operation = 0;
	stack_operand[counter_operand] = "";
	for (int i = 0; i < trm.length(); i++)
	{
		int a = trm[i];
		if ((a >= 97 && a <= 122) || (a >= 65 && a <= 90))
		{
			++counter_operand;
			stack_operand[counter_operand] = trm[i];
		}
		else if (a == 40 || a == 94 || a == 43 || a == 45 || a == 42 || a == 47 || a == 41)
		{
			if (counter_operation == 0)
				stack_operation[++counter_operation] = trm[i];
			else
			{
				int c = stack_operation[counter_operation];
				if (a == 40 || a == 94)
					stack_operation[++counter_operation] = trm[i];
				else if (a == 43 || a == 45 || a == 42 || a == 47)
				{
					if (c == 42 || c == 47 || c == 94)
					{
						temp2 = stack_operand[counter_operand--];
						temp1 = stack_operand[counter_operand--];
						stack_operand[++counter_operand] = stack_operation[counter_operation--];
						stack_operand[counter_operand] += temp1;
						stack_operand[counter_operand] += temp2;
						stack_operation[++counter_operation] = trm[i];
					}
					else
						stack_operation[++counter_operation] = trm[i];
				}
				else if (a == 41)
				{
					while (c != 40 && counter_operation != 0)
					{
						temp2 = stack_operand[counter_operand--];
						temp1 = stack_operand[counter_operand--];
						stack_operand[++counter_operand] = stack_operation[counter_operation--];
						stack_operand[counter_operand] += temp1;
						stack_operand[counter_operand] += temp2;
						c = stack_operation[counter_operation];
					}
					counter_operation--;
				}
			}
		}
	}
	while (counter_operation != 0)
	{
		int c = stack_operation[counter_operation];
		if (c != 40)
		{
			temp2 = stack_operand[counter_operand--];
			temp1 = stack_operand[counter_operand--];
			stack_operand[++counter_operand] = stack_operation[counter_operation--];
			stack_operand[counter_operand] += temp1;
			stack_operand[counter_operand] += temp2;
		}
		else
		{
			counter_operation--;
		}
	}
	trm_pre = stack_operand[counter_operand];
	return trm_pre;
}
string post2in(string trm)
{
	string trm_in, stack[100], temp1, temp2;
	int counter = 0;
	for (int i = 0; i < trm.length(); i++)
	{
		int a = trm[i];
		if (a >= 48 && a <= 57)
		{
			return "CAN'T CONTINUE WITH DIGITS!!!";
		}
		else if ((a >= 97 && a <= 122) || (a >= 65 && a <= 90))
		{
			stack[++counter] = trm[i];
		}
		else
		{
			temp2 = stack[counter--];
			temp2 += ")";
			temp1 = "(";
			temp1 += stack[counter--];
			++counter;
			stack[counter] = temp1;
			stack[counter] += trm[i];
			stack[counter] += temp2;
		}
	}
	trm_in = stack[1];
	return trm_in;
}
string pre2in(string trm)
{
	string trm_in, stack_operand[100], temp1, temp2, stack_operation[100];
	int counter_operation = 0, counter_operand = 0;
	for (int i = 0; i < trm.length(); i++)
	{
		int a = trm[i], b = trm[i - 1];
		if (a >= 48 && a <= 57)
		{
			return "CAN'T CONTINUE WITH DIGITS!!!";
		}
		else if ((a >= 97 && a <= 122) || (a >= 65 && a <= 90))
		{
			stack_operand[++counter_operand] = trm[i];
			if ((b >= 97 && b <= 122) || (b >= 65 && b <= 90))
			{
				temp2 = stack_operand[counter_operand--];
				temp2 += ")";
				temp1 = "(";
				temp1 += stack_operand[counter_operand--];
				temp1 += stack_operation[counter_operation--];
				stack_operand[++counter_operand] = temp1 + temp2;
			}
		}
		else
		{
			stack_operation[++counter_operation] = trm[i];
		}
	}
	while (counter_operand != 0)
	{
		temp2 = stack_operand[counter_operand--];
		temp2 += ")";
		temp1 = "(";
		temp1 += stack_operand[counter_operand--];
		temp1 += stack_operation[counter_operation--];
		stack_operand[++counter_operand] = temp1 + temp2;
	}
	trm_in = stack_operand[counter_operand];
	return trm_in;
}