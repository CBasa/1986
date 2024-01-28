#include "Interaction.h"

Interaction::Interaction()
{
	_description = "default";
	_outcome = "default";
}

Interaction::Interaction(std::string name, std::string description, std::string outcome)
{
	_name = name;
	_outcome = outcome;
	_description = description;
}

std::string Interaction::getName()
{
	return _name;
}

std::string Interaction::getDescription()
{
	return _description;
}

std::string Interaction::getOutcome()
{
	return _outcome;
}

void Interaction::setOutcome(std::string outcome)
{
	_outcome = outcome;
}


