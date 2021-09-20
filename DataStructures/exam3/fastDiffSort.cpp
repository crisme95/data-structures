#include <iostream>
#include <vector>
#include <set>

typedef std::set<int> intset;
typedef intset::const_iterator int_it;

std::vector<int> fastDiffSort(const intset &s1, const intset &s2)
{
  std::vector<int> ret;
  int_it it2 = s2.begin();
  for (int_it it1 = s1.begin(); it1 != s1.end(); it1++)
  {
    if (*it1 != *it2)
    {
      ret.push_back(*it1);
    }
    else
    {
      it2++;
    }
  }
  return ret;
}

int main()
{
  std::set<int> a{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  std::set<int> b{5, 10, 15};

  std::vector<int> fastSortComplete = fastDiffSort(a, b);
  for (int i = 0; i < fastSortComplete.size(); i++)
  {
    std::cout << fastSortComplete[i] << " ";
  }

  std::cout << std::endl;

  return 0;
}