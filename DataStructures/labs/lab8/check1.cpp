#include <iostream>
#include <fstream>
#include <map>

int main(int argc, char *argv[])
{
  int i;
  std::map<int, int> counters; // store each integer and an associated counter
  int max = 0;

  std::ifstream istr(argv[1]);
  // read the input, keeping track of each integer and how often we see it
  while (istr >> i)
    ++counters[i];

  // print the integers and associated counts
  std::map<int, int>::const_iterator it;
  for (it = counters.begin(); it != counters.end(); ++it)
  {
    std::cout << it->first << "\t" << it->second << std::endl;
  }

  // finds max amount of times an integer is repeated
  for (it = counters.begin(); it != counters.end(); ++it)
  {
    if (it->second > max)
      max = it->second;
  }

  std::cout << std::endl
            << "The mode(s) are: ";

  // prints out the mode(s) of the entered integers
  for (it = counters.begin(); it != counters.end(); ++it)
  {
    if (it->second == max)
      std::cout << it->first << " ";
  }
  std::cout << std::endl;

  return 0;
}