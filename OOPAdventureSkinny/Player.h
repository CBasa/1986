#pragma once
#include <map>
#include <string>

#include "Item.h"
#include "Room.h"

class Room;

class Player
{
public:
	Player();
	Player(std::string name, Room* startingRoom);

	std::string getName();
	std::string getGreatestFear();
	int getHealth();
	bool getHasKeycard();
	bool getlightSwitchOn();
	Room* getStartingRoom();

	void setName(std::string name);
	void setGreatestFear(std::string greatestFear);
	void setHasKeycard(bool hasKeycard);
	void setlightSwitchOn(bool lightSwitchOn);
	void reduceHealth(int damage);
	void increaseHealth(int heal);

	bool isAlive();

	// PLayer's bag inventory
	std::map<std::string, Item*> inventory;

private:
	std::string _name;
	std::string _greatestFear;
	int _health;
	bool _hasKeycard;
	bool _lightSwitchOn;
	bool _bookshelfSwitchUnlocked;
	Room* _startingRoom;
};

class Enemy : public Player
{
public:
	Enemy(std::string name, std::string description);

	void setWeakness(std::string weaponWeakness);
	std::string fight(std::string attackingWeapon);
private:
	std::string _weakness;
};
