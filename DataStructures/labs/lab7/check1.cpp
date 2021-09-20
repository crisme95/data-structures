#include <iostream>
#include <iomanip>

int count = 0;

int paths(int x, int y)
{
  if (x == 0 || y == 0)
  {
    return 1;
  }
  else
  {
    return (paths(x, y - 1) + paths(x - 1, y));
  }
}

int main()
{
  int x = 2;
  int y = 2;
  std::cout << paths(x, y) << std::endl;

  return 0;
}