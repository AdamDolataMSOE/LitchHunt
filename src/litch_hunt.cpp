//
// Created by dolataa on 3/26/2025.
//

#include "map_parts.cpp"
#include "player_character.cpp"

#include <iostream>
using namespace std;

void printStartMessage();
void printHelp();
int hitRoll();
bool handleSpikeTrap(PlayerCharacter* pc);
bool potentialCombat(char playerAction, PlayerCharacter* pc);
bool litchDead = false;

int main() {
  srand(static_cast<unsigned int>(time(0)));

  PlayerCharacter* pc = new PlayerCharacter();
  Map* map = new Map();
  map->load(pc);

  printStartMessage();
  pc->printWarnings();

  bool gameOver = false;
  char input;

  while (!gameOver) {
    cout << "What would you like to do?" << endl;
    cin >> input;
    toupper(input);
    switch (input) {
      case 'N':
        pc->move('N');
        gameOver = handleSpikeTrap(pc);
        break;
      case 'n':
        pc->move('N');
        gameOver = handleSpikeTrap(pc);
        break;
      case 'S':
        pc->move('S');
        gameOver = handleSpikeTrap(pc);
        break;
      case 's':
        pc->move('S');
        gameOver = handleSpikeTrap(pc);
        break;
      case 'E':
        pc->move('E');
        gameOver = handleSpikeTrap(pc);
        break;
      case 'e':
        pc->move('E');
        gameOver = handleSpikeTrap(pc);
        break;
      case 'W':
        pc->move('W');
        gameOver = handleSpikeTrap(pc);
        break;
      case 'w':
        pc->move('W');
        gameOver = handleSpikeTrap(pc);
        break;
      case '1':
        gameOver = potentialCombat('1', pc);
        break;
      case '2':
        gameOver = potentialCombat('2', pc);
        break;
      case '3':
         gameOver = potentialCombat('3', pc);
        break;
      case 'H':
        printHelp();
        break;
      case 'h':
        printHelp();
        break;
      case 'M':
        map->print();
        break;
      case 'm':
        map->print();
      break;
      case 'Q':
        cout << "You have quit the game, the litch has won. Because of you many will die." << endl;
        gameOver = true;
        break;
      case 'q':
        cout << "You have quit the game, the litch has won. Because of you many will die." << endl;
      gameOver = true;
      break;
      case ' ':
        break;
      case '\n':
        break;
      default:
        cout << "Invalid input, please try again." << endl;
      break;
    }
  }
  if (!litchDead) {
    cout << "You have failed to kill the litch and retrieve the Ritual Stone." << endl;
  }
  delete pc;
  delete map;
  return 0;
}

void printStartMessage() {
  cout << "The noble adventurer must plunge into the depths of the dungeon to retrieve the stone of rituals which\n"
          "was stolen by the evil litch. You must search for the litch and kill it. As you search you will face\n"
          "mechanical spike traps, undead flying skulls, and the litch itself.\n" << endl;
  printHelp();
}
void printHelp() {
  cout << "If you can hear the sounds of turning gears you can be sure that there is a room near by where there \n"
          "is a spike trap, be careful as spike traps have a chance to be skewer you through and end your life.\n\n"
          "If you can hear the sound of chattering teeth there is a flying skull near by. Flying skulls are weak\n"
          "to magic so you were equipped with a magic scroll upon entry, more of which can be found in some of the\n "
          "dungeon rooms so search around. If need be you can try to attack with your sword but this will be more\n "
          "difficult.\n\n "
          "If you are filled with an uneasy feeling and it stinks of death the litch is near. The litch is\n"
          "resistant to magic so the scrolls will be less effective, your best bet is attacking with your sword.\n"
          "Once the litch is killed and you retrieve the ritual stone you will be teleported out of the dungeon\n"
          "and a parade will be made in your honor.\n\n"
          "Spike Traps can hit you as soon as you enter a room. Be careful re-entering these rooms as the traps will\n"
          "reactivate. The undead are fairly slow reacting so if you are quick enough you could run out of the room\n"
          "before they can react.\n\n"
          "Controls:\n"
          "    N: Move north through the dungeon\n"
          "    S: Move south through the dungeon\n"
          "    E: Move east through the dungeon\n"
          "    W: Move west through the dungeon\n"
          "    1: Attack with your sword\n"
          "    2: Attack with a magic scroll\n"
          "    3: Search the room for scrolls\n"
          "    M: Show Map\n"
          "    H: Help\n"
          "    Q: Quit\n\n"
          "opening the help menu and quitting the game does not progress the game however if you search the room for\n"
          "scrolls or open your map in a room with the undead you may be hit before you can react." << endl;
}

int hitRoll() {
  return rand() % (20 + 1);
}

bool handleSpikeTrap(PlayerCharacter* pc) {

  int preHealth = pc->getHealth();
  if (pc->getCurrentCell()->hasHazard()) { //if there is a spike trap in the room you get stabbed immediately if the hit lands
    pc->getAttacked(hitRoll() + 3, pc->getCurrentCell()->getHazard()->rollDamage());
    if (pc->getHealth() == 0) {
      cout << "You have died to a spike trap and failed to collect the Ritual Stone." << endl;
      return true;
    }
    if (preHealth > pc->getHealth()) {
      cout << "You have been stabbed by a spike trap. You have " << pc->getHealth() << "/35 health left" << endl;
    } else {
      cout << "You have successfully evaded the spike trap and took no damage." << endl;
    }
  }
  return false;
}

bool potentialCombat(char playerAction, PlayerCharacter* pc) {
  Monster* monster = pc->getCurrentCell()->getMonster();

  //no monster to fight
  if (monster == nullptr) {
    if (playerAction == '1') {
      cout << "You swing your sword at the air waisting your time." << endl;
    } else if (playerAction == '2') {
      cout << "You used a spell scroll at an empty room..." << endl;
    } else if (playerAction == '3') {
      if (pc->getCurrentCell()->search()) {
        pc->addScroll();
      }
    }
    return false;
  }

  //monster is present
  char type = pc->getCurrentCell()->getHazardSymbol();
  bool end = false;
  int preHealth = pc->getHealth();
  if (type == '*') {
    //litch
    if (playerAction == '1') {
      end = monster->getAttacked('s', hitRoll(), pc->swordAttack()); //sword attack
      if (end) {
        litchDead = true;
        return end;
      }
      if (pc->getAttacked(hitRoll(), monster->rollDamage()) == 0) {
        cout << "You have died to the litch and failed to collect the Ritual Stone. The litch will soon become too powerful\n"
                "to stop." << endl;
        return true;
      }
      if (preHealth == pc->getHealth()) {
        cout << "The litch missed you with its magic attack." << endl;
      }
      if (preHealth > pc->getHealth()) {
        cout << "The litch hit you. You have " << pc->getHealth() << "/35 health left" << endl;
      }
      return false;
    }
    if (playerAction == '2') {
      end = monster->getAttacked('m', hitRoll(), pc->swordAttack()); //magic attack
      if (end) {
        litchDead = true;
        return end;
      }
      if (pc->getAttacked(hitRoll(), monster->rollDamage()) == 0) {
        cout << "You have died to the litch and failed to collect the Ritual Stone. The litch will soon become too powerful\n"
                "to stop." << endl;
        return true;
      }
      if (preHealth == pc->getHealth()) {
        cout << "The litch missed you with its magic attack." << endl;
      }
      if (preHealth > pc->getHealth()) {
        cout << "The litch hit you. You have " << pc->getHealth() << "/35 health left" << endl;
      }
      return false;
    }
    if (playerAction == '3') {
      if (pc->getCurrentCell()->search()) {
        pc->addScroll();
      }
      if (pc->getAttacked(hitRoll(), monster->rollDamage()) == 0) {
        cout << "You have died to the litch and failed to collect the Ritual Stone. The litch will soon become too powerful\n"
                "to stop." << endl;
        return true;
      }
      if (preHealth == pc->getHealth()) {
        cout << "The litch missed you with its magic attack." << endl;
      }
      if (preHealth > pc->getHealth()) {
        cout << "The litch hit you. You have " << pc->getHealth() << "/35 health left" << endl;
      }
      return false;
    }
  }

  //monster is a flying skull
  if (type == '~') {
    if (playerAction == '1') {
      end = monster->getAttacked('s', hitRoll(), pc->swordAttack()); //sword attack
      if (end) {
        return false;
      }
      if (pc->getAttacked(hitRoll(), monster->rollDamage()) == 0) {
        cout << "You have died to a flying skull. Because you died to a lowly undead we are all doomed" << endl;
        return true;
      }
      if (preHealth == pc->getHealth()) {
        cout << "The flying skull missed you with its attack." << endl;
      }
      if (preHealth > pc->getHealth()) {
        cout << "The flying skull hit you. You have " << pc->getHealth() << "/35 health left" << endl;
      }
      return false;
    }
    if (playerAction == '2') {
      end = monster->getAttacked('m', hitRoll(), pc->swordAttack()); //magic attack
      if (end) {
        return false;
      }
      if (pc->getAttacked(hitRoll(), monster->rollDamage()) == 0) {
        cout << "You have died to a flying skull. Because you died to a lowly undead we are all doomed" << endl;
        return true;
      }
      if (preHealth == pc->getHealth()) {
        cout << "The flying skull missed you with its attack." << endl;
      }
      if (preHealth > pc->getHealth()) {
        cout << "The flying skull hit you. You have " << pc->getHealth() << "/35 health left" << endl;
      }
      return false;
    }
    if (playerAction == '3') {
      if (pc->getCurrentCell()->search()) {
        pc->addScroll();
      }
      if (pc->getAttacked(hitRoll(), monster->rollDamage()) == 0) {
        cout << "You have died to a flying skull. Because you died to a lowly undead we are all doomed" << endl;
        return true;
      }
      if (preHealth == pc->getHealth()) {
        cout << "The flying skull missed you with its attack." << endl;
      }
      if (preHealth > pc->getHealth()) {
        cout << "The flying skull hit you. You have " << pc->getHealth() << "/35 health left" << endl;
      }
      return false;
    }
  }
  return false;
}

