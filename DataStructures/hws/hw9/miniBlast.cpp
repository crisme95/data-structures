#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

#include "miniBlast.h"

using namespace std;

// returns vector of keys with length set by the kmer
void MiniBLAST::makeKeys(const string &genome, unsigned int kmer)
{
  for (unsigned int i = 0; i < genome.length(); i++)
  {
    string temp = genome.substr(i, kmer);

    // stops loop from making keys if they won't be long enough
    if (temp.length() < kmer)
      break;

    tableKeys.push_back(make_pair(temp, i));
  }

  // for (unsigned int j = 0; j < tableKeys.size(); j++)
  // {
  //   cout << "key = " << tableKeys[j].first << " position = " << tableKeys[j].second << endl;
  // }
}

// makes table using all the keys
void MiniBLAST::makeTable()
{
  // loops through each index and maps the key
  for (unsigned int i = 0; i < tableKeys.size(); i++)
  {
    insert(tableKeys[i]);
  }
}

// borrowed from lecture, 20.9
unsigned int MiniBLAST::hash(const string &key)
{
  unsigned int index = 0;
  for (unsigned int i = 0; i < key.size(); ++i)
  {
    index = index * 8 + key[i];
  }

  // cout << "key = " << key << " hash = " << index << " index = " << (index % table.size()) << endl;
  return index % table.size();
}

// inserts key if there's space, resizes table if none
// uses linear probing
void MiniBLAST::insert(const pair<string, int> &key)
{
  if (tableSize >= tableOcc * table.size())
  {
    // cout << "resize in progress" << endl;
    resizeTable(2 * table.size() + 1);
  }

  unsigned int index = hash(key.first);

  if (table[index].empty() == false)
  {
    // check if same key to add index on genome
    if (table[index][0].first == key.first)
    {
      table[index].push_back(key);
      tableSize++;
    }
    else
    {
      // loops until we find an empty spot or the same key
      while (table[index].empty() == false)
      {
        index = (index + 1) % table.size();
      }

      table[index].push_back(key);
      tableSize++;
    }
  }
  else
  {
    // loops until we find an empty spot or the same key
    while (table[index].empty() == false)
    {
      index = (index + 1) % table.size();
    }

    table[index].push_back(key);
    tableSize++;
  }
}

void MiniBLAST::find(const string &genome, const string &query, const unsigned int mismatches)
{
  unsigned int index = hash(query);

  // if we index an empty spot, return no matches
  if (table[index].empty() == true)
  {
    cout << "No match" << endl;
  }
}

// resizes the table and rehashes all the keys
void MiniBLAST::resizeTable(unsigned int newSize)
{
  vector<vector<pair<string, int>>> oldTable = table;
  table.clear();
  table.resize(newSize);

  // loop through each vector in the table
  for (unsigned int i = 0; i < oldTable.size(); i++)
  {
    if (oldTable[i].empty() == false)
    {
      unsigned int index = hash(oldTable[i][0].first);

      // loop until we find correct index
      while (table[index].empty() == false)
      {
        index = (index + 1) % table.size();
      }

      table[index] = oldTable[i]; // copy vector
    }
  }

  // cout << "resize complete" << endl;
}
