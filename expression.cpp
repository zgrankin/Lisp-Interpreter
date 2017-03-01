#include "expression.hpp"
#include "environment.hpp"

#include <iostream>

Expression::Expression()
{

}

Expression::Expression(bool value)
{

}

Expression::Expression(double value)
{

}

Expression::Expression(const std::string & value)
{

}

void Expression::defineMethod()
{
		if (atom.var == "+") {
			for (unsigned int i = 0; i < children.size(); i++) {
				if (children[i]->atom.atomType == NumberType) {
					atom.number += children[i]->atom.number;
					atom.atomType = NumberType;
				}
				else
					throw InterpreterSemanticError("Error: Improper arguments for addition.");
			}
		}
		else if (atom.var == "*") {
			atom.number = 1;
			for (unsigned int i = 0; i < children.size(); i++) {
				if (children[i]->atom.atomType == NumberType) {
					atom.number *= children[i]->atom.number;
					atom.atomType = NumberType;
				}
				else
					throw InterpreterSemanticError("Error: Improper arguments for multiplication.");
			}
		}

		else if (atom.var == "and") {
			atom.truthValue = true;
			for (unsigned int i = 0; i < children.size(); i++) {
				if (children[i]->atom.atomType == BoolType) {
					atom.truthValue &= children[i]->atom.truthValue;
					atom.atomType = BoolType;
				}
				else
					throw InterpreterSemanticError("Error: Improper arguments for logic operator \"and\".");
			}
		}
		else if (atom.var == "or") {
			atom.truthValue = false;
			for (unsigned int i = 0; i < children.size(); i++) {
				if (children[i]->atom.atomType == BoolType) {
					atom.truthValue |= children[i]->atom.truthValue;
					atom.atomType = BoolType;
				}
				else
					throw InterpreterSemanticError("Error: Improper arguments for logic operator \"or\".");
			}
		}
		else if (atom.var == "-") {
			if (children.size() == 2 && children[0]->atom.atomType == NumberType && children[1]->atom.atomType == NumberType) {
				atom.number = children[0]->atom.number - children[1]->atom.number;
				atom.atomType = NumberType;
			}
			else if (children.size() == 1 && children[0]->atom.atomType == NumberType) {
				atom.number = children[0]->atom.number * -1;
				atom.atomType = NumberType;
			}
			else
				throw InterpreterSemanticError("Error: Improper arguments for subtraction.");
		}
		else if (atom.var == "/") {
			if (children.size() == 2 && children[0]->atom.atomType == NumberType && children[1]->atom.atomType == NumberType) {
				atom.number = children[0]->atom.number / children[1]->atom.number;
				atom.atomType = NumberType;
			}
			else
				throw InterpreterSemanticError("Error: Improper arguments for division.");
		}

		else if (atom.var == "<") {
			if (children.size() == 2 && children[0]->atom.atomType == NumberType && children[1]->atom.atomType == NumberType) {
				children[0]->atom.number < children[1]->atom.number ? atom.truthValue = true : atom.truthValue = false;
				atom.atomType = BoolType;
			}
			else
				throw InterpreterSemanticError("Error: Improper arguments for logic operator \"<\".");
		}
		else if (atom.var == "<=") {
			if (children.size() == 2 && children[0]->atom.atomType == NumberType && children[1]->atom.atomType == NumberType) {
				children[0]->atom.number <= children[1]->atom.number ? atom.truthValue = true : atom.truthValue = false;
				atom.atomType = BoolType;
			}
			else
				throw InterpreterSemanticError("Error: Improper arguments for logic operator \"<=\".");
		}
		else if (atom.var == ">") {
			if (children.size() == 2 && children[0]->atom.atomType == NumberType && children[1]->atom.atomType == NumberType) {
				children[0]->atom.number > children[1]->atom.number ? atom.truthValue = true : atom.truthValue = false;
				atom.atomType = BoolType;
			}
			else
				throw InterpreterSemanticError("Error: Improper arguments for logic operator \">\".");
		}
		else if (atom.var == ">=") {
			if (children.size() == 2 && children[0]->atom.atomType == NumberType && children[1]->atom.atomType == NumberType) {
				children[0]->atom.number >= children[1]->atom.number ? atom.truthValue = true : atom.truthValue = false;
				atom.atomType = BoolType;
			}
			else
				throw InterpreterSemanticError("Error: Improper arguments for logic operator \">=\".");
		}
		else if (atom.var == "=") {
			if (children.size() == 2 && children[0]->atom.atomType == NumberType && children[1]->atom.atomType == NumberType) {
				children[0]->atom.number == children[1]->atom.number ? atom.truthValue = true : atom.truthValue = false;
				atom.atomType = BoolType;
			}
			else
				throw InterpreterSemanticError("Error: Improper arguments for logic operator \"=\".");
		}
		else if (atom.var == "not") {
			if (children.size() == 1 && children[0]->atom.atomType == BoolType) {
				atom.truthValue = !children[0]->atom.truthValue;
				atom.atomType = BoolType;
			}
			else
				throw InterpreterSemanticError("Error: Improper arguments for logic operator \"not\".");
		}
		else if (atom.atomType == SymbolType)
		{
			atom = environment->findVar(atom.var);
		}
		//hi
}

Expression Expression::evaluateTree()
{
	if (atom.var == "begin"){
		if (children.size() == 0)
			throw InterpreterSemanticError("Error: Cannot evaluate.");
		for (unsigned int i = 0; i < children.size(); i++)
			children[i]->evaluateTree();
		atom.atomType = children[children.size() - 1]->atom.atomType;
		atom.number = children[children.size() - 1]->atom.number;
		atom.truthValue = children[children.size() - 1]->atom.truthValue;
		atom.var = children[children.size() - 1]->atom.var;
	}
	else if (atom.var == "define"){
		if (children.size() == 2 && children[0]->atom.atomType == SymbolType)
		{
			children[1]->evaluateTree();
			if (children[1]->atom.atomType == BoolType || children[1]->atom.atomType == NumberType)
				environment->setVariable(children[0]->atom.var, children[1]->atom);
			atom = environment->findVar(children[0]->atom.var);
		}
		else
			throw InterpreterSemanticError("Error: Cannot evaluate.");
	}
	else if (atom.var == "if"){
		children[0]->evaluateTree();
		if (children[0]->atom.atomType == BoolType)
		{
			if (children[0]->atom.truthValue == true)
			{
				children[1]->evaluateTree();
				atom.atomType = children[children.size() - 1]->atom.atomType;
				atom.number = children[children.size() - 1]->atom.number;
				atom.truthValue = children[children.size() - 1]->atom.truthValue;
				atom.var = children[children.size() - 1]->atom.var;
			}
			else if (children[0]->atom.truthValue == false)
			{
				children[2]->evaluateTree();
				atom.atomType = children[children.size() - 1]->atom.atomType;
				atom.number = children[children.size() - 1]->atom.number;
				atom.truthValue = children[children.size() - 1]->atom.truthValue;
				atom.var = children[children.size() - 1]->atom.var;
			}
		}
	}

	else// if (atom.atomType == SymbolType)
	{
		for (unsigned int i = 0; i < children.size(); i++){
			children[i]->evaluateTree();
		}
		defineMethod();
	}

	/*std::cout << "Number Result: " << atom.number << std::endl;
	std::cout << "Bool Result: ";
	if (atom.truthValue == true) std::cout << "True" << std::endl;
	else std::cout << "False" << std::endl;*/

	return *this;
}

void Expression::outputFinalAnswer()
{
	if (atom.atomType == NumberType)
		cout << "(" << atom.number << ")" << endl;
	
	else if (atom.atomType == SymbolType)
		cout << "(" << atom.var << ")" << endl;

	else if (atom.atomType == BoolType)
	{
		if (atom.truthValue == true)
			cout << "(" << "True" << ")" << endl;
		else if (atom.truthValue == false)
			cout << "(" << "False" << ")" << endl;
	}
		
	
}

bool Expression::operator==(const Expression & exp) const noexcept
{
	if (atom.atomType == exp.atom.atomType && atom.atomType == BoolType)
	{
		if (atom.truthValue == exp.atom.truthValue && children.size() == exp.children.size())
			return true;
		else
			return false;
	}

	else if (atom.atomType == exp.atom.atomType && atom.atomType == NumberType)
	{
		if (atom.number == exp.atom.number && children.size() == exp.children.size())
			return true;
		else
			return false;
	}

	else if (atom.atomType == exp.atom.atomType && atom.atomType == SymbolType)
	{
		if (atom.var == exp.atom.var && children.size() == exp.children.size())
			return true;
		else
			return false;
	}

	return false;
}
