#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <bits/stdc++.h>

typedef std::map<std::string, std::pair<int, std::pair<int, std::vector<std::string>>>> COSTUME_SHOP_TYPE;
typedef std::map<std::pair<std::string, std::string>, std::string> PEOPLE_TYPE;

// prototypes for the helper functions
void addCostume(COSTUME_SHOP_TYPE &costume_shop);
void rentCostume(COSTUME_SHOP_TYPE &costume_shop, PEOPLE_TYPE &people);
void lookup(COSTUME_SHOP_TYPE &costume_shop);
void printPeople(const PEOPLE_TYPE &people);

int main()
{
  // two data structures store all of the information for efficiency
  COSTUME_SHOP_TYPE costume_shop;
  PEOPLE_TYPE people;
  char c;

  while (std::cin >> c)
  {
    if (c == 'a')
    {
      addCostume(costume_shop);
    }
    else if (c == 'r')
    {
      rentCostume(costume_shop, people);
    }
    else if (c == 'l')
    {
      lookup(costume_shop);
    }
    else if (c == 'p')
    {
      printPeople(people);
    }
    else
    {
      std::cerr << "error unknown char " << c << std::endl;
      exit(0);
    }
  }

  return 0;
}

void addCostume(COSTUME_SHOP_TYPE &costume_shop)
{
  std::string costume_name;
  int num;
  std::cin >> costume_name >> num;

  costume_shop[costume_name].first += num;        // stores the total number of costumes, stays constant
  costume_shop[costume_name].second.first += num; // stores the total number of costumes, changes as people rent and return the costume

  // prints out how many costumes are being added
  if (num < 2)
  {
    std::cout << "Added " << num << " " << costume_name << " costume." << std::endl;
  }
  else
  {
    std::cout << "Added " << num << " " << costume_name << " costumes." << std::endl;
  }
}

void rentCostume(COSTUME_SHOP_TYPE &costume_shop, PEOPLE_TYPE &people)
{
  std::string first_name;
  std::string last_name;
  std::string costume_name;
  std::cin >> first_name >> last_name >> costume_name;

  // pair where the first element is the person's last name so that
  // it can be sorted alphabetically by last name
  const std::pair<std::string, std::string> tmp (last_name, first_name);

  // checks if person exists in the map
  PEOPLE_TYPE::iterator p_itr = people.find(tmp);
  if (p_itr == people.end())
  {
    people[tmp] = "";
  }

  // checks if the costume is available or the person already has the costume
  COSTUME_SHOP_TYPE::iterator c_itr = costume_shop.find(costume_name);
  if (c_itr == costume_shop.end())
  {
    std::cout << "The shop doesn't carry " << costume_name << " costumes." << std::endl;
  }
  else if (costume_shop[costume_name].second.first < 1)
  {
    std::cout << "No " << costume_name << " costumes available." << std::endl;
  }
  else if (people[tmp] == costume_name)
  {
    std::cout << tmp.second << " " << tmp.first << " already has a " << costume_name << " costume." << std::endl;
  }
  else
  {
    const std::string p_name = tmp.second + " " + tmp.first; // stores the name of the person

    if (people[tmp] == "")
    {
      std::cout << tmp.second << " " << tmp.first << " rents a " << costume_name << " costume." << std::endl;

      costume_shop[costume_name].second.first--;                  // takes the costume the person wants to rent out of inventory
      costume_shop[costume_name].second.second.push_back(p_name); // adds person to the list for the costume they rented
      people[tmp] = costume_name;                                 // stores what costume the person currently has
    }
    else
    {
      std::cout << tmp.second << " " << tmp.first << " returns a " << people[tmp] << " costume before renting a " << costume_name << " costume." << std::endl;

      costume_shop[people[tmp]].second.first++; // adds the costume the person is returning back to the inventory

      // deletes the person's name from the list of the costume they're returning
      std::vector<std::string>::iterator c_itr = std::find(costume_shop[people[tmp]].second.second.begin(), costume_shop[people[tmp]].second.second.end(), p_name);
      if (c_itr != costume_shop[people[tmp]].second.second.end())
        costume_shop[people[tmp]].second.second.erase(c_itr);

      costume_shop[costume_name].second.first--;                  // takes the costume the person wants to rent out of inventory
      costume_shop[costume_name].second.second.push_back(p_name); // adds person to the list for the costume they rented
      people[tmp] = costume_name;                                 // stores what costume the person currently has
    }
  }
}

void lookup(COSTUME_SHOP_TYPE &costume_shop)
{
  std::string costume_name;
  std::cin >> costume_name;

  // checks if the costume exists in the inventory
  COSTUME_SHOP_TYPE::iterator c_itr = costume_shop.find(costume_name);
  if (c_itr == costume_shop.end())
  {
    std::cout << "The shop doesn't carry " << costume_name << " costumes." << std::endl;
  }
  else
  {
    std::cout << "Shop info for " << costume_name << " costumes:" << std::endl;

    // checks if there are any copies available, if not then nothing gets printed
    if (costume_shop[costume_name].second.first > 0)
    {
      // prints out how many copies are available
      if (costume_shop[costume_name].second.first < 2)
      {
        std::cout << "  " << costume_shop[costume_name].second.first << " copy available" << std::endl;
      }
      else
      {
        std::cout << "  " << costume_shop[costume_name].second.first << " copies available" << std::endl;
      }
    }

    // checks if there are people currently renting the costume, if not then nothing gets printed
    if (costume_shop[costume_name].first - costume_shop[costume_name].second.first > 0)
    {
      // prints out how many copies are currently being rented
      if ((costume_shop[costume_name].first - costume_shop[costume_name].second.first) < 2)
      {
        std::cout << "  " << (costume_shop[costume_name].first - costume_shop[costume_name].second.first) << " copy rented by:" << std::endl;
      }
      else
      {
        std::cout << "  " << (costume_shop[costume_name].first - costume_shop[costume_name].second.first) << " copies rented by:" << std::endl;
      }

      // prints out the people who are currently renting the costume
      for (unsigned int i = 0; i < costume_shop[costume_name].second.second.size(); i++)
      {
        std::cout << "    " << costume_shop[costume_name].second.second[i] << std::endl;
      }
    }
  }
}

void printPeople(const PEOPLE_TYPE &people)
{
  // checks how many people are stored in the map
  if (people.size() > 1)
  {
    std::cout << "Costume info for the " << people.size() << " party attendees:" << std::endl;
  }
  else
  {
    std::cout << "Costume info for the " << people.size() << " party attendee:" << std::endl;
  }

  // loops through the map and prints out the person's costume
  for (PEOPLE_TYPE::const_iterator it = people.begin(); it != people.end(); ++it)
  {
    if (it->second == "")
    {
      std::cout << "  " << it->first.second << " " << it->first.first << " does not have a costume." << std::endl;
    }
    else
    {
      std::cout << "  " << it->first.second << " " << it->first.first << " is wearing a " << it->second << " costume." << std::endl;
    }
  }
}
