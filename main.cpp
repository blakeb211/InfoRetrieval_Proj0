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
  mb.LoadStopwords();
  // Initialize a dictionary that takes the word (term) as a key and returns the
  // postings list (vector holding the files the word is located in and where it
  // occurs).
  // TODO: replace boost tokenizer with a regex  "/[\w|-]+/g"  for words
  // TODO: Factor BuildMap into 3 functions and use a Linked List
  mb.GetTermsAndPostings();
  mb.SortTerms();
  mb.BuildDictionary();
  // StringVecMap dict = mb.BuildMap();
  ofstream outfile("output.txt", ios::out);
  mb.PrintMap(outfile, dict);
  return 0;
}
