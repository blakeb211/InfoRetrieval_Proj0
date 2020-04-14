/*  main.cpp :    Blake Baird
    Description:  This file has the 'main' function that runs the program.
    */
#include "MapBuilder.h"
#include "Posting.h"
#include "boost/algorithm/string.hpp"

using namespace std;

// Type defs
typedef map<string, vector<Posting>> StringVecMap;

// Define global constants
const vector<string> kInputFilenames = {
    "alice_wonderland_carroll.txt",           "devils_dictionary_pierce.txt",
    "great_expectations_dickens.txt",         "pride_prejudice_austen.txt",
    "principles_of_philosophy_descartes.txt", "turn_screw_james.txt"};
const string kStopwordFilename("stop_words.txt");

int main() {
  // Initialize a vector to hold the stop words
  MapBuilder mb(kStopwordFilename, kInputFilenames);
  mb.LoadStopwords();
  // Initialize a dictionary that takes the word (term) as a key and returns the
  // postings list (vector holding the files the word is located in and where it
  // occurs).
  mb.ProcessInputFiles(); // this function calls AddPostingToMap()
  mb.SortMap();
  // Write the map to an output file
  ofstream outfile("output.txt", ios::out);
  mb.PrintMap(outfile);
  outfile.close();

  // Show a user interface to search the map
  string user_input;
  while (1) {
    cout << "Enter terms to search (or q to quit):" << endl;
    getline(cin, user_input);
    if (user_input == "q")
      break;
    vector<string> result;
    boost::split(result, user_input, boost::is_any_of(" "));
  }
  return 0;
}
