/*  main.cpp :    Blake Baird
    Description:  This file has the 'main' function that runs the program.
    */

#include "Posting.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

// Define global constants
const vector<string> kFiles = {
    "alice_wonderland_carroll.txt",           "devils_dictionary_pierce.txt",
    "great_expectations_dickens.txt",         "pride_prejudice_austen.txt",
    "principles_of_philosophy_descartes.txt", "turn_screw_james.txt"};
const string kStopWords("stop_words.txt");

// Function declarations
vector<string> LoadStopWords();
void Tokenize(const vector<string> &);

int main() {
  // Initialize a vector to hold the stop words
  vector<string> v_stop = LoadStopWords();
  map<string, vector<Posting>> dict;
  Tokenize(kFiles);
  return 0;
}

// Description: Iterate through the files. Save the words (alphanumeric, - , ').
// Remove stop words. Return Type:
void Tokenize(const vector<string> &files) {
  cout << "Tokenize function running..." << endl;
  for (auto f : files)
    cout << f << endl;
}

// Description: Load the words from a local
// file. Return Type: Return a vector of strings
vector<string> LoadStopWords() {
  // Open stop_words file using constructor
  // that automatically opens the file in input mode.
  ifstream f_stop(kStopWords, ios::in);
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
