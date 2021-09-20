//
// NOTE: YOUR FINAL SUBMITTED VERSION SHOULD ONLY CONTAIN
//       CHANGES TO MoreTests()
//

#include <iostream>
#include <cmath>
#include <cassert>
#include <list>

#include "unrolled.h"

// ===================================================================
// This function compares an unrolled linked list to an STL list.  It
// returns true if the lists are the same size, and contain the same
// elements in the same order.
template <class T>
bool SAME(UnrolledLL<T> &a, std::list<T> &b)
{
  if (a.size() != b.size())
    return false;
  typename UnrolledLL<T>::iterator a_iter = a.begin();
  typename std::list<T>::iterator b_iter = b.begin();
  while (a_iter != a.end() && b_iter != b.end())
  {
    if (*a_iter != *b_iter)
      return false;
    a_iter++;
    b_iter++;
  }
  // if(a_iter == a.end())
  //   std::cout << "A" << std::endl;
  // if(b_iter == b.end())
  //   std::cout << "B" << std::endl;
  assert(a_iter == a.end() && b_iter == b.end());
  return true;
}

// ===================================================================
void BasicTests();
void MoreTests();

int main()
{
  BasicTests();
  MoreTests();
  std::cout << "Finished MoreTests()" << std::endl;
}

// ===================================================================
// NOTE: Your internal data structure may be different (& thus print
// differently), depending on how you implement your internal member
// functions.  That's ok!
void BasicTests()
{

  // make two matching list of integers, one using an unrolled list,
  // one using an STL list.  They should stay the "SAME" throughout
  // these tests.
  UnrolledLL<int> a;
  std::list<int> b;
  for (int i = 10; i < 30; ++i)
  {
    a.push_back(i);
    b.push_back(i);
  }

  // iterate through the integers and print them out
  std::cout << "the integers from 10->29" << std::endl;
  for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++)
  {
    std::cout << " " << *itr;
  }
  std::cout << std::endl
            << std::endl;
  assert(SAME(a, b));

  // use the output operator to print the underlying representation
  std::cout << "initial" << std::endl;
  a.print(std::cout);
  std::cout << std::endl;

  // testing some basic functions in the class
  std::cout << "some editing with pop & push" << std::endl;
  assert(a.size() == 20);
  assert(a.front() == 10);
  assert(a.back() == 29);
  a.pop_front();
  b.pop_front();
  assert(a.size() == 19);
  assert(a.front() == 11);
  a.pop_back();
  b.pop_back();
  assert(a.size() == 18);
  assert(a.back() == 28);
  a.print(std::cout);
  std::cout << std::endl;
  assert(SAME(a, b));

  // more editing
  std::cout << "more editing with pop & push" << std::endl;
  a.pop_front();
  a.pop_front();
  a.pop_front();
  a.pop_front();
  a.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  a.print(std::cout);
  assert(SAME(a, b));
  a.pop_back();
  b.pop_back();
  a.print(std::cout);
  assert(SAME(a, b));
  assert(a.size() == 12);
  assert(a.front() == 16);
  assert(a.back() == 27);
  a.push_front(90);
  a.push_front(91);
  a.push_front(92);
  a.push_front(93);
  b.push_front(90);
  b.push_front(91);
  b.push_front(92);
  b.push_front(93);
  a.print(std::cout);
  std::cout << std::endl;
  assert(a.size() == 16);
  assert(a.front() == 93);
  assert(SAME(a, b));

  // erase the multiples of 3
  std::cout << "erase the multiples of 3" << std::endl;
  UnrolledLL<int>::iterator a_iter = a.begin();
  while (a_iter != a.end())
  {
    if (*a_iter % 3 == 0)
    {
      a_iter = a.erase(a_iter);
    }
    else
    {
      a_iter++;
    }
  }
  std::list<int>::iterator b_iter = b.begin();
  while (b_iter != b.end())
  {
    if (*b_iter % 3 == 0)
    {
      b_iter = b.erase(b_iter);
    }
    else
    {
      b_iter++;
    }
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert(a.size() == 10);
  assert(SAME(a, b));

  // inserting elements
  std::cout << "do some inserts" << std::endl;
  // insert some stuff
  for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++)
  {
    if (*itr == 92 || *itr == 16 || *itr == 19 || *itr == 26)
    {
      itr = a.insert(itr, 77);
      itr++;
    }
  }
  for (std::list<int>::iterator itr = b.begin(); itr != b.end(); itr++)
  {
    if (*itr == 92 || *itr == 16 || *itr == 19 || *itr == 26)
    {
      itr = b.insert(itr, 77);
      itr++;
    }
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert(a.size() == 14);
  assert(SAME(a, b));

  // overflowing an insert
  std::cout << "insert that overflows the node" << std::endl;
  for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++)
  {
    if (*itr == 17)
    {
      itr = a.insert(itr, 88);
      itr++;
    }
  }
  for (std::list<int>::iterator itr = b.begin(); itr != b.end(); itr++)
  {
    if (*itr == 17)
    {
      itr = b.insert(itr, 88);
      itr++;
    }
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert(a.size() == 15);
  assert(SAME(a, b));

  // more erasing
  std::cout << "erasing that removes a node" << std::endl;
  a_iter = a.begin();
  while (a_iter != a.end())
  {
    if (*a_iter == 77 || *a_iter == 16 || *a_iter == 88)
    {
      a_iter = a.erase(a_iter);
    }
    else
    {
      a_iter++;
    }
  }
  b_iter = b.begin();
  while (b_iter != b.end())
  {
    if (*b_iter == 77 || *b_iter == 16 || *b_iter == 88)
    {
      b_iter = b.erase(b_iter);
    }
    else
    {
      b_iter++;
    }
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert(a.size() == 9);
  assert(SAME(a, b));
  std::cout << "Finished BasicTests()" << std::endl;
}

// ===================================================================
void MoreTests()
{

  //
  //
  // ADD YOUR OWN TEST CASES HERE
  // ADD COMMENTS TO EXPLAIN THE PURPOSE OF THE TEST CASES
  // TEST CASES SHOULD FINISH AND NOT CRASH. OUTPUT IS HELPFUL AS WELL.
  //
  //

  UnrolledLL<char> a;
  std::list<char> b;

  for (int i = 10; i < 30; ++i)
  {
    a.push_back('c');
    b.push_back('c');
  }

  // iterate through the chars and print them out
  std::cout << "prints out the chars" << std::endl;
  for (UnrolledLL<char>::iterator itr = a.begin(); itr != a.end(); itr++)
  {
    std::cout << " " << *itr;
  }
  std::cout << std::endl
            << std::endl;
  assert(SAME(a, b));

  std::cout << "some editing with pop & push" << std::endl;
  assert(a.size() == 20);
  assert(a.front() == 'c');
  assert(a.back() == 'c');
  a.pop_front();
  b.pop_front();
  assert(a.size() == 19);
  assert(a.front() == 'c');
  a.pop_back();
  b.pop_back();
  assert(a.size() == 18);
  assert(a.back() == 'c');
  a.print(std::cout);
  std::cout << std::endl;
  assert(SAME(a, b));

  // tests pop_front, pop_back, and push_front
  std::cout << "more editing with pop & push" << std::endl;
  a.pop_front();
  a.pop_front();
  a.pop_front();
  a.pop_front();
  a.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  a.print(std::cout);
  assert(SAME(a, b));
  a.pop_back();
  b.pop_back();
  a.print(std::cout);
  assert(SAME(a, b));
  assert(a.size() == 12);
  assert(a.front() == 'c');
  assert(a.back() == 'c');
  a.push_front('d');
  a.push_front('d');
  a.push_front('d');
  a.push_front('d');
  b.push_front('d');
  b.push_front('d');
  b.push_front('d');
  b.push_front('d');
  a.print(std::cout);
  std::cout << std::endl;
  assert(a.size() == 16);
  assert(a.front() == 'd');
  assert(SAME(a, b));

  // tests copy constructor
  UnrolledLL<char> c = a;
  assert(SAME(c, b));
}
