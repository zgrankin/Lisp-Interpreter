#include "tokenize.hpp"

//template<typename T>
template<typename T>
vector<string> Tokenize<T>::tokenize(string expression)
{
	vector<string> token;


	string parseExpression = "";

	
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

	for (unsigned int i = 0; i < expression.size(); ++i) // store into my vector 
	{
		if (expression[i] == 100 && expression.substr(i, 6) == "define" && expression[i + 6] == ' ' &&
			(expression[i - 1] == ' ' || expression[i - 1] == '(' || expression[i-1] == ')')) //checking for define
		{
			i += 5; // bring it to last letter of define because it's going to increment once the loop starts again
			token.push_back("define");
		}

		// add more else if's to check for other word operators
		

		else if (((expression[i] >= 65 && expression[i] <= 90) || (expression[i] >= 97 && expression[i] <= 122)) && (expression[i-1] == ' ' || expression[i-1] == '(' || expression[i-1] == ')'))
		{
			string newVar = "";
			newVar += expression[i]; //so now newVar is the first letter we read
			++i; // move forward to next symbol
			while (((expression[i] >= 65 && expression[i] <= 90) || (expression[i] >= 97 && expression[i] <= 122)) && i < expression.size()) // is a letter following that letter?
			{
				newVar += expression[i];
				++i;
			}
			token.push_back(newVar);
		}

		else if ((expression[i] == '(' && expression[i + 1] != ')')) // ********** may need slight adjustment because only an operator can follow expression
			token.push_back("(");

		else if (expression[i] == ')') // ********** may need slight adjustment because only an operator can follow expression
			token.push_back(")");

		else if ((expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') && expression[i + 1] == ' ' && (expression[i-1] == ' ' || expression[i-1] == '(' || expression[i-1] == ')'))
		{
			string newVar = "";
			newVar += expression[i];
			token.push_back(newVar);
		}

		else if (expression[i] >= 48 && expression[i] <= 57 && (expression[i - 1] == ' ' || expression[i - 1] == '('))
		{
			string newVar = "";
			newVar += expression[i]; //so now newVar is the first letter we read
			++i; // move forward to next symbol
			while (expression[i] >= 48 && expression[i] <= 57 && i < expression.size()) // is a letter following that letter?
			{
				newVar += expression[i];
				++i;
			}
			token.push_back(newVar);
		}
	}

	for (unsigned int i = 0; i < token.size(); ++i)
		cout << token[i] << " ";

	cout << endl;

	return token;
}

//bool buildAST(vector<string> token)
//{
//	
//
//
//	if (token[0] != "(") {
//		cerr << "Expression was invalid. It did not start with a '('." << endl;
//		return EXIT_FAILURE;
//	}
//
//	enum States { stateA, stateB, stateC, stateD, stateE };
//	enum States currentState = stateA;
//
//	unsigned int pos = 0;
//
//	while (pos < token.size())
//	{
//		switch (currentState)
//		{
//		case stateA:
//			if (token[pos] == "(") {
//				node *newNode = new node;
//			}
//
//			currentState = stateB;
//
//			break;
//
//		case stateB:
//			if (token[pos] == "define")
//			{
//			}
//			else if (token[pos] == "+")
//			{
//				//newNode->data = "+";
//				//newNode->next = nullptr;
//			}
//			else if (token[pos] == "*")
//			{
//			}
//			else if (token[pos] == "/")
//			{
//			}
//			else if (token[pos] == "-")
//			{
//			}
//
//			currentState = stateC;
//			break;
//
//		case stateC:
//			node *newNode = new node;
//			//if (isdigit(token[pos[0]]) == true || token[pos[0]] == '-')
//			//{
//				newNode->nChildren;
//			//}
//			break;
//
//		//case stateD:
//			//break;
//
//		//case stateE:
//			//break;
//		}
//	}
//
//}
//

int main(int argc, char *argv[])
{
	string expression; 
	expression = argv[1];

	Tokenize<string> m;
	
	vector<string> token = m.tokenize(expression);
	//buildAST(token);

	return 0;
}



//void traversePostOrder(node<string> *curNode) {
//	for (int index = 0; index < curNode->children.size(), index++)
//	{
//		traversePostOrder(curNode->children[index]);
//	}
//	cout << curNode->data << endl;
//}