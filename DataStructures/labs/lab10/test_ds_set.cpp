#include <iostream>
#include <string>
#include <utility>
#include <cassert>
#include <vector>

#include "ds_set.h"

int main()
{

  ds_set<std::string> set1;
  set1.insert("hello");
  set1.insert("good-bye");
  set1.insert("friend");
  set1.insert("abc");
  set1.insert("puppy");
  set1.insert("zebra");
  set1.insert("daddy");
  set1.insert("puppy"); // should recognize that this is a duplicate!

  assert(set1.sanity_check());
  assert(set1.size() == 7);

  ds_set<std::string>::iterator p = set1.begin();
  assert(p != set1.end() && *p == std::string("abc"));

  p = set1.find("foo");
  assert(p == set1.end());

  p = set1.find("puppy");
  assert(p != set1.end());
  assert(*p == "puppy");

  std::cout << "Here is the tree, printed sideways.\n"
            << "The indentation is proportional to the depth of the node\n"
            << "so that the value stored at the root is the only value printed\n"
            << "without indentation.  Also, for each node, the right subtree\n"
            << "can be found above where the node is printed and indented\n"
            << "relative to it\n";
  set1.print_as_sideways_tree(std::cout);
  std::cout << std::endl;

  // copy the set
  ds_set<std::string> set2(set1);
  assert(set1.sanity_check());
  assert(set2.sanity_check());
  assert(set1.size() == set2.size());

  //  Now add stuff to set2
  set2.insert(std::string("a"));
  set2.insert(std::string("b"));
  std::cout << "After inserting stuff:\n";
  set2.print_as_sideways_tree(std::cout);
  std::cout << std::endl;
  assert(set1.sanity_check());
  assert(set2.sanity_check());
  assert(set1.size() == set2.size() - 2);

  //  Now erase stuff from set2
  set2.erase("hello");
  set2.erase("a");
  set2.erase("hello"); // should recognize that it's not there anymore!
  set2.erase("abc");
  set2.erase("friend");
  std::cout << "After erasing stuff:\n";
  set2.print_as_sideways_tree(std::cout);
  std::cout << std::endl;
  assert(set1.sanity_check());
  assert(set2.sanity_check());
  assert(set1.size() == set2.size() + 2);

  // Checkpoints 2 & 3
  // Write code to test the forwards & backwards iterators!
  ds_set<int> set3;
  int tmp[] = {8, 4, 2, 6, 1, 3, 5, 7, 12, 10, 14, 9, 11, 13, 15};
  std::vector<int> test(tmp, tmp + 15);

  std::cout << "Balanced tree of ints from 1-15:" << std::endl;
  for (unsigned int i = 0; i < test.size(); i++)
  {
    set3.insert(test[i]);
  }

  set3.print_as_sideways_tree(std::cout);

  std::cout << "operator++ testing:" << std::endl;
  for (ds_set<int>::iterator s3_itr = set3.begin(); s3_itr != set3.end(); s3_itr++)
  {
    std::cout << *s3_itr << std::endl;
  }

  std::cout << "operator-- testing:" << std::endl;
  for (ds_set<int>::iterator s3_itr = set3.end(); s3_itr != set3.begin(); --s3_itr)
  {
    std::cout << *s3_itr << std::endl;
  }

  return 0;
}
