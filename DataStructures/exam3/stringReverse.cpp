#include <iostream>
#include <string>

void reverseString(const std::string &og, std::string &change, unsigned int i)
{
  if (change.size() == og.size()){
    return;
  }

  change += og[i];
  std::cout << change << std::endl;
  reverseString(og, change, i - 1);

}

void reverse(std::string &og)
{
  std::string reversedString = "";
  reverseString(og, reversedString, og.size() - 1);
  og = reversedString;
}

int main()
{
  std::string a = "ThisIsEven";
  std::string b = "ThisIsOdd";
  std::string c(a);
  std::string d(b);
  reverse(c);
  reverse(d);
  std::cout << a << " reversed is " << c << std::endl;
  std::cout << b << " reversed is " << d << std::endl;

  return 0;
}
