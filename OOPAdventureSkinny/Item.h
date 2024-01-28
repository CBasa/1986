#pragma once
#include <map>
#include <string>

#include "Interaction.h"

class Item
{
public:
	Item();
	Item(std::string name, std::string description);

	std::string getName();
	std::string getDescription();
	std::string getAsciiArt();

	void setName(std::string name);
	void setDescription(std::string description);

	std::map<std::string, Interaction*> linkedInteractions;

private:
	std::string _name;
	std::string _description;
	std::string _asciiArt;

};



class PlayerItem : public Item
{
public:
	PlayerItem(const std::string& name, const std::string& description, bool heldByPlayer);
	PlayerItem(std::string name, std::string description, bool heldByPlayer, std::map<std::string, Interaction*> linkedInteractions);

	/*bool getHeldByPlayer();
	void setHeldByPlayer(bool heldByPlayer);*/

private:
	/*bool _heldByPlayer;*/
};


class FixedItem : public Item
{
public:
	FixedItem(std::string name, std::string description);
private:

};

