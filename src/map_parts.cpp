//
// Created by dolataa on 3/26/2025.
//

#include "map_parts.h"
#include "player_character.h"
#include "hazards.cpp"
#include <iostream>
using namespace std;

//---MapCell------------------------------------------------------------------------------------------------------------
MapCell::MapCell(char type) {
  hasPlayer = false;
  hazardSymbol = type;
  hazard = nullptr;
  monster = nullptr;
  northCell = nullptr;
  southCell = nullptr;
  eastCell = nullptr;
  westCell = nullptr;
  setHazard();
  if(rand() % (2 + 1) == 1) {
    hasScroll = true;
  } else {
    hasScroll = false;
  }
}

char MapCell::getHazardSymbol() const {
  return hazardSymbol;
}

MapCell::~MapCell() {

  delete hazard;
  delete monster;

}

void MapCell::setNeighbors(MapCell* north, MapCell* south, MapCell* east, MapCell* west) {
  northCell = north;
  southCell = south;
  eastCell = east;
  westCell = west;
}

MapCell* MapCell::getNextRoom(char direction) const {
  if (direction == 'N') {
    return northCell;
  }
  if (direction == 'S') {
    return southCell;
  }
  if (direction == 'E') {
    return eastCell;
  }
  return westCell;
}

void MapCell::playerEnter() {
  hasPlayer = true;
}
void MapCell::playerExit() {
  hasPlayer = false;
}

void MapCell::setHazard() {
  if(hazardSymbol == '*') {
    monster = new Litch();
  } else if (hazardSymbol == '~'){
    monster = new FlyingSkull();
  } else if (hazardSymbol == '^') {
    hazard = new SpikeTrap();
  }
}

void MapCell::removeMonster() {
  // delete monster;
  hazardSymbol = '.';
}

void MapCell::printCell() {
  if (hasPlayer) {
    cout << '#';
  } else {
    cout << hazardSymbol;
  }
}

bool MapCell::search() {
  if(hasScroll) {
    cout << "You found a scroll!" << endl;
    hasScroll = false;
    return true;
  }
  cout << "You found nothing in this musty room." << endl;
  return false;
}

void MapCell::printWarning() const {
  if(hazardSymbol == '*') {
    cout << "You feel a deathly aura nearby." << endl;
  } else if (hazardSymbol == '~') {
    cout << "You hear the chittering of teeth coming from nearby." << endl;
  } else if (hazardSymbol == '^') {
    cout << "You hear the sounds of turning gears from nearby." << endl;
  }
}

bool MapCell::hasHazard() const {
  return hazardSymbol == '^';
}

bool MapCell::hasMonster() const {
  return monster != nullptr;
}

SpikeTrap* MapCell::getHazard() const {
  return hazard;
}

Monster* MapCell::getMonster() const {
  return monster;
}

//---Map----------------------------------------------------------------------------------------------------------------
Map::Map() {
  for(int i = 0; i < SIDE_LENGTH; i++) {
    for(int j = 0; j < SIDE_LENGTH; j++) {
      cells[i][j] = nullptr;
    }
  }
}

Map::~Map() {
  for(int i = 0; i < SIDE_LENGTH; i++) {
    for(int j = 0; j < SIDE_LENGTH; j++) {
      delete cells[i][j];
    }
  }
}

void Map::load(PlayerCharacter* pc) {
  int litchCell = rand() % (SIDE_LENGTH * SIDE_LENGTH);
  int countForLitch = 0;
  int countForEmpty = 0;

  for(int i = 0; i < SIDE_LENGTH; i++) {
    for(int j = 0; j < SIDE_LENGTH; j++) {

      //determines what is in a cell
      int type = rand() % 12;
      if(countForLitch == litchCell) {
        cells[i][j] = new MapCell('*');
      } else if(type < 1) {
        cells[i][j] = new MapCell('^');
      } else if(type < 3) {
        cells[i][j] = new MapCell('~');
      } else {
        countForEmpty++;
        cells[i][j] = new MapCell('.');
      }
      countForLitch++;
    }
  }

  if (countForEmpty == 0) {
    for(int i = 0; i < SIDE_LENGTH; i++) {
      for(int j = 0; j < SIDE_LENGTH; j++) {
        //gives each cell pointers to its four neighbors nsew
        MapCell* north = nullptr;
        MapCell* south = nullptr;
        MapCell* east = nullptr;
        MapCell* west = nullptr;
        if (i > 0) {
          north = cells[i - 1][j];
        }
        if (i < SIDE_LENGTH - 1) {
          south = cells[i + 1][j];
        }
        if (j > 0) {
          west = cells[i][j - 1];
        }
        if (j < SIDE_LENGTH - 1) {
          east = cells[i][j + 1];
        }
        cells[i][j]->setNeighbors(north, south, east, west);
      }
    }
    bool litchCellPlayerAdd = false;
    int playerCellI = rand() % (SIDE_LENGTH + 1);
    int playerCellJ = rand() % (SIDE_LENGTH + 1);
    while (!litchCellPlayerAdd) {
      if (cells[playerCellI][playerCellJ]->getHazardSymbol() != '*') {
        pc->setCurrentCell(cells[playerCellI][playerCellJ]);
        cells[playerCellI][playerCellJ]->playerEnter();
        litchCellPlayerAdd = true;
      } else {
        playerCellI = rand() % (SIDE_LENGTH + 1);
        playerCellJ = rand() % (SIDE_LENGTH + 1);
      }
    }
  } else {
    countForEmpty /= 2;
    for(int i = 0; i < SIDE_LENGTH; i++) {
      for(int j = 0; j < SIDE_LENGTH; j++) {
        //gives each cell pointers to its four neighbors nsew
        MapCell* north = nullptr;
        MapCell* south = nullptr;
        MapCell* east = nullptr;
        MapCell* west = nullptr;
        if (i > 0) {
          north = cells[i - 1][j];
        }
        if (i < SIDE_LENGTH - 1) {
          south = cells[i + 1][j];
        }
        if (j > 0) {
          west = cells[i][j - 1];
        }
        if (j < SIDE_LENGTH - 1) {
          east = cells[i][j + 1];
        }
        cells[i][j]->setNeighbors(north, south, east, west);

        //determines where the player starts
        if(!(cells[i][j]->hasHazard()) && !(cells[i][j]->hasMonster())) {
          countForEmpty--;
          if(countForEmpty == 1) {
            pc->setCurrentCell(cells[i][j]);
            cells[i][j]->playerEnter();
          }
        }
      }
    }
  }
}

void Map::print() const {
  cout << "Key: # = Player, * = Litch, ~ = Flying Skull, ^ = Spike Trap" << endl;
  for(int i = 0; i < SIDE_LENGTH; i++) {
    for(int j = 0; j < SIDE_LENGTH; j++) {
      cells[i][j]->printCell();
    }
    cout << endl;
  }
}
