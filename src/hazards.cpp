//
// Created by dolataa on 3/26/2025.
//

#include "hazards.h"
#include <iostream>
using namespace std;

//---Hazard------------------------------------------------------------------------------------------------------------
int Hazard::rollDamage() {
  return 0;
}
Hazard::~Hazard() {}
//---SpikeTrap----------------------------------------------------------------------------------------------------------
SpikeTrap::SpikeTrap() {
}

SpikeTrap::~SpikeTrap() {}

int SpikeTrap::rollDamage() {
  int maxDamage = 10;
  return rand() % (maxDamage + 1);
}

//---Monster------------------------------------------------------------------------------------------------------------
int Monster::rollDamage() {
  return 0;
}

Monster::~Monster() {}

bool Monster::getAttacked(char type, int toHit, int damage) {
  return false;
}

//---Litch--------------------------------------------------------------------------------------------------------------
Litch::~Litch() {}

int Litch::rollDamage() {
  int maxDamage = 10;
  return rand() % (maxDamage + 1);
}

bool Litch::getAttacked(char type, int toHit, int damage) {
  if (type == 'm') { //Magic attack
    if (toHit >= magicArmor) {
      cout << "You hit the litch with your magic attack!" << endl;
      health -= damage;
      if (health < 0) {
        health = 0;
      }
      cout << "Litch Health: " << health << "/35" << endl;
    } else {
      cout << "Your magic attack went wide and harmlessly hit the wall" << endl;
    }
  } else { //Physical attack with sword
    if (toHit >= physicalArmor) {
      cout << "You hit the litch with your sword!" << endl;
      health -= damage;
      if (health < 0) {
        health = 0;
      }
      cout << "Litch Health: " << health << "/35" << endl;
    } else {
      cout << "You swung and missed the litch" << endl;
    }
  }
  if (health <= 0) {
    cout << "Litch has been defeated and you claimed the ritual stone! You have been teleported out of the"
            "dungeon and a parade is thrown in your honor. YOU WIN!! " << endl;
    return true;
  }
  return false;
}

//---FlyingSkull--------------------------------------------------------------------------------------------------------
FlyingSkull::FlyingSkull() {}

FlyingSkull::~FlyingSkull() {}

int FlyingSkull::rollDamage() {
  int maxDamage = 5;
  return rand() % (maxDamage + 1);
}

bool FlyingSkull::getAttacked(char type, int toHit, int damage) {
  if (type == 'm') { //Magic attack
    if (toHit >= magicArmor) {
      cout << "You hit the flying skull with your magic attack!" << endl;
      health -= damage;
      if (health < 0) {
        health = 0;
      }
      cout << "Flying Skull Health: " << health << "/10" << endl;
    } else {
      cout << "Your magic attack missed the flying skull" << endl;
    }
  } else { //Physical attack with sword
    if (toHit >= physicalArmor) {
      cout << "You were fast enough and hit the flying skull with your sword!" << endl;
      health -= damage;
      if (health < 0) {
        health = 0;
      }
      cout << "Flying Skull Health: " << health << "/10" << endl;
    } else {
      cout << "The flying skull was too quick and you missed it with your sword." << endl;
    }
  }
  if (health <= 0) {
    cout << "You have defeated the flying skull." << endl;

    return true;
  }
  return false;
}


