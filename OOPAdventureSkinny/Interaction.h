#pragma once
#include <string>

class Interaction
{
public:
	Interaction();
	Interaction(std::string name, std::string description, std::string outcome);
	std::string getName();
	std::string getDescription();
	std::string getOutcome();

	void setOutcome(std::string outcome);
private:
	std::string _name;
	std::string _description;
	std::string _outcome;
};

