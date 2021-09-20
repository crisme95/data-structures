#ifndef SUPERHERO_H
#define SUPERHERO_H

#include <iostream>
#include <string>

class Superhero
{
public:
  Superhero(const std::string &h, const std::string &i, const std::string &p) : heroName(h), identity(i), power(p), isHero(true) {}

  bool operator==(const std::string &guess) { return guess == identity; }
  bool operator!=(const std::string &guess) { return guess != identity; }
  bool operator>(const Superhero &hero)
  {
    // std::cout << power << " > " << hero.getPower() << std::endl;
    if (power == "Fire" && hero.getPower() == "Wood")
      return true;
    else if (power == "Wood" && hero.getPower() == "Water")
      return true;
    else if (power == "Water" && hero.getPower() == "Fire")
      return true;
    else if (power == "Laser" && hero.getPower() == "Wood")
      return true;
    else if (power == "Speed" && hero.getPower() == "Fire")
      return true;
    else
      return false;
  }

  void operator-()
  {
    if (isHero == true)
    {
      isHero = false;
    }
    else
    {
      isHero = true;
    }
  }

  friend std::ostream &operator<<(std::ostream &ostr, const Superhero &hero)
  {
    if (hero.isGood() == true)
    {
      ostr << "Superhero " << hero.getName() << " has power " << hero.getPower() << std::endl;
    }
    else
    {
      ostr << "Supervillian " << hero.getName() << " has power " << hero.getPower() << std::endl;
    }

    return ostr;
  }

  std::string getName() const { return heroName; }
  std::string getPower() const { return power; }
  std::string getTrueIdentity() const { return identity; }
  bool isGood() const { return isHero; }

private:
  std::string heroName;
  std::string identity;
  std::string power;
  bool isHero;
};

#endif