#include "interpreter.hpp"
#include "environment.hpp"

Interpreter::Interpreter(){
	//environment = new Environment();
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

string Interpreter::streamToString(std::istream & in)
{
	/*string tokenString;
	char buffer[4096];
	while (in.read(buffer, sizeof(buffer)))
		tokenString.append(buffer, sizeof(buffer));
	tokenString.append(buffer, in.gcount());*/
	string tokenString(std::istreambuf_iterator<char>(in), {});
	return tokenString;
}