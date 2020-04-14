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
    vector<string> result{};
    boost::split(result, user_input, boost::is_any_of(" "));
    vector<string> search_words_in_map{};
    vector<forward_list<Posting>::iterator> pointers{};
    // Get an interator to the linked list for each term
    for (auto word : result) {
      if (mb.GetFrequency(word) > 0) {
        search_words_in_map.emplace_back(word);
        pointers.emplace_back(mb.GetIterator(word));
      }
    }
    assert(search_words_in_map.size() == pointers.size());
    // Start the search algorithm
    vector<int> files_with_the_terms{};
    while (1) {
      // check if all ptrs point to the same doc_id
      // if yes - add that document to the result
      int doc_id_first_pointer = -2;
      int lowest_doc_id = 999;
      int index_of_ptr_with_lowest_doc_id = -1;
      for (int ptr_and_word_index = 0; ptr_and_word_index < pointers.size();
           ptr_and_word_index++) {
        auto ptr_index = pointers[ptr_and_word_index];
        // update lowest doc_id
        if (ptr_index->DocId() < lowest_doc_id) {
          lowest_doc_id = ptr_index->DocId();
          index_of_ptr_with_lowest_doc_id = ptr_and_word_index;
        }
        if (doc_id_first_pointer == -2) {
          doc_id_first_pointer = ptr_index->DocId();
        } else {
          if (ptr_index->DocId() != doc_id_first_pointer) {
            doc_id_first_pointer = -1;
            break;
          }
        }
      } // End of loop over pointers
        // if doc_id_first_pointer == -1, they did not match. increment the
        // lowest pointer.
      if (doc_id_first_pointer >= 0)
        files_with_the_terms.emplace_back(doc_id_first_pointer);
      // increment lowest pointer
      if (pointers[index_of_ptr_with_lowest_doc_id] ==
          mb.GetEndIterator(
              search_words_in_map[index_of_ptr_with_lowest_doc_id])) {
        // search is done
        break;
      }
      pointers[index_of_ptr_with_lowest_doc_id]++;

    } // End of search while loop
    cout << "Terms found in files: " << endl;
    for (int i = 0; i < files_with_the_terms.size(); i++) {
      cout << kInputFilenames[i] << endl;
    }
  }
  return 0;
}
