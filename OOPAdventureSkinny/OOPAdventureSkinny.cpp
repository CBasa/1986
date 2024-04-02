// OOPAdventureSkinny.cpp : This file contains the 'main' function. Program
// execution begins and ends there.
//

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <chrono>
#include <thread>

#include <locale>

#include "Interaction.h"
#include "Item.h"
#include "Player.h"
#include "Room.h"

void enterRoom(Room room, Room *currentRoom, std::string action,
               Player *player);

void convertToLowerCase(std::string &input) {
  for (auto iter = input.begin(); iter != input.end(); ++iter) {
    *iter = std::tolower(*iter);
  }
}

void welcome(std::string &name, Room currentRoom) {
   
  std::cout << "What is your name?\n";
  std::cout << "> ";
  std::getline(std::cin, name);
  std::cout << "\nWelcome to 1986, " << name << ".\n";
  std::cout << "\nINITIALISING...\n\n\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  std::cout << "You wake in a cold, dark room, not knowing who you are, how you got here or even if you are supposed to be here, wherever here is...\n\n";




  std::cout << /*"\nYou are in the " + currentRoom.getName() + ". " +*/
                   currentRoom.getDescription() + "\n\n";
}

void playerDies(Player* player, Room room, Room* currentRoom, std::string action)
{
    std::cout
        << "\n\nYou did not make it!\n\nWould you like to try again? (Y/N)\n> ";
    std::string response;
    std::getline(std::cin, response);
    convertToLowerCase(response);
    std::cout << "\n";

    if (response == "y") {
        player->setHasKeycard (false);
        player->setlightSwitchOn(false);
        std::string name;
        welcome(name, *currentRoom);
        enterRoom(*currentRoom, currentRoom, action, player);
    }
    else {
        player->reduceHealth(player->getHealth());
    }
}


void initialiseKnife(PlayerItem *knife) {
  // PlayerItem knife = PlayerItem("Knife", "A rusty knife", false);
  Interaction stab =
      Interaction("stab", "stab the mutant", "Mutant falls and dies");
  Interaction drop = Interaction("drop", "drop the item", "Mutant attacks you");
  Interaction ignore =
      Interaction("ignore", "ignore the item", "Mutant attacks you");
  knife->linkedInteractions["stab"] = &stab;
  knife->linkedInteractions["drop"] = &drop;
  knife->linkedInteractions["ignore"] = &ignore;
}

void moveRoom(Room *currentRoom, std::string action, Player *player) {
  if (currentRoom->linkedRooms.find(action) != currentRoom->linkedRooms.end()) {
    if (currentRoom->getName() == "Bunker Entrance" && action == "south" &&
        player->getHasKeycard() != true) {
      std::cout << "\nThe door is locked.\n";
      std::cout << "\n You are in the " + currentRoom->getName() +
                       ". What would you like to do next?\n";
    } else if (currentRoom->getName() == "Staircase" && action == "south" && player->getlightSwitchOn() == false) {
        std::cout
            << "\nYou carefully descend the staircase into the darkness. As you "
            "descend your vision slowly fades to black. You see nothing and "
            "hear nothing. Feeling like you’re almost at the bottom you "
            "place your foot on the next step and feel your foot lose grip "
            "and the ground hurls towards you. You hear a final crunch as "
            "you land on your neck at the final step.";
        playerDies(player, *player->getStartingRoom(), player->getStartingRoom(), action);
    } else if (currentRoom->getName() == "Mutant Room" && action == "west") {

    } else {
      std::cout << "\nYou are in the " +
                       currentRoom->linkedRooms[action]->getName() + ". " +
                       currentRoom->linkedRooms[action]->getDescription() +
                       "\n\n";
      currentRoom = currentRoom->linkedRooms[action];
      enterRoom(*currentRoom, currentRoom, action, player);
    }
  }
}

/// <summary>
/// Pick what do do with the item
/// </summary>
/// <param name="item">The item the player has chosen to interact with</param>
/// <param name="currentItem">Pointer for the item the player has chosen to interact with</param>
/// <param name="currentRoom">Pointer for the room the player is currently in</param>
/// <param name="action">Player's command input</param>
/// <param name="player">The player</param>
void pickItemInteraction(Item item, Item *currentItem, std::string action,
                         Room *currentRoom, Player *player) {
  Interaction interaction =
      Interaction("No action selected", "default", "default");
  Interaction *currentInteraction = &interaction;

  //Output item description to the player
  std::cout << "\n" + item.getDescription() + "\n";

  // Output options to the player
  for (auto it = item.linkedInteractions.cbegin();
       it != item.linkedInteractions.cend(); ++it) {
    std::cout << std::right << "\n- Type command '" << it->second->getName()
              << "' to " << it->second->getDescription();
  }

  // Player inputs command
  std::cout << "\n\n> ";
  std::getline(std::cin, action);
  convertToLowerCase(action);
  // Set current interaction and output outcome to player
  if (currentItem->linkedInteractions.find(action) !=
      currentItem->linkedInteractions.end()) {
    currentInteraction = currentItem->linkedInteractions[action];
    if (currentInteraction->getName() == "pick up") {
      // remove item from linkedItems in currentRoom
      currentRoom->linkedItems.erase(currentItem->getName());
      player->inventory[currentItem->getName()] = currentItem;
    } else if (currentInteraction->getName() == "search labcoat") {
      // remove item from linkedItems in currentRoom
      currentRoom->linkedItems.erase(currentItem->getName());
      player->setHasKeycard(true);
    } else if (currentInteraction->getName() == "pull" ||
               currentInteraction->getName() == "push" ||
               currentInteraction->getName() == "knock") {
      if (player->getHasKeycard()) {
        currentInteraction->setOutcome(
            "You press the keycard to the electronic pad "
            "attached to the door. It makes a quiet beep and you hear the door "
            "unlock.");
      }
    } else if (currentInteraction->getName() == "flick switch" && player->getlightSwitchOn() == true) {
        currentInteraction->setOutcome(
            "You should probably keep these lights on.");
    } else if (currentInteraction->getName() == "flick switch") {
      player->setlightSwitchOn(true);
    } else if (currentInteraction->getName() == "flick switch" &&  player->getlightSwitchOn() == true) {
        currentInteraction->setOutcome(
            "You should probably keep these lights on.");
    } else if (currentInteraction->getName() == "look" && player->getlightSwitchOn() == true) {
        currentInteraction->setOutcome(
            "The staircase is dimly lit but you can make out a small obstacle at the bottom of the stairs.");
    } else if (currentInteraction->getName() == "go down") {
      if (!player->getlightSwitchOn()) {
        std::cout
            << "\nYou carefully descend the staircase into the darkness. As you "
               "descend your vision slowly fades to black. You see nothing and "
               "hear nothing. Feeling like you’re almost at the bottom you "
               "place your foot on the next step and feel your foot lose grip "
               "and the ground hurls towards you. You hear a final crunch as "
               "you land on your neck at the final step.";
        playerDies(player, *player->getStartingRoom(),  player->getStartingRoom(), action);
      } else
      {
          moveRoom(currentRoom, "south", player);
      }
    }
    else if (currentInteraction->getName() == "open")
    {
        std::cout << "\n" + currentInteraction->getOutcome() + "\n";
        playerDies(player, *player->getStartingRoom(), player->getStartingRoom(), action);
    }

    std::cout << "\n" + currentInteraction->getOutcome() + "\n";
    std::cout << "\nYou are in the " + currentRoom->getName() +
                     ". What would you like to do next?\n\n";
  } // add condition for if no interactions available
  else {
    pickItemInteraction(item, currentItem, action, currentRoom, player);
  }
}


/// <summary>
/// Pick what to do in the room
/// </summary>
/// <param name="room">The room the player is currently in</param>
/// <param name="currentRoom">Pointer for the room the player is currently in</param>
/// <param name="action">Player's command input</param>
/// <param name="player">The player</param>
void pickRoomInteraction(Room room, Room *currentRoom, std::string action,
                         Player *player) {
  Interaction interaction =
      Interaction("No action selected", "default", "default");
  Interaction *currentInteraction = &interaction;

  // Output options to the player
  for (auto it = room.linkedInteractions.cbegin();
       it != room.linkedInteractions.cend(); ++it) {
    std::cout << std::right << "- Type command '" << it->second->getName()
              << "' to " << it->second->getDescription() << std::endl;
  }

  // Player inputs command
  std::cout << " \n> ";
  std::getline(std::cin, action);
  convertToLowerCase(action);
  // Set current interaction and output outcome to player
  if (currentRoom->linkedInteractions.find(action) !=
      currentRoom->linkedInteractions.end()) {
    currentInteraction = currentRoom->linkedInteractions[action];
    if (currentInteraction->getName() == "move") {
      std::cout << "\nWhich direction do you want to move?\n";
      for (auto it = currentRoom->linkedRooms.cbegin();
           it != currentRoom->linkedRooms.cend(); ++it) {
        std::cout << std::right << "- Type command '" << it->first << "'"
                  << std::endl;
      }
      std::cout << " \n> ";
      std::getline(std::cin, action);
      convertToLowerCase(action);
      moveRoom(currentRoom, action, player);
    } else if (currentInteraction->getName() == "inspect" &&
               !currentRoom->linkedItems.empty()) {
      // add if statement for no items in room left to inspect
      std::cout << "\nWhich item do you want to inspect?\n";
      for (auto it = currentRoom->linkedItems.cbegin();
           it != currentRoom->linkedItems.cend(); ++it) {
        std::cout << std::right << "- Type command '" << it->first << "'"
                  << std::endl;
      }
      std::cout << "\n> ";
      std::getline(std::cin, action);
      convertToLowerCase(action);
      if (currentRoom->linkedItems.find(action) !=
          currentRoom->linkedItems.end()) {
        Item *currentItem = currentRoom->linkedItems[action];
        pickItemInteraction(*currentItem, currentItem, action, currentRoom,
                            player);
      }
    }
  } else {
    pickRoomInteraction(room, currentRoom, action, player);
  }
}

void enterRoom(Room room, Room *currentRoom, std::string action,
               Player *player) {
  do {
    pickRoomInteraction(room, currentRoom, action, player);
  } while (player->isAlive() == true);
}

int main() {
  //Initialise Rooms
  Room staircase = Room(
      "Staircase", "You find yourself at the top of a large metal STAIRCASE "
                   "with a bright white light illuminating the landing. The "
                   "stairs slowly descend"
                   " into darkness. You see a large DOOR behind you and a "
                   "small SWITCH on the wall nearby.");

  Room bunkerEntrance =
      Room("Bunker Entrance",
           "On your way down the stairs you see a banana peel that "
           "has been left on the stairs. You step around it on your way down. "
           "Once you reach"
           " the bottom of the stairs you see a WRENCH with some tools "
           "inside, a LABCOAT hanging "
           "on a hook attached to the wall and a small WOODEN DOOR.");
  Room adminRoom =
      Room("Admin Room",
           "The place has been torn apart. "
           "Something horrible has happened here. What appears to "
           "once have been a desk is now a collection of splinters and the floor "
           "is covered in paper. A TYPEWRITER sits atop the rubble. "
           "A piece of paper stuck inside. The only other objects still "
           "standing are a set of metal CABINETS and on your right a CUPBOARD in the corner. "
           "You hear strange noises coming from the corner in which the cupboard stands");

  staircase.linkedRooms["south"] = &bunkerEntrance;
  bunkerEntrance.linkedRooms["north"] = &staircase;
  bunkerEntrance.linkedRooms["south"] = &adminRoom;
  adminRoom.linkedRooms["north"] = &bunkerEntrance;

  Interaction moveToRoom = Interaction("move", "move to a different room",
                                       "You have moved to a different room");
  Interaction inspect = Interaction("inspect", "inspect the area or items",
                                    "You can see the following: \n");

  staircase.linkedInteractions["move"] = &moveToRoom;
  staircase.linkedInteractions["inspect"] = &inspect;
  bunkerEntrance.linkedInteractions["move"] = &moveToRoom;
  bunkerEntrance.linkedInteractions["inspect"] = &inspect;
  adminRoom.linkedInteractions["move"] = &moveToRoom;
  adminRoom.linkedInteractions["inspect"] = &inspect;

  Room *currentRoom = &staircase;

  //PlayerItem knife = PlayerItem("Knife", "A rusty knife", false);
  //// initialiseKnife(&knife);
  //Interaction stab =
  //    Interaction("stab", "stab the mutant", "Mutant falls and dies");
  //Interaction drop = Interaction("drop", "drop the item", "Mutant attacks you");
  //Interaction ignore =
  //    Interaction("ignore", "ignore the item", "Mutant attacks you");
  //knife.linkedInteractions["stab"] = &stab;
  //knife.linkedInteractions["drop"] = &drop;
  //knife.linkedInteractions["ignore"] = &ignore;

  //Wrench in Bunker Entrance
  PlayerItem wrench =
      PlayerItem("wrench", "A wrench on the floor", false);
  Interaction pickUp = Interaction(
      "pick up", "pick up the item",
      "You place the item in your bag. It might come in handy later.");
  wrench.linkedInteractions["pick up"] = &pickUp;
  bunkerEntrance.linkedItems["wrench"] = &wrench;

  //Labcoat in Bunker Entrance
  PlayerItem labcoat = PlayerItem(
      "labcoat",
      "The labcoat is well worn, stained with what looks like red paint and "
      "various yellowy chemical stains. This labcoat does not get washed.",
      false);
  Interaction tryOnLabcoat =
      Interaction("search labcoat", "search the labcoat pockets",
                  "You feel around inside the pockets of the lab coat. There "
                  "appears to be a keycard inside.");
  labcoat.linkedInteractions["search labcoat"] = &tryOnLabcoat;
  bunkerEntrance.linkedItems["labcoat"] = &labcoat;

  //Wooden Door in Bunker Entrance
  PlayerItem woodenDoor = PlayerItem(
      "wooden door",
      "On the wooden door there is a small window. The door looks sturdy and you "
      "notice that there is no keyhole but an electronic pad.",
      false);
  Interaction pushOnDoor = Interaction(
      "push", "try to push open the door", "The door does not budge.");
  Interaction pullOnDoor = Interaction(
      "pull", "try to pull open the door", "The door does not budge.");
  Interaction knockOnDoor =
      Interaction("knock", "knock on the door",
                  "You eagerly wait for a response. Silence.");
  Interaction openDoor =
      Interaction("open door", "tap the keycard on the electronic pad",
                  "You hear a beep. Your key card opens the door.");
  Interaction lookWindow =
      Interaction("window", "look through the window",
          "You peer through the small window on the door. You see a room that "
            "is an absolute mess. As you scan the left side of the room you see a "
          "flicker on the other side of the room. You look to see what it was but nothing is there.");

  woodenDoor.linkedInteractions["push"] = &pushOnDoor;
  woodenDoor.linkedInteractions["pull"] = &pullOnDoor;
  woodenDoor.linkedInteractions["knock"] = &knockOnDoor;
  woodenDoor.linkedInteractions["window"] = &lookWindow;
  bunkerEntrance.linkedItems["wooden door"] = &woodenDoor;

  //Metal Door in Staircase
  PlayerItem metalDoor =
      PlayerItem("metal door",
                 "You approach the large chunk of metal that appears to be a "
                 "door. Whether it's designed to keep things in or out you are "
                 "unsure. You think about attempting to PUSH or PULL the door "
                 "open but doubt you will have any success. There may be a "
                 "BUTTON somewhere or you could always try and KNOCK.",
                 false);
  Interaction pushOnMetalDoor = Interaction(
      "push", "try to push open the door", "The door does not budge.");
  Interaction pullOnMetalDoor = Interaction(
      "pull", "try to pull open the door", "The door does not budge.");
  Interaction knockOnMetalDoor =
      Interaction("knock", "knock on the door",
                  "You eagerly wait for a response. Silence.");

  metalDoor.linkedInteractions["push"] = &pushOnMetalDoor;
  metalDoor.linkedInteractions["pull"] = &pullOnMetalDoor;
  metalDoor.linkedInteractions["knock"] = &knockOnMetalDoor;
  staircase.linkedItems["metal door"] = &metalDoor;

  //Light Switch in Staircase
  PlayerItem lightSwitch =
      PlayerItem("light switch", "It appears to be a light switch.", false);
  Interaction flickLightSwitch =
      Interaction("flick switch", "flick the light switch.",
                  "This turns on the lights down the staircase.");
  Interaction goBack = Interaction("go back", "back away from the light switch",
                                   "You return to the centre of the room.");

  lightSwitch.linkedInteractions["flick switch"] = &flickLightSwitch;
  lightSwitch.linkedInteractions["go back"] = &goBack;
  staircase.linkedItems["light switch"] = &lightSwitch;

  PlayerItem stairsItem = PlayerItem(
      "stairs",
      "You approach the staircase. You see nothing but darkness down below. "
      "You cannot see where the stairs lead. You are a bit scared to LOOK DOWN "
      "and not sure if you are brave enough to GO DOWN THE STAIRS.",
      false);
  Interaction goDownStairs =
      Interaction("go down", "go down the stairs.",
                  "You make it to the bottom of the stairs.  Try moving to "
                  "another room to proceed.");
  Interaction lookDownStairs =
      Interaction("look", "look down the stairs.", "You cannot see the bottom.");

  stairsItem.linkedInteractions["go down"] = &goDownStairs;
  stairsItem.linkedInteractions["look"] = &lookDownStairs;
  staircase.linkedItems["stairs"] = &stairsItem;

  //Typewriter in Admin Room
  PlayerItem typewriter =
      PlayerItem("typewriter", "a typewriter with a piece of paper still inside ", false);
  Interaction typewriterLookCloser = Interaction(
      "look closer", "see what's in the typewriter.",
      "The top half has been ripped apart. You read over the half written "
      "piece of paper. The text is hastily typed, and the content sends shivers "
      "down your spine. You read “The experiments of Project Cave hint at "
      "the manipulation of subjective experiences, raising profound questions "
      "ab…” The rest is ineligible. You wonder what the purpose of these "
      "experiments were or are.");
  Interaction typewriterSmash = Interaction(
      "throw", "smash the typewriter on the floor", 
      "You pick up the typewriter above your head and throw it to the floor. As "
      "it crashes to the ground, its shattered pieces scatter across the room.The "
      "sound of breaking metal and plastic screech and echo in the air. As the final "
      "pieces come to a stop, you notice just how silent the room is. Normally, one "
      "would anticipate the subtle hum of electricity and the faint buzz of fluorescent "
      "lights. Instead only the silence of the void can be heard. \n"
      "You notice amidst what remains of the typewriter a small gold key. At the head of "
      "the key is an Omega symbol. You wonder what door this will unlock");

  typewriter.linkedInteractions["look closer"] = &typewriterLookCloser;
  typewriter.linkedInteractions["throw"] = &typewriterSmash;
  adminRoom.linkedItems["typewriter"] = &typewriter;

  //Cabinets in Admin Room
  PlayerItem cabinets =
      PlayerItem("cabinets", "You move towards the cabinets ", false);
  Interaction lookInside = Interaction(
      "look inside","look inside the cabinets",
      "A document titled Protocol Alpha catches your eye. You open it to find "
      "that almost the entire document has been reduced to thick black lines "
      "covering the text making it unreadable. Whatever was written on these "
      "pages must be extremely confidential.");

  cabinets.linkedInteractions["look inside"] = &lookInside;
  adminRoom.linkedItems["cabinets"] = &cabinets;

  //Cupboard in Admin Room
  PlayerItem cupboard =
      PlayerItem("cupboard", "You move towards the cupboard ", false);
  Interaction cupboardListen = Interaction(
      "listen", "the hear what's inside",
      "you hear scratching and heavy breathing coming from inside.");
  Interaction cupboardLookInside = Interaction(
      "open", "see what's inside",
      "With a deep breath you open the cupboard door. Suddenly the door "
      "bursts open and a mutant lunges out from the confined darkness. Its "
      "eyes gleam with a feral intensity and a guttural growl escaped its  "
      "twisted form. In the blink of an eye it’s upon you, claws slashing "
      "through the air.There is no time to react.The mutant’s attack is "
      "swift and relentless.Its claws tear through your defences and before "
      "you can comprehend the horror, darkness envelops you.As you close your "
      "eyes for the last time you see the world around you crumble and fall apart.");
  //Player dies here
  
  cupboard.linkedInteractions["listen"] = &cupboardListen;
  cupboard.linkedInteractions["open"] = &cupboardLookInside;
  adminRoom.linkedItems["cupboard"] = &cupboard;

  //Initialise player
  std::string name;
  Player *player;
  player = new Player(name, &staircase);
  bool staircaseLightSwitch = false;
  std::string feared;
  welcome(name, staircase);
  std::string action;

  //PlayerItem *currentItem = &knife;

  // do
  //{
  enterRoom(staircase, currentRoom, action, player);
  //} while (isAlive == true);

}