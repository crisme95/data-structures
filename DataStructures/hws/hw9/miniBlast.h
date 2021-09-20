#ifndef MINIBLAST_H
#define MINIBLAST_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

class MiniBLAST
{
public:
  // constructor
  MiniBLAST() : table(100), tableSize(0), tableOcc(0.5) {}

  // member functions
  void makeKeys(const string &genome, const unsigned int kmer);
  void makeTable();

  unsigned int hash(const string &key);
  void insert(const pair<string, int> &key);
  void find(const string &genome, const string &query, const unsigned int mismatches);
  void resizeTable(unsigned int newSize);

  // Optional commands that change hash table behavior
  void setSize(unsigned int size) { table.resize(size); }
  void setOcc(float occ) { tableOcc = occ; }

  unsigned int returnSize() { return table.size(); }

private:
  vector<vector<pair<string, int>>> table; // actual table
  vector<pair<string, int>> tableKeys;     // keys for table
  unsigned int tableSize;                  // number of keys
  float tableOcc;                          // maximum occupancy
};

#endif