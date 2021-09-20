#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

#include "miniBlast.h"

using namespace std;

int main()
{
  string s;

  MiniBLAST MBTable;
  unsigned int kmer;
  string genSeq;
  unsigned int MBTableSize;
  float MBTableOcc;

  while (cin >> s)
  {
    if (s == "genome")
    {
      string genome;
      cin >> genome;
      // cout << genome << endl;
      ifstream istr(genome);

      // checks if file can be opened
      if (!istr.good())
      {
        cerr << "Can't open " << genome << " for read." << endl;
        exit(1);
      }

      string genstr;

      // reads genome into one large string
      while (istr >> genstr)
      {
        genSeq += genstr;
      }

      // cout << genSeq << endl;
    }
    else if (s == "kmer")
    {
      cin >> kmer;
      // cout << kmer << endl;

      MBTable.makeKeys(genSeq, kmer); // makes the keys for the table
      // cout << MBTable.returnSize() << endl;
      MBTable.makeTable(); // makes the table with the keys generated
    }
    else if (s == "query")
    {
      string query;
      unsigned int mismatches;
      cin >> mismatches >> query;
      // cout << mismatches << " " << query << " " << query.substr(0, kmer) << endl;
      cout << "Query: " << query << endl;

      // finds matches based on the first k letters of the query
      MBTable.find(genSeq, query.substr(0, kmer), mismatches);
    }
    else if (s == "table_size")
    {
      cin >> MBTableSize;
      MBTable.setSize(MBTableSize); // sets new table size
    }
    else if (s == "occupancy")
    {
      cin >> MBTableOcc;
      MBTable.setOcc(MBTableOcc); // sets new occupancy limit
    }
    else if (s == "quit")
    {
      break;
    }
    else
    {
      cerr << "Unknown command, type 'quit' to stop the program." << endl;
    }
  }

  return 0;
}