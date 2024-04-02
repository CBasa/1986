#pragma once
#include <string>

class NPC
{
public:
	NPC(std::string name, std::string description, std::string weakness);

	std::string fight(std::string attackingWeapon);
	std::string speak();


private:
	std::string _name;
	std::string _description;
	std::string _weakness;
};

