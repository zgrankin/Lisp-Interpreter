#include "interpreter.hpp"
#include "environment.hpp"

Interpreter::Interpreter()
{
	tree.environment = &theEnvironment;
}


bool Interpreter::parse(std::istream & expression) noexcept
{
	string tokenString = streamToString(expression);
	vector<string> token = tree.tokenize(tokenString);
	return tree.buildAST(token);
}

Expression Interpreter::eval()
{
	return tree.head->evaluateTree();
}

string Interpreter::streamToString(std::istream & expression)
{
	std::string tempExpression;
	std::string finalExpression;
	std::getline(expression, tempExpression);
	while (!expression.fail()) {
		if (tempExpression.find(';') != -1)
			finalExpression.append(tempExpression.substr(0, tempExpression.find(';')));
		else {
			finalExpression.append(tempExpression);
		}

		finalExpression.append(" ");
		std::getline(expression, tempExpression);
		//std::cout << finalExpression << endl;
	}

	return finalExpression;

	/*string tokenString;
	char buffer[4096];
	while (in.read(buffer, sizeof(buffer)))
		tokenString.append(buffer, sizeof(buffer));
	tokenString.append(buffer, in.gcount());*/
	//string tokenString(std::istreambuf_iterator<char>(in), {});
}

