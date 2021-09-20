#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <queue>

// defined in performance.cpp
void usage();

template <class T>
void pq_sort(std::priority_queue<T, std::vector<T>, std::greater<T>> &pq,
             std::ostream &ostr,
             int &output_count)
{
  // priority queue is already sorted
  output_count = pq.size();
  while (!pq.empty())
  {
    ostr << pq.top() << "\n";
    pq.pop();
  }
}

template <class T>
void pq_remove_duplicates(std::priority_queue<T, std::vector<T>, std::greater<T>> &pq,
                          std::ostream &ostr,
                          int &output_count)
{
  output_count = 0;
  while (!pq.empty())
  {
    ostr << pq.top() << "\n";
    output_count++;
    T compare = pq.top();
    pq.pop();

    // skip over duplicates
    if (!pq.empty())
    {
      while (compare == pq.top())
      {
        pq.pop();
      }
    }
  }
}

template <class T>
void pq_mode(std::priority_queue<T, std::vector<T>, std::greater<T>> &pq,
             std::ostream &ostr,
             int &output_count)
{
  output_count = 0;
  T modeVal;
  int mode = 0;
  while (!pq.empty())
  {
    int numDup = 1;
    T comp = pq.top();
    pq.pop();
    if (!pq.empty())
    {
      // while there are duplicates keep popping
      while (comp == pq.top())
      {
        numDup++;
        pq.pop();
      }
    }
    if (numDup >= mode)
    {
      modeVal = comp;
      mode = numDup;
    }
  }
  output_count = 1;
  ostr << modeVal << "\n";
}

void pq_closest_pair(std::priority_queue<int, std::vector<int>, std::greater<int>> &pq,
                     std::ostream &ostr,
                     int &output_count)
{
  assert(pq.size() >= 2);
  // priority queue is already sorted
  output_count = 2;
  int best;
  int pair1;
  int pair2;
  int stop = pq.size();

  // the two elements with closest value must be next to each other in sorted order
  while (!pq.empty())
  {
    int current = pq.top();
    pq.pop();
    --stop;

    // stop loop if we popped all the elements
    if (stop == 0)
    {
      break;
    }
    int next = pq.top();
    int diff = next - current;
    ostr << diff << " " << next << " " << current << "\n";
    if (diff < best)
    {
      best = diff;
      pair1 = current;
      pair2 = next;
    }
  }
  ostr << pair1 << "\n";
  ostr << pair2 << "\n";
}

template <class T>
void pq_first_sorted(std::priority_queue<T, std::vector<T>, std::greater<T>> &pq, std::ostream &ostr,
                     int &output_count,
                     int &optional_arg)
{
  assert(optional_arg >= 1);
  assert((int)pq.size() >= optional_arg);
  output_count = optional_arg;
  int stop = optional_arg; // keeps track of when we need to stop

  // make sure we don't seg fault
  while (!pq.empty())
  {
    ostr << pq.top() << "\n";
    pq.pop();
    --stop;

    // check if we printed out the specified number of elements
    if (stop == 0)
    {
      break;
    }
  }
}

void priority_queue_test(const std::string &operation, const std::string &type,
                         std::istream &istr, std::ostream &ostr,
                         int &input_count, int &output_count, int optional_arg)
{

  // HINT: For the string element type, declare your priority_queue like this:

  // std::priority_queue<std::string,std::vector<std::string> > pq;
  // (this will make a "max" priority queue, with big values at the top)

  // OR

  // std::priority_queue<std::string,std::vector<std::string>, std::greater<std::string> > pq;
  // (this will make a "min" priority queue, with big values at the bottom)

  if (type == "string")
  {
    std::priority_queue<std::string, std::vector<std::string>, std::greater<std::string>> pq;
    std::string s;
    input_count = 0;
    while (istr >> s)
    {
      pq.push(s);
      input_count++;
    }

    if (operation == "sort")
    {
      pq_sort(pq, ostr, output_count);
    }
    else if (operation == "remove_duplicates")
    {
      pq_remove_duplicates(pq, ostr, output_count);
    }
    else if (operation == "mode")
    {
      pq_mode(pq, ostr, output_count);
    }
    else if (operation == "first_sorted")
    {
      pq_first_sorted(pq, ostr, output_count, optional_arg);
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
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    int s;
    input_count = 0;
    while (istr >> s)
    {
      pq.push(s);
      input_count++;
    }
    if (operation == "sort")
    {
      pq_sort(pq, ostr, output_count);
    }
    else if (operation == "remove_duplicates")
    {
      pq_remove_duplicates(pq, ostr, output_count);
    }
    else if (operation == "mode")
    {
      pq_mode(pq, ostr, output_count);
    }
    else if (operation == "closest_pair")
    {
      pq_closest_pair(pq, ostr, output_count);
    }
    else if (operation == "first_sorted")
    {
      pq_first_sorted(pq, ostr, output_count, optional_arg);
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
