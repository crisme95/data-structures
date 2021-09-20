#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <list>

// defined in performance.cpp
void usage();

template <class T>
void list_sort(std::list<T> &lst, std::ostream &ostr, int &output_count)
{
  // use the list sort algorithm
  lst.sort();
  output_count = lst.size();
  typename std::list<T>::iterator itr;
  for (itr = lst.begin(); itr != lst.end(); itr++)
    ostr << *itr << "\n";
}

template <class T>
void list_remove_duplicates(const std::list<T> &lst, std::ostream &ostr,
                            int &output_count)
{
  // don't reorder the elements, just do all pairwise comparisons
  output_count = 0;
  typename std::list<T>::const_iterator itr1;
  for (itr1 = lst.begin(); itr1 != lst.end(); itr1++)
  {
    bool dup = false;
    typename std::list<T>::const_iterator itr2;
    for (itr2 = lst.begin(); itr2 != itr1; itr2++)
    {
      if (*itr1 == *itr2)
      {
        dup = true;
        break;
      }
    }
    // if it has not already been added to the output list
    if (!dup)
    {
      ostr << *itr1 << "\n";
      output_count++;
    }
  }
}

template <class T>
void list_mode(std::list<T> &lst, std::ostream &ostr, int &output_count)
{
  // use the list sort algorithm
  lst.sort();
  int current_count = 1;
  T mode;
  int mode_count = 0;
  // keep track of two iterators into the structure
  typename std::list<T>::iterator current = lst.begin();
  ++current;
  typename std::list<T>::iterator previous = lst.begin();
  for (; current != lst.end(); ++current, ++previous)
  {
    if (*current == *previous)
    {
      // if they are the same element increment the count
      current_count++;
    }
    else if (current_count >= mode_count)
    {
      // found a new mode!
      mode = *previous;
      mode_count = current_count;
      current_count = 1;
    }
    else
    {
      current_count = 1;
    }
  }
  if (current_count >= mode_count)
  {
    // last entry is a new mode!
    mode = *previous;
    mode_count = current_count;
  }

  output_count = 1;
  ostr << mode << "\n";
}

void list_closest_pair(std::list<int> &lst,
                       std::ostream &ostr,
                       int &output_count)
{
  assert(lst.size() >= 2);
  // use the vector sort algorithm
  lst.sort();
  output_count = 2;
  int best;
  int best_curr;
  int best_next;
  std::list<int>::iterator itr1 = lst.begin();
  std::list<int>::iterator itr2 = lst.begin();
  std::list<int>::iterator end = lst.end();
  --end; // decrementing end iterator
  // the two elements with closest value must be next to each other in sorted order
  for (; itr1 != end; itr1++)
  {
    int current = *itr1;
    int next = *++itr1; // get next element
    --itr1;             // go back to where we started
    int diff = next - current;
    // ostr << *itr1 << " " << diff << " " << next << " - " << current << "\n";
    if (itr2 == lst.begin() || diff < best)
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
void list_first_sorted(std::list<T> &lst,
                       std::ostream &ostr,
                       int &output_count,
                       int optional_arg)
{
  assert(optional_arg >= 1);
  assert((int)lst.size() >= optional_arg);
  // use the vector sort algorithm
  lst.sort();
  output_count = optional_arg;
  typename std::list<T>::iterator itr = lst.begin();
  for (int i = 0; i < optional_arg; i++, itr++)
  {
    ostr << *itr << "\n";
  }
}

void list_test(const std::string &operation, const std::string &type,
               std::istream &istr, std::ostream &ostr,
               int &input_count, int &output_count, int optional_arg)
{

  // HINT: For the string element type, declare your list like this:
  // std::list<std::string> lst;

  if (type == "string")
  {
    std::list<std::string> lst;
    std::string s;
    input_count = 0;
    while (istr >> s)
    {
      lst.push_back(s);
      input_count++;
    }
    if (operation == "sort")
    {
      list_sort(lst, ostr, output_count);
    }
    else if (operation == "remove_duplicates")
    {
      list_remove_duplicates(lst, ostr, output_count);
    }
    else if (operation == "mode")
    {
      list_mode(lst, ostr, output_count);
    }
    else if (operation == "first_sorted")
    {
      list_first_sorted(lst, ostr, output_count, optional_arg);
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
    std::list<int> lst;
    int v;
    input_count = 0;
    while (istr >> v)
    {
      lst.push_back(v);
      input_count++;
    }
    if (operation == "sort")
    {
      list_sort(lst, ostr, output_count);
    }
    else if (operation == "remove_duplicates")
    {
      list_remove_duplicates(lst, ostr, output_count);
    }
    else if (operation == "mode")
    {
      list_mode(lst, ostr, output_count);
    }
    else if (operation == "first_sorted")
    {
      list_first_sorted(lst, ostr, output_count, optional_arg);
    }
    else if (operation == "closest_pair")
    {
      list_closest_pair(lst, ostr, output_count);
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
