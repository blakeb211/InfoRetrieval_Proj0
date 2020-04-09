/*  main.cpp :    Blake Baird
    Description:  This file has the 'main' function that runs the program.
    */
#include "MapBuilder.h"
#include "Posting.h"
#include "Tokenizer.h"

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
  vector<string> words;
  string target = "Test string to see if the light-hearted words get pulled "
                  "out! He said \' I shalt not go !\'";
  Tokenizer::ParseString(target, words);
  for (auto i : words)
    cout << i << endl;
  // StringVecMap dict = mb.BuildMap();
  ofstream outfile("output.txt", ios::out);
  outfile.close();
  // mb.PrintMap(outfile, dict);
  return 0;
}
