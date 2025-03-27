//
// Created by dolataa on 3/26/2025.
//

#ifndef MAP_PARTS_H
#define MAP_PARTS_H

#include "hazards.h"
#include "player_character.h"

class MapCell;

class Map {
  static constexpr int SIDE_LENGTH = 5;
  MapCell* cells[SIDE_LENGTH][SIDE_LENGTH];
  public:
    Map();
    ~Map();
    void load(PlayerCharacter* pc);
    void print() const;
};

//---MapCell------------------------------------------------------------------------------------------------------------
class MapCell{
  private:
    bool hasPlayer;
    char hazardSymbol;
    SpikeTrap* hazard;
    Monster* monster;
    bool hasScroll;
    MapCell* northCell;
    MapCell* southCell;
    MapCell* eastCell;
    MapCell* westCell;
  public:
    MapCell(char type);
    ~MapCell();
    char getHazardSymbol() const;
    SpikeTrap* getHazard() const;
    Monster* getMonster() const;
    void playerEnter();
    void playerExit();
    void setHazard();
    void printCell();
    bool search();
    void printWarning() const;
    bool hasHazard() const;
    bool hasMonster() const;
    void setNeighbors(MapCell* north, MapCell* south, MapCell* east, MapCell* west);
    MapCell* getNextRoom(char direction) const;
};

#endif //MAP_PARTS_H
