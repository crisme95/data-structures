#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <set>
#include <map>

// defined in performance.cpp
void usage();

template <class T>
void bst_sort(std::map<T, int> &mp, std::ostream &ostr, int &output_count)
{
  // maps are already sorted
  output_count = 0;
  typename std::map<T, int>::iterator itr;
  for (itr = mp.begin(); itr != mp.end(); itr++)
  {
    // print out all the duplicates
    for (int i = 0; i < itr->second; i++)
    {
      ostr << itr->first << "\n";
      output_count++;
    }
  }
}

template <class T>
void bst_remove_duplicates(std::map<T, int> &mp, std::ostream &ostr, int &output_count)
{
  // maps are sorted by design which makes this very inefficient
  output_count = mp.size();
  typename std::map<T, int>::iterator itr;
  for (int i = 0; i < output_count; i++)
  {
    for (itr = mp.begin(); itr != mp.end(); itr++)
    {
      // check for the index that the element should be printout out
      if (itr->second == i)
      {
        ostr << itr->first << "\n";
        break;
      }
    }
  }
}

template <class T>
void bst_mode(std::map<T, int> &mp, std::ostream &ostr, int &output_count)
{
  output_count = 0;
  T modeVal;
  int mode = 0;
  typename std::map<T, int>::iterator itr = mp.begin();
  for (; itr != mp.end(); ++itr)
  {
    // compare amount of duplicates to mode
    if (itr->second >= mode)
    {
      modeVal = itr->first;
      mode = itr->second;
    }
  }

  // check if we got a mode
  if (mode != 0)
  {
    output_count = 1;
  }
  ostr << modeVal << "\n";
}

void bst_closest_pair(std::set<int> &st, std::ostream &ostr, int &output_count)
{
  assert(st.size() >= 2);
  output_count = 2;
  int best;
  int best_curr;
  int best_next;
  std::set<int>::iterator itr1 = st.begin();
  std::set<int>::iterator itr2 = st.begin();
  std::set<int>::iterator end = st.end();
  --end; // decrementing end iterator
  // the two elements with closest value must be next to each other in sorted order
  for (; itr1 != end; itr1++)
  {
    int current = *itr1;
    int next = *++itr1; // get next element
    --itr1;             // go back to where we started
    int diff = next - current;
    // ostr << *itr1 << " " << diff << " " << next << " - " << current << "\n";
    if (itr2 == st.begin() || diff < best)
    {
      best = diff;
      itr2 = itr1;
      best_curr = current;
      best_next = next;
    }
  }
  // print the two elements
  output_count = 2;
  ostr << best_curr << "\n";
  ostr << best_next << "\n";
}

template <class T>
void bst_first_sorted(std::map<T, int> &mp, std::ostream &ostr, int &output_count,
                      int optional_arg)
{
  assert(optional_arg >= 1);
  assert((int)mp.size() >= optional_arg);
  output_count = optional_arg;
  typename std::map<T, int>::iterator itr = mp.begin();
  int i = 0;
  // print out the amount of arguments the optional arg requires
  while (i < optional_arg)
  {
    int n = itr->second;

    // go through the duplicate values
    while (n != 0 && i < optional_arg)
    {
      ostr << itr->first << "\n";
      --n;
      ++i;
    }
    ++itr;
  }
}

void bst_test(const std::string &operation, const std::string &type,
              std::istream &istr, std::ostream &ostr,
              int &input_count, int &output_count, int optional_arg)
{

  // HINT: For the string element type, declare your binary search tree (BST) like this:
  // std::set<std::string> st;
  // OR
  // std::map<std::string,int> mp;

  if (type == "string")
  {
    std::set<std::string> st;
    std::map<std::string, int> mp;
    std::string s;
    input_count = 0;

    if (operation == "sort")
    {
      while (istr >> s)
      {
        mp[s]++;
        input_count++;
      }
      bst_sort(mp, ostr, output_count);
    }
    else if (operation == "remove_duplicates")
    {
      int index = 0;
      while (istr >> s)
      {
        std::map<std::string, int>::iterator itr = mp.find(s);
        if (itr == mp.end())
        {
          mp[s] = index;
          index++;
        }

        input_count++;
      }

      bst_remove_duplicates(mp, ostr, output_count);
    }
    else if (operation == "mode")
    {
      while (istr >> s)
      {
        mp[s]++;
        input_count++;
      }
      bst_mode(mp, ostr, output_count);
    }
    else if (operation == "first_sorted")
    {
      while (istr >> s)
      {
        mp[s]++;
        input_count++;
      }
      bst_first_sorted(mp, ostr, output_count, optional_arg);
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
    std::set<int> st;
    std::map<int, int> mp;
    int s;
    input_count = 0;

    if (operation == "sort")
    {
      while (istr >> s)
      {
        mp[s]++;
        input_count++;
      }
      bst_sort(mp, ostr, output_count);
    }
    else if (operation == "remove_duplicates")
    {
      int index = 0;
      while (istr >> s)
      {
        std::map<int, int>::iterator itr = mp.find(s);
        if (itr == mp.end())
        {
          mp[s] = index;
          index++;
        }

        input_count++;
      }

      bst_remove_duplicates(mp, ostr, output_count);
    }
    else if (operation == "mode")
    {
      while (istr >> s)
      {
        mp[s]++;
        input_count++;
      }
      bst_mode(mp, ostr, output_count);
    }

    else if (operation == "first_sorted")
    {
      while (istr >> s)
      {
        mp[s]++;
        input_count++;
      }
      bst_first_sorted(mp, ostr, output_count, optional_arg);
    }
    else if (operation == "closest_pair")
    {
      while (istr >> s)
      {
        st.insert(s);
        input_count++;
      }
      bst_closest_pair(st, ostr, output_count);
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
