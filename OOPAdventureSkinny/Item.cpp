#include "Item.h"

Item::Item()
{
	_name = "default name";
	_description = "default description";
}

Item::Item(std::string name, std::string description)
{
	_name = name;
	_description = description;
}

std::string Item::getName()
{
	return _name;
}

std::string Item::getDescription()
{
	return _description;
}

std::string Item::getAsciiArt()
{
	return std::string();
}

void Item::setName(std::string name)
{
	_name = name;
}

void Item::setDescription(std::string description)
{
	_description = description;
}

// Player Item
PlayerItem::PlayerItem(const std::string& name, const std::string& description, bool heldByPlayer)
{
	setName(name);
	setDescription(description);
	//setHeldByPlayer(heldByPlayer);
}

PlayerItem::PlayerItem(std::string name,  std::string description, bool heldByPlayer, std::map<std::string, Interaction*> linkedInteractions)
{
	setName(name);
	setDescription(description);
	//_heldByPlayer = heldByPlayer;
	linkedInteractions = linkedInteractions;
}

//bool PlayerItem::getHeldByPlayer()
//{
//	return _heldByPlayer;
//}
//
//void PlayerItem::setHeldByPlayer(bool heldByPlayer)
//{
//	_heldByPlayer = heldByPlayer;
//}

// Fixed Item
FixedItem::FixedItem(std::string name, std::string description)
{
	setName(name);
	setDescription(description);
}


