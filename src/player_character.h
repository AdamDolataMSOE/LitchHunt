//
// Created by dolataa on 3/26/2025.
//


#ifndef PLAYER_CHARACTER_H
#define PLAYER_CHARACTER_H

#include "map_parts.h"
class MapCell;

class PlayerCharacter {
private:
  int scrollCount, health, armorClass;
  MapCell* currentCell;
public:
  PlayerCharacter();
  ~PlayerCharacter();
  int addScroll();
  int getAttacked(int toHit, int damage);
  void printWarnings();
  void move(char direction);
  int getHealth();
  MapCell* getCurrentCell();
  void setCurrentCell(MapCell* cell);
  int magicAttack();
  int swordAttack();
};

#endif //PLAYER_CHARACTER_H
