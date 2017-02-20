#include "interpreter.hpp"
#include <fstream>

#include <string>

int main(int argc, char *argv[])
{
	string expression;
	string argument;
	

	if (argc == 3)
	{
		argument = argv[1];
		if (argument == "-e") {

			expression = argv[2];

			std::istringstream ss(expression);
			Interpreter a;

			if (a.parse(ss)) {
				try {
					a.eval().outputFinalAnswer();
				}
				catch (InterpreterSemanticError &error) {
					std::cout << error.what() << std::endl;
					return EXIT_FAILURE;
				}
			}
			else {
				std::cerr << "Error: Parsing failed.";
				return EXIT_FAILURE;
			}
		}
	}

	else if (argc == 2)
	{
		string filename = argv[1];
		string initialExpression = "";
		string finalExpression = "";

		std::ifstream instream(filename);
		getline(instream, initialExpression);
		while (!instream.fail()){
			finalExpression.append(initialExpression.substr(0, initialExpression.find(';')));
			finalExpression.append(" ");
			getline(instream, initialExpression);
		}
		std::cout << finalExpression << endl;

		std::istringstream ss(finalExpression);
		Interpreter a;

		if (a.parse(ss)) {
			try {
				a.eval().outputFinalAnswer();
			}
			catch (InterpreterSemanticError &error) {
				std::cout << error.what() << std::endl;
				return EXIT_FAILURE;
			}
		}
		else {
			std::cerr << "Error: Parsing failed.";
			return EXIT_FAILURE;
		}

	}
	
	else if (argc == 1)
	{
		std::string b;
		Interpreter a;

		while (1)
		{
			std::cout << "vtscript> ";
			getline(cin, b);
			std::istringstream ss(b);

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

	}
	else
		std::cerr << "Error: Invalid Arguments." << std::endl;

	return 0;
}