#pragma once
#include <string>
#include <map>

#include "NPC.h"
#include "Player.h"

class Room
{
public:
	Room(std::string name, std::string description);
	std::string getName();
	std::string getDescription();


	std::map<std::string, NPC*> linkedNPCs;
	std::map<std::string, Room*> linkedRooms;
	std::map<std::string, Item*> linkedItems;
	std::map<std::string, Interaction*> linkedInteractions;

private:
	std::string _name;
	std::string _description;

};

