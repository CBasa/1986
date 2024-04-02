#include "Player.h"

Player::Player()
{
}

Player::Player(std::string name, Room* startingRoom)
{
	_name = name;
	_health = 10;
	_hasKeycard = false;
	_lightSwitchOn = false;
	_startingRoom = startingRoom;
}

std::string Player::getName()
{
	return _name;
}

std::string Player::getGreatestFear()
{
	return _greatestFear;
}

int Player::getHealth()
{
	return _health;
}

bool Player::getHasKeycard()
{
	return _hasKeycard;
}

bool Player::getlightSwitchOn()
{
	return _lightSwitchOn;
}

Room* Player::getStartingRoom()
{
	return _startingRoom;
}

void Player::setName(std::string name)
{
	_name = name;
}

void Player::setGreatestFear(std::string greatestFear)
{
	_greatestFear = greatestFear;
}

void Player::setHasKeycard(bool hasKeycard)
{
	_hasKeycard = hasKeycard;
}

void Player::setlightSwitchOn(bool lightSwitchOn)
{
	_lightSwitchOn = lightSwitchOn;
}

void Player::reduceHealth(int damage)
{
	_health -= damage;
}

void Player::increaseHealth(int heal)
{
	_health += heal;
}

bool Player::isAlive()
{
	return _health > 0;
}


Enemy::Enemy(std::string name, std::string description) : Player()
{
	setName(name);
}

void Enemy::setWeakness(std::string weaponWeakness)
{
	_weakness = weaponWeakness;
}

std::string Enemy::fight(std::string attackingWeapon)
{
	if (attackingWeapon == _weakness)
	{
		return "Hes dead";
	}
	else
	{
		return "Thats not very much damage";
	}
}
