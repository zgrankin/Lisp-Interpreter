#include "interpreter.hpp"

Interpreter::Interpreter()
{
}

bool Interpreter::parse(std::istream & expression) noexcept
{
	string tokenString = streamToString(expression);
	vector<string> token = tree.tokenize(tokenString);
	tree.buildAST(token);
	return false;
}

Expression Interpreter::eval()
{
	//return tree.head->evalulateTree();
	return true;
}

string Interpreter::streamToString(std::istream & in)
{
	string tokenString;
	char buffer[4096];
	while (in.read(buffer, sizeof(buffer)))
		tokenString.append(buffer, sizeof(buffer));
	tokenString.append(buffer, in.gcount());
	return tokenString;
}


int main(int argc, char *argv[])
{
	string expression;
	expression = argv[1];

	std::istringstream ss(expression);
	Interpreter a;
	a.parse(ss);


	return 0;
}