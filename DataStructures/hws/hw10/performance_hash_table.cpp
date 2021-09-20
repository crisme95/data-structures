#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>

// defined in performance.cpp
void usage();

template <class T>
void ht_sort(const std::unordered_map<T, int> &um, std::ostream &ostr,
             int &output_count)
{
  ostr << "Not implemented"
       << "\n";
}

template <class T>
void ht_remove_duplicates(std::unordered_map<T, int> &um,
                          std::ostream &ostr,
                          int &output_count)
{
  // maps don't allow duplicates
  output_count = um.size();
  typename std::unordered_map<T, int>::iterator itr;
  for (int i = 0; i < output_count; i++)
  {
    for (itr = um.begin(); itr != um.end(); itr++)
    {
      // check where the element needs to be printed out
      // to stay in order
      if (itr->second == i)
      {
        ostr << itr->first << "\n";
        break;
      }
    }
  }
}

template <class T>
void ht_mode(std::unordered_map<T, int> &um, std::ostream &ostr, int &output_count)
{
  output_count = 0;
  T modeVal;
  int mode = 0;
  typename std::unordered_map<T, int>::iterator itr;
  for (itr = um.begin(); itr != um.end(); itr++)
  {
    // compare number of duplicates to mode
    if (itr->second >= mode)
    {
      modeVal = itr->first;
      mode = itr->second;
    }
  }
  if (mode != 0)
  {
    output_count = 1;
  }
  ostr << modeVal << "\n";
}

void ht_closest_pair(std::unordered_set<int> &us, std::ostream &ostr,
                     int &output_count)
{
  assert(us.size() >= 2);
  output_count = 2;
  int best;
  int best_curr;
  int best_next;
  std::unordered_set<int>::iterator itr1 = us.begin();
  std::unordered_set<int>::iterator itr2;
  for (; itr1 != us.end(); itr1++)
  {
    for (itr2 = us.begin(); itr2 != us.end(); itr2++)
    {
      // make sure we are not subracting itself
      if (itr2 != itr1)
      {
        int current = *itr1;
        int next = *itr2;
        int diff = abs(next - current);
        ostr << diff << " " << next << " - " << current << "\n";
        if (diff < best)
        {
          best = diff;
          best_curr = *itr1;
          best_next = *itr2;
        }
      }
    }
  }

  output_count = 2;
  ostr << best_curr << "\n";
  ostr << best_next << "\n";
}

void hash_table_test(const std::string &operation, const std::string &type,
                     std::istream &istr, std::ostream &ostr,
                     int &input_count, int &output_count, int optional_arg)
{

  // HINT: For the string element type, declare your hash table like this:
  // std::unordered_set<std::string> ht;
  // OR
  // std::unordered_map<std::string,int> ht;

  if (type == "string")
  {
    std::unordered_set<std::string> us;
    std::unordered_map<std::string, int> um;
    std::string s;
    input_count = 0;
    if (operation == "sort")
    {
      while (istr >> s)
      {
        um[s]++;
        input_count++;
      }
    }
    else if (operation == "remove_duplicates")
    {
      int index = 0;
      while (istr >> s)
      {
        std::unordered_map<std::string, int>::iterator itr = um.find(s);
        if (itr == um.end())
        {
          um[s] = index;
          index++;
        }
        input_count++;
      }
      ht_remove_duplicates(um, ostr, output_count);
    }
    else if (operation == "mode")
    {
      while (istr >> s)
      {
        um[s]++;
        input_count++;
      }
      ht_mode(um, ostr, output_count);
    }
    else
    {
      std::cerr << "Error: Unknown operation: " << operation << std::endl;
      usage();
      exit(0);
    }
  }
  else
  {
    assert(type == "integer");
    std::unordered_set<int> us;
    std::unordered_map<int, int> um;
    int s;
    input_count = 0;
    if (operation == "sort")
    {
      while (istr >> s)
      {
        um[s]++;
        input_count++;
      }
    }
    else if (operation == "remove_duplicates")
    {
      int index = 0;
      while (istr >> s)
      {
        std::unordered_map<int, int>::iterator itr = um.find(s);
        if (itr == um.end())
        {
          um[s] = index;
          index++;
        }
        input_count++;
      }
      ht_remove_duplicates(um, ostr, output_count);
    }
    else if (operation == "mode")
    {
      while (istr >> s)
      {
        um[s]++;
        input_count++;
      }
      ht_mode(um, ostr, output_count);
    }
    else if (operation == "closest_pair")
    {
      while (istr >> s)
      {
        us.insert(s);
        input_count++;
      }
      ht_closest_pair(us, ostr, output_count);
    }
    else
    {
      std::cerr << "Error: Unknown operation: " << operation << std::endl;
      usage();
      exit(0);
    }
  }

  // std::cerr << "Error: DATA STRUCTURE NOT IMPLEMENTED" << std::endl;
  // exit(0);
}
