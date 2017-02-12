#include "tokenize.hpp"



bool tokenize(string expression)
{
	string parseExpression = "";

	vector<char> token;
	
	for (unsigned int i = 0; i < expression.size(); ++i)
	{
		if (expression[i] == 40)
			parseExpression = parseExpression + " ( ";
		else if (expression[i] == 41)
			parseExpression = parseExpression + " ) ";
		else
			parseExpression = parseExpression + expression[i];
	}

	cout << "Expression: " << expression << endl;
	cout << "Parsed Expression: " << parseExpression << endl;

	expression = parseExpression;

	//maybe good time to start a switch case?
	//if i see define start looping through until I see a variable, once i get a variable keep parsing and just moving deeper and deeper into state machine

	for (unsigned int i = 0; i < expression.size(); ++i)
	{
		if (expression[i] == 100 && expression.substr(i, 6) == "define" && expression[i + 6] == ' ' &&
			(expression[i - 1] == ' ' || expression[i - 1] == '(')) //checking for define
			i += 6;

		else if ((expression[i] >= 65 && expression[i] <= 90) || (expression[i] >= 97 && expression[i] <= 122))
		{

		}
	}



	return false;
}

int main(int argc, char *argv[])
{
	string expression; 
	expression = argv[1];

	tokenize(expression);

	return 0;
}