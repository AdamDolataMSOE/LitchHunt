/*
 * hazards.h
 *
 *      Author: [Adam Dolata]
 */

#ifndef HAZARDS_H_
#define HAZARDS_H_

class Hazard {
private:
  int maxDamage;
public:
  virtual ~Hazard();
  virtual int rollDamage(); //returns the amount of damage the hazard does
};

class SpikeTrap : public Hazard {
private:
  int maxDamage = 10;
public:
  SpikeTrap();
  ~SpikeTrap();
  int rollDamage() override;
};

//---Monsters-----------------------------------------------------------------------------------------------------------

class Monster : public Hazard {
private:
  int health, magicArmor, physicalArmor; //the health of the monster and the values needed to hit the monster
public:
  virtual ~Monster();
  virtual bool getAttacked(char type, int toHit, int damage); //determines when a monster is hit, how much damage it takes,
  //and if it dies rereturns true if it dies else false
  virtual int rollDamage();
};

class Litch : public Monster {
  int health = 35, magicArmor = 13, physicalArmor = 7, maxDamage = 10;
public:
  ~Litch() override;
  bool getAttacked(char type, int toHit, int damage) override;
  int rollDamage() override;
};

class FlyingSkull : public Monster {
  int health = 10, magicArmor = 5, physicalArmor = 10, maxDamage = 5;
public:
  FlyingSkull();
  ~FlyingSkull() override;
  bool getAttacked(char type, int toHit, int damage) override;
  int rollDamage() override;
};

#endif /* HAZARDS_H_ */