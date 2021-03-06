#include "catch.hpp"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include "interpreter_semantic_error.hpp"
#include "interpreter.hpp"
#include "expression.hpp"
#include "test_config.hpp"

Expression runScript(const std::string & program) {

	std::istringstream iss(program);

	Interpreter interp;

	bool ok = interp.parse(iss);
	if (!ok) {
		std::cerr << "Failed to parse: " << program << std::endl;
	}
	REQUIRE(ok);

	Expression result;
	result = interp.eval();

	return result;
}

TEST_CASE("Test Expression M-ary Operators Invalid Input", "[interpreter]") {

	std::string program = "(+ True False)";
	std::istringstream iss(program);
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);
	program = "(+)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);

	program = "(* True False)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);
	program = "(*)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);

	program = "(and 1 2)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);
	program = "(and)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);

	program = "(or 1 2)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);
	program = "(or)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);

	Interpreter interp;

	bool ok = interp.parse(iss);

	REQUIRE(ok);
}

TEST_CASE("Test Expression Binary Operators Invalid Input", "[interpreter]") {

	std::string program = "(- True False)";
	std::istringstream iss(program);
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);
	program = "(- 1 2 3)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);
	program = "(-)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);

	program = "(/ True False)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);
	program = "(/ 1 2 3)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);
	program = "(/ 1)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);
	program = "(/)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);

	program = "(< 1 2 3)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);
	program = "(< True False)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);
	program = "(< 1)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);
	program = "(<)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);

	program = "(<= 1 2 3)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);
	program = "(<= True False)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);
	program = "(<= 1)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);
	program = "(<=)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);

	program = "(> 1 2 3)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);
	program = "(> True False)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);
	program = "(> 1)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);
	program = "(>)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);

	program = "(>= 1 2 3)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);
	program = "(>= True False)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);
	program = "(>= 1)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);
	program = "(>=)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);

	program = "(= 1 2 3)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);
	program = "(= True False)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);
	program = "(= 1)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);
	program = "(=)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);

	Interpreter interp;

	bool ok = interp.parse(iss);

	REQUIRE(ok);
}

TEST_CASE("Test Expression Special Forms Invalid Input", "[interpreter]") {

	std::string program = "(begin a b)";
	std::istringstream iss(program);
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);
	program = "(begin)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);

	program = "(if (+ 1 2) 4 5)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);
	program = "(if (< 1 2) 4 5 6)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);
	program = "(if)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);

	program = "(define 1 a)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);
	program = "(define a 1 (+ 1 2))";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);
	program = "(define)";
	REQUIRE_THROWS_AS(runScript(program), InterpreterSemanticError);

	Interpreter interp;

	bool ok = interp.parse(iss);

	REQUIRE(ok);
}

TEST_CASE("Test Special Case Number Input", "[interpreter]") {

	std::string program = "(.5)";
	REQUIRE(runScript(program).atom.atomType == NumberType);
	program = "(0.5)";
	REQUIRE(runScript(program).atom.atomType == NumberType);
	program = "(0.5e5)";
	REQUIRE(runScript(program).atom.atomType == NumberType);
	program = "(-4e-5)";
	REQUIRE(runScript(program).atom.atomType == NumberType);
	program = "(-4-e5)";

	std::istringstream iss(program);
	Interpreter interp;
	bool ok = interp.parse(iss);

	REQUIRE(!ok);
	
}