/*  main.cpp :    Blake Baird
    Description:  This file has the 'main' function that runs the program.
    */
#include "MapBuilder.h"
#include "Posting.h"
#include "Search.h"
#include "Utility.h"
#include <algorithm>
#include <cassert>

using namespace std;

// Type defs
typedef map<string, vector<Posting>> StringVecMap;

// Define global constants
const vector<string> kInputFilenames = {"alice_wonderland_carroll.txt",
                                        "turn_screw_james.txt"};
//"devils_dictionary_pierce.txt",
//"great_expectations_dickens.txt",         "pride_prejudice_austen.txt"};
//   "principles_of_philosophy_descartes.txt", };

// TEST CASES
// actually - both docs
// frighten - both docs
// actually and frighten - both docs
// shouting - alice only
// mention - turn screw
// god - turn screw
// mention god

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

  // Show a user interface to search the map

  while (1) {

    // Break user input up into a vector of strings called search_words
    vector<string> search_words = Search::GetSearchTerms();

    // Crawlers have two two iterators and there is one crawler per search term.
    // 		+	One is a "moving_iterator" that will move forward as the
    // search
    //			algorithm progresses. - called Mover
    // 		+	The other is an end iterator to tell when the
    // "moving_iterator" gets to the 			end. - called End_Marker

    /* START INITIALIZE CRAWLERS */
    bool SOME_TERMS_NOT_IN_MAP = false;
    for (int i = 0; i < search_words.size(); i++) {
      if (mb.GetFrequency(search_words[i]) == 0) {
        SOME_TERMS_NOT_IN_MAP = true;
        break;
      }
    }

    if (SOME_TERMS_NOT_IN_MAP) {
      cout << "One or more search terms not found in any files." << endl;
      continue;
    }
    /* END INITIALIZE CRAWLERS */

    // print docids for terms
    for (int word_id = 0; word_id < search_words.size(); word_id++) {
      auto map_it = mb.GetIterator(search_words[word_id]);
      cout << "Word: " << search_words[word_id];
      auto end_it = mb.GetEndIterator(search_words[word_id]);
      while (map_it != end_it) {
        cout << map_it->DocId() << " ";
        map_it++;
      }
      cout << endl;
    }

    // Start the search algorithm
    /* 1.	Maintain markers into both lists and walk through the two
       postings lists simultaneously.
       2. 	At each step, compare the DocID pointed to by both pointers.
       3.	If they are the same, put that DocID in a result list, else
       advance the pointer pointing to the smaller docID. */

    if (search_words.size() == 1) {
    }

    if (search_words.size() == 2) {
    }
    vector<int> doc_ids_with_all_terms{};
    // it = set_intersection(vector1.begin(), vector1.end(), vector2.begin(),
    //                      vector2.end(), v.begin());

  } // end of outer while loop
  return 0;
}
