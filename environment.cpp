#include "environment.hpp"

Environment::Environment()
{
	Atom atom;
	setVariable("begin", atom);
}

bool Environment::setVariable(std::string aString, Atom envAtom)
{
	if (varMap.count(aString) > 0) {
		throw InterpreterSemanticError("Error: Variable already defined.");
		return false;
	}
	else {
		varMap.insert(std::pair<std::string, Atom>(aString, envAtom));
			return true;
	}
}

Atom Environment::findVar(std::string aString)
{
	return varMap[aString];
}
