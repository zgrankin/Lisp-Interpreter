#include "tokenize.hpp"

//template<typename T>
template<typename T>
vector<string> Tokenize<T>::tokenize(string expression)
{
	vector<string> token;


	string expressionHolder = "";


	for (unsigned int i = 0; i < expression.size(); ++i) // add spaces around the parentheses for easier tokenizing
	{
		if (expression[i] == '(')
			expressionHolder = expressionHolder + " ( ";
		else if (expression[i] == ')')
			expressionHolder = expressionHolder + " ) ";
		else
			expressionHolder = expressionHolder + expression[i];
	}

	cout << "Expression: " << expression << endl;
	cout << "Parsed Expression: " << expressionHolder << endl;

	expression = expressionHolder;

	string newVar = "";
	for (unsigned int i = 0; i < expression.size(); ++i) // store into my vector 
	{
		if (expression[i] == ' ') { // string will be considered empty even filled with a space

			if (!newVar.empty())
			{
				token.push_back(newVar);
			}
			newVar = "";
		}

		else {
			newVar += expression[i]; //so now newVar is the first letter we read
		}
	}

	for (unsigned int i = 0; i < token.size(); ++i)
		cout << "This is the token: " << token[i] << endl;

	cout << endl;

	return token;
}

template<typename T>
bool Tokenize<T>::buildAST(vector<string> token)
{

	if (token[0] != "(") {
		cerr << "Expression could not be parsed. It did not start with a '('." << endl;
		return EXIT_FAILURE;
	}

	enum States { stateA, stateB, stateC, stateD, stateE };
	enum States currentState = stateA;

	unsigned int pos = 0;

	while (pos < token.size())
	{
		if (pos == 3)
		{
			int a;
			a = 0;
		}
		switch (currentState)
		{
		case stateA:
		{
			if (token[pos] == "(" && token[pos + 1] != ")") {
				node<T> *newNode = new node<T>;
				if (pos == 0) {
					newNode->parent = nullptr; head = newNode; tail = newNode; currentNode = newNode;
				}
				else {
					tail = newNode;
					tail->parent = currentNode;
					currentNode->children.push_back(tail);
					currentNode = newNode;
				}
				currentState = stateB;
				pos++;
			}

			else if (token[pos] == "(" && token[pos + 1] == ")")
			{
				cerr << "Parsing error: '(' was followed by ')'" << endl;
				return false;
			}

			else if (token[pos] == ")")
			{
				if (currentNode->parent != nullptr)
					currentNode = currentNode->parent;
				pos++;
				currentState = stateA;
			}

			else
			{
				node<T> *newNode = new node<T>;
				tail = newNode;
				tail->parent = currentNode;
				currentNode->children.push_back(tail);
				currentState = stateB;
			}
			
		}
		break;

		case stateB: // check for SymbolType
		{
			if (!isdigit(token[pos][0]) && token[pos][0] != '-') {
				tail->atomType = SymbolType;
				tail->data = token[pos];
				pos++;
				currentState = stateA;
			}

			else
				currentState = stateC;
		}
		break;

		case stateC: // check for NumberType
		{
			bool isNumber = true;
			for (unsigned int i = 0; i < token[pos].size(); i++) {
				if (!isdigit(token[pos][i]))
					isNumber = false;
			}

			if (isNumber == true)
			{
				tail->atomType = NumberType;
				tail->data = token[pos];
				pos++;
				currentState = stateA;
			}

			else
				currentState = stateD;
		}
		break;

		case stateD:
		{
			;
		}
		break;

		//case stateE:
		//break;
		}

	}

	traversePostOrder(head);

}

template <typename T>
void Tokenize<T>::traversePostOrder(node<string> *currentNode)
{
	for (int i = 0; i < currentNode->children.size(); i++)
	{
		traversePostOrder(currentNode->children[i]);
	}
	cout << currentNode->data << endl;
}


int main(int argc, char *argv[])
{
	string expression;
	expression = argv[1];

	Tokenize<string> m;

	vector<string> token = m.tokenize(expression);
	m.buildAST(token);

	return 0;
}



