/*  main.cpp :    Blake Baird
    Description:  This file has the 'main' function that runs the program.
    */

#include "Posting.h"
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include <fstream>
#include <iomanip>
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
bool is_number(const string &s);

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
  for (auto map_iterator : map) {
    os << left << setw(20) << map_iterator.first;
    for (auto posting_vector_iterator : map_iterator.second) {
      os << setw(0) << "Doc" << posting_vector_iterator.doc_id;
      os << " [";
      int num_postings = posting_vector_iterator.location.size();
      for (int location_id = 0; location_id < num_postings; location_id++) {
        os << posting_vector_iterator.location[location_id] << " ";
        if (location_id != num_postings - 1)
          os << ", ";
      }
      os << "] ";
    }
    os << endl;
  }
}

/*
	MAP - Connects Terms (String) to a list of Postings (vector<Posting>)
		Word 		====>	Posting List 
		(String)			(<vector<Posting>)
		
	POSTING
		Doc_ID	Integer		
		Location Vector<int>
		
*/

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
      // TODO: fix the tokenizer to not include numbers
      // Loop over tokens
      for (auto word_iterator = tok.begin(); word_iterator != tok.end();
           word_iterator++) {
        // convert token to lowercase
        string lowercase = *word_iterator;
        boost::algorithm::to_lower(lowercase);
        // if word is a stop word, continue with next token
        if (count(v_stop.begin(), v_stop.end(), lowercase))
          continue;
        // if word is a number, continue with next token
        if (is_number(lowercase))
          continue;
        // check whether term is already stored in map
        StringVecMap::iterator term_it = tmp_map.find(lowercase);
        if (term_it == tmp_map.end()) {
          vector<Posting> v_post{Posting(doc_id, -1)};
          // word was *not* found, so add a map entry
          tmp_map.emplace(lowercase, v_post);
        } else {
          // Term was found. Set a flag for if a
          // posting for this doc_id already exists.
          bool post_for_this_doc_id_already_exists = false;
          int index_of_matching_post = -1;
          for (int post_index = 0; post_index < (*term_it).second.size();
               post_index++) {
            if (term_it->second[post_index].doc_id == doc_id) {
              post_for_this_doc_id_already_exists = true;
              index_of_matching_post = post_index;
            }
          }
          if (!post_for_this_doc_id_already_exists) {
            // add this new word to the map
            tmp_map[lowercase].emplace_back(Posting(doc_id, -1));
          } else {
            // add an additional location to the location vector
            (tmp_map[lowercase])[index_of_matching_post].location.push_back(-1);
          }
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

bool is_number(const string &s) {
  string::const_iterator it = s.begin();
  while (it != s.end() && isdigit(*it))
    ++it;
  return !s.empty() && it == s.end();
}
