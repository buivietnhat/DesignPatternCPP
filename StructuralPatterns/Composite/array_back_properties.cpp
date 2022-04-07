//
// Created by Nhat Bui on 07/04/2022.
//

#include <iostream>
#include <vector>
#include <array>
#include <numeric>

using namespace std;

class Creature
{
  int strength, agility, intelligence;

public:
  Creature(int strength, int agility, int intelligence) : strength(strength),
    agility(agility), intelligence(intelligence) {}

  int get_strength() const
  {
    return strength;
  }

  void set_strength(int strength)
  {
    Creature::strength = strength;
  }

  int get_agility() const
  {
    return agility;
  }

  void set_agility(int agility)
  {
    Creature::agility = agility;
  }

  int get_intelligence() const
  {
    return intelligence;
  }

  void set_intelligence(int intelligence)
  {
    Creature::intelligence = intelligence;
  }

  // some aggregate statistics
  int sum() const
  {
    return strength + agility + intelligence;
  }

  double average() const
  {
    return sum() / 3.0;
  }

  int max() const
  {
    return ::max(strength, ::max(agility, intelligence));
  }

};

// this implementation above doesn't scale well when it comes to add new properties
// array-back properties implementation

class BetterCreature
{
  enum Ability { str, agl, intl, count};
  array<int,count> abilities;

public:
  BetterCreature(){}

  BetterCreature(int strength, int agility, int intelligence)
  {
    abilities[str] = strength;
    abilities[agl] = agility;
    abilities[intl] = intelligence;
  }


  int get_strength() const
  {
    return abilities[str];
  }

  void set_strength(int value)
  {
    abilities[str] = value;
  }

  int sum() const
  {
    return std::accumulate(abilities.begin(), abilities.end(), 0);
  }

  double average() const
  {
    return sum() / (double)count;
  }

  int max() const
  {
    return *max_element(abilities.begin(), abilities.end());
  }
};

int main()
{

  auto goblin = BetterCreature{1, 2, 2};

  cout << "Sum is " <<  goblin.sum() << endl;
  cout << "Average is " << goblin.average() << endl;
  cout << "Max element is " << goblin.max() << endl;

}

