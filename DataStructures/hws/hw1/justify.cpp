#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <string>

// Creates vector with text from the .txt file
void read_txt(std::vector<std::string> &txt_file, std::ifstream &txt_in, unsigned int width)
{
  std::string x;

  while (txt_in >> x)
  { // Checks if the word is longer than the width
    if (x.length() > width)
    {
      // Loops until the word is shorter than the width
      while (x.length() > width)
      {
        txt_file.push_back(x.substr(0, width - 1) + "-");
        x = x.substr(width - 1, x.length());
      }
    }
    txt_file.push_back(x);
  }
}

std::vector<std::string> flush_left(const std::vector<std::string> &txt_file, unsigned int width)
{
  std::vector<std::string> left_complete; // Empty vector that will have flush_left strings inserted
  unsigned int i = 0;

  while (i < txt_file.size())
  {
    std::string temp = txt_file[i]; // String with first word of each line
    ++i;

    while (temp.length() < width)
    {
      // If adding word to string fits the width then it gets added on
      if ((temp.length() + txt_file[i].length()) < width)
      {
        temp = temp + " " + txt_file[i];
        ++i;
      }
      else
      {
        while (temp.length() < width) // If not, this loop adds spaces to end of string
        {
          temp = temp + " ";
        }
      }
    }
    temp = "| " + temp;
    temp = temp + " |";
    left_complete.push_back(temp); //Add completed line to local vector
  }
  left_complete.insert(left_complete.begin(), std::string(width + 4, '-'));
  left_complete.insert(left_complete.end(), std::string(width + 4, '-'));

  return left_complete; // Returns completed vector
}

std::vector<std::string> flush_right(const std::vector<std::string> &txt_file, unsigned int width)
{
  std::vector<std::string> right_complete; // Empty vector that will have flush_left strings inserted
  unsigned int i = 0;

  while (i < txt_file.size())
  {
    std::string temp = txt_file[i]; // String with first word of each line
    ++i;

    while (temp.length() < width)
    {
      // If adding word to string fits the width then it gets added on
      if ((temp.length() + txt_file[i].length()) < width)
      {
        temp = temp + " " + txt_file[i];
        ++i;
      }
      else
      {
        while (temp.length() < width) // If not, this loop adds spaces to front of string
        {
          temp = " " + temp;
        }
      }
    }
    temp = "| " + temp;
    temp = temp + " |";
    right_complete.push_back(temp); // Add completed line to local vector
  }
  right_complete.insert(right_complete.begin(), std::string(width + 4, '-'));
  right_complete.insert(right_complete.end(), std::string(width + 4, '-'));

  return right_complete; // Returns completed vector
}

std::vector<std::string> full_justify(const std::vector<std::string> &txt_file, unsigned int width)
{
  std::vector<std::string> full_complete; // Empty vector where full_justified strings are inserted
  unsigned int i = 0;

  while (i < txt_file.size())
  {
    std::string temp = txt_file[i];
    std::string final_line = "";
    std::vector<std::string> vec_temp;
    vec_temp.push_back(txt_file[i]);
    unsigned int len = temp.length();
    ++i;

    while (len < width)
    {
      // If adding word to string fits the width then it gets added on
      if ((temp.length() + txt_file[i].length()) < width)
      {
        temp = temp + " " + txt_file[i];
        vec_temp.push_back(" " + txt_file[i]);
        len = temp.length();
        ++i;
      }
      else
      {
        len = temp.length();
        for (int n = 0; n < vec_temp.size(); ++n){
          if (len < width){
            std::string temp_word = vec_temp[n];
            temp_word += " ";
            vec_temp[n] = temp_word;
            ++len;
          }else{
            break;
          }
        }
      }
      for (int j = 0; j < vec_temp.size(); ++j){
        final_line += vec_temp[j];
      }
    }
    final_line = "| " + final_line;
    final_line = final_line + " |";
    full_complete.push_back(final_line); // Add completed line to local vector
  }
  full_complete.insert(full_complete.begin(), std::string(width + 4, '-'));
  full_complete.insert(full_complete.end(), std::string(width + 4, '-'));

  return full_complete; // Returns completed vector
}

int main(int argc, char *argv[])
{
  if (argc != 5)
  {
    std::cerr << "Missing 1 or more command line arguments" << std::endl;
    exit(1);
  }
  std::ifstream txt_in(argv[1]); // Creates input stream of .txt file
  if (!txt_in.good())
  {
    std::cerr << "Can't open " << argv[1] << " to read.\n";
    exit(1);
  }
  std::vector<std::string> txt_file; // Vector made to hold text from .txt file, initially empty

  std::vector<std::string> complete;                 // Vector that gets filled with left, right, or full justified text
  const unsigned int txt_width = std::stof(argv[3]); // Sets width of the text column
  const std::string txt_just = argv[4];
  read_txt(txt_file, txt_in, txt_width); // Read the .txt file into the vector
  if (txt_just == "flush_left")
  {
    complete = flush_left(txt_file, txt_width);
  }
  else if (txt_just == "flush_right")
  {
    complete = flush_right(txt_file, txt_width);
  }
  else if (txt_just == "full_justify")
  {
    complete = full_justify(txt_file, txt_width);
  }
  else
  {
    std::cerr << argv[4] << "is not a/an valid command.\n";
  }

  std::ofstream txt_out(argv[2]);
  if (!txt_out.good())
  {
    std::cerr << "Can't open " << argv[2] << " to write.\n";
    exit(1);
  }

  for (unsigned int i = 0; i < complete.size(); ++i)
  {
    txt_out << complete[i] << std::endl;
  }
  return 0;
}