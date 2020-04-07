/*  main.cpp :    Blake Baird
    Description:  This file has the 'main' function that runs the program.
    */
#include "MapBuilder.h"
#include "Posting.h"

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
  mb.load_Stopwords();
  // Initialize a dictionary that takes the word (term) as a key and returns the
  // postings list (vector holding the files the word is located in and where it
  // occurs).
  StringVecMap dict = mb.BuildMap();
  ofstream outfile("output.txt", ios::out);
  mb.print_Map(outfile, dict);
  return 0;
}
