//
// Created by dolataa on 3/26/2025.
//

#include "player_character.h"
#include "map_parts.h"

PlayerCharacter::PlayerCharacter() {
  health = 35;
  armorClass = 15;
  scrollCount = 1;
  currentCell = nullptr;
}

PlayerCharacter::~PlayerCharacter() {
}

//returns the total number of scrolls the player has
int PlayerCharacter::addScroll() {
  return ++scrollCount;
}

int PlayerCharacter::getAttacked(int toHit, int damage) {
  if (toHit >= armorClass) {
    health -= damage;
  }
  if (health <= 0) {
    health = 0;
  }
  return health;
}

void PlayerCharacter::printWarnings() {
  bool canNorth = currentCell->getNextRoom('N') != nullptr;
  bool canSouth = currentCell->getNextRoom('S') != nullptr;
  bool canEast = currentCell->getNextRoom('E') != nullptr;
  bool canWest = currentCell->getNextRoom('W') != nullptr;

  if (canNorth) {
    currentCell->getNextRoom('N')->printWarning();
  } else {
    cout << "You can't go any further North." << endl;
  }
  if (canSouth) {
    currentCell->getNextRoom('S')->printWarning();
  } else {
    cout << "You can't go any further South." << endl;
  }
  if (canEast) {
    currentCell->getNextRoom('E')->printWarning();
  } else {
    cout << "You can't go any further East." << endl;
  }
  if (canWest) {
    currentCell->getNextRoom('W')->printWarning();
  } else {
    cout << "You can't go any further West." << endl;
  }
}

void PlayerCharacter::move(char direction) {
  if (currentCell->getNextRoom(direction) != nullptr) {
    currentCell->playerExit();
    currentCell = currentCell->getNextRoom(direction);
    currentCell->playerEnter();
    if (currentCell->hasHazard()) {
      cout << "You have entered a room with a spike trap!" << endl;
    }
    if (currentCell->hasMonster()) {
      if (currentCell->getHazardSymbol() == '*') {
        cout << "You have entered a room with the litch!" << endl;
      } else {
        cout << "You have entered a room with a flying skull!" << endl;
      }
    }
  } else {
    cout << "You can't go that way. You are already as far ";
    switch (direction) {
      case 'N':
        cout << "North";
        break;
      case 'S':
        cout << "South";
        break;
      case 'E':
        cout << "East";
        break;
      case 'W':
        cout << "West";
        break;
      default:
        cout << "FIX YOUR CODE IT HAS A BAD THING PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP";
        break;
    }
    cout << " as you can go." << endl;
  }
  printWarnings();
}

int PlayerCharacter::getHealth() {
  return health;
}

MapCell* PlayerCharacter::getCurrentCell() {
  return currentCell;
}

void PlayerCharacter::setCurrentCell(MapCell* cell) {
  currentCell = cell;
}

int PlayerCharacter::magicAttack() {
  scrollCount--;
  return rand() % (7 + 1);
}

int PlayerCharacter::swordAttack() {
  return rand() % (7 + 1);;
}
