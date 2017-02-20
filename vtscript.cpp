#include "interpreter.hpp"
#include <fstream>

#include <string>

int main(int argc, char *argv[])
{
	string expression;
	string argument;
	argument = argv[1];

	if (argc == 3 && argument == "-e")
	{
		expression = argv[2];

		std::istringstream ss(expression);
		Interpreter a;

		if (a.parse(ss)) {
			try {
				a.eval().outputFinalAnswer();
			}
			catch (InterpreterSemanticError &error) {
				std::cout << error.what() << std::endl;
			}
		}
		else
			std::cerr << "Error: Parsing failed.";
	}

	else if (argc == 2)
	{
		string filename = argv[1];
		string trash;
		string finalExpression = "";

		std::ifstream istream(filename);

		while (!istream.fail())
		{
			std::getline(istream, expression, ';');
			finalExpression += expression;
			std::getline(istream, trash);
		}

		cout << finalExpression << endl;

	}

	return 0;
}