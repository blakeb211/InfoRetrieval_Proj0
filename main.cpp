/*  main.cpp :    Blake Baird
    Description:  This file has the 'main' function that runs the program.
    */

#include "Posting.h"
#include <algorithm>
#include <boost/tokenizer.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;
// Type defs
typedef map<string, vector<Posting>> StringVecMap;
// Define global constants
const vector<string> kInputFilenames = {
    "alice_wonderland_carroll.txt",           "devils_dictionary_pierce.txt",
    "great_expectations_dickens.txt",         "pride_prejudice_austen.txt",
    "principles_of_philosophy_descartes.txt", "turn_screw_james.txt"};
const string kStopwordFilename("stop_words.txt");

// Function declarations
vector<string> LoadStopWords();
StringVecMap BuildMap(const vector<string> &, vector<string> &);
void PrintMap(ostream &, StringVecMap &);

int main() {
  // Initialize a vector to hold the stop words
  vector<string> v_stop = LoadStopWords();
  // Initialize a dictionary that takes the word (term) as a key and returns the
  // postings list (vector holding the files the word is located in and where it
  // occurs).
  StringVecMap dict = BuildMap(kInputFilenames, v_stop);
  ofstream outfile("output.txt", ios::out);
  PrintMap(outfile, dict);
  return 0;
}

// Description: Print a map<string, vector<Posting>> to an ostream
// Return Type: void
void PrintMap(ostream &os, StringVecMap &map) {
  for (auto it : map) {
    os << it.first << "\t";
    for (auto posting : it.second) {
      os << "doc_id: " << posting.doc_id << "\t";
      for (auto location : posting.location) {
        os << location << " ";
      }
    }
    os << endl;
  }
}

// Description: Iterate through the files. Tokenize the words.').
// Remove stop words. Add doc_id and location to the dictionary.
// Return Type: Map of strings to vector<Posting>
StringVecMap BuildMap(const vector<string> &files, vector<string> &v_stop) {
  cout << "Map is being built..." << endl;
  ifstream ifs;         // declare reusable ifstream
  StringVecMap tmp_map; // declare map to be returned
  // Loop over filenames
  for (int doc_id = 0; doc_id < kInputFilenames.size(); doc_id++) {
    ifs = ifstream(files[doc_id], ios::in);
    string line;
    while (true) {
      getline(ifs, line, '\n');
      // Tokenize the line with boost tokenizer.
      boost::tokenizer<> tok(line);
      // Loop over tokens
      for (auto it = tok.begin(); it != tok.end(); it++) {
        // if word is a stop word, continue with next token
        if (count(v_stop.begin(), v_stop.end(), *it))
          continue;
        // check whether term is already stored in map
        StringVecMap::iterator term_it = tmp_map.find(*it);
        if (term_it == tmp_map.end()) {
          vector<Posting> v_post{Posting(doc_id, -1)};
          // word was *not* found, so add a map entry
          tmp_map.emplace(*it, v_post);
        } else {
          // Term was found. Check if there is already a
          // posting for this doc_id.
          tmp_map[*it].emplace_back(Posting(doc_id, -1));
        }
      } // End of loop over tokens
      if (!ifs.good())
        break;
    }
    ifs.close();
  } // end of loop over files
  return tmp_map;
}

// Description: Load the words from a local
// file. Return Type: Return a vector of strings
vector<string> LoadStopWords() {
  // Open stop_words file using constructor
  // that automatically opens the file in input mode.
  ifstream f_stop(kStopwordFilename, ios::in);
  // Read stop words into vector until EOF
  vector<string> v_words(0);
  string tmp;
  while (true) {
    f_stop >> tmp;
    if (!f_stop.good())
      break;
    v_words.push_back(tmp);
  }
  f_stop.close();
  return v_words;
}
