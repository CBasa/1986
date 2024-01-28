#include "NPC.h"

NPC::NPC(std::string name, std::string description, std::string weakness)
{
	_name = name;
	_description = description;
	_weakness = weakness;
}

std::string NPC::fight(std::string attackingWeapon)
{
	return std::string();
}

std::string NPC::speak()
{
	return std::string();
}
