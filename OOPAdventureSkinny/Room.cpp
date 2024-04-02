#include "Room.h"

Room::Room(std::string name, std::string description)
{
	_name = name;
	_description = description;
}

std::string Room::getName()
{
	return _name;
}

std::string Room::getDescription()
{
	return _description;
}
