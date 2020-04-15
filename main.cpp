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
    vector<Search::Crawler> crawlers;
    bool SOME_TERMS_NOT_IN_MAP = false;
    for (int i = 0; i < search_words.size(); i++) {
      if (mb.GetFrequency(search_words[i]) == 0) {
        SOME_TERMS_NOT_IN_MAP = true;
        break;
      }
      // Build a vector of Search::Crawler that holds the moving iterator, the
      // end iterator, the word, and a flag for whether we have reached the end
      // with that crawler. Search is over when all crawlers have reached the
      // end.
      Utility::ToLower(search_words[i]);
      crawlers.emplace_back(Search::Crawler(mb.GetIterator(search_words[i]),
                                            mb.GetEndIterator(search_words[i]),
                                            search_words[i]));
    }
    if (SOME_TERMS_NOT_IN_MAP) {
      cout << "One or more search terms not found in any files." << endl;
      continue;
    }
    /* END INITIALIZE CRAWLERS */

    // Start the search algorithm
    /* 1.	Maintain markers into both lists and walk through the two
       postings lists simultaneously.
           2. 	At each step, compare the DocID pointed to by both pointers.
           3.	If they are the same, put that DocID in a result list, else
       advance the pointer pointing to the smaller docID. */

    vector<int> doc_ids_with_all_terms{};

    while (1) {
      // Find the lowest doc_id out of all the moving iterators.
      int lowest_doc_id = Search::GetLowestDocId(crawlers);
      // If all crawlers have ended, break out of loop.
      if (lowest_doc_id == -1)
        break;
      // Check if all crawlers have same docid.
      // 		If so, add doc_id to doc_ids_with_all_terms
      if (Search::AllDocIdsTheSame(crawlers)) {
        doc_ids_with_all_terms.push_back(lowest_doc_id);
      }
      // Move all crawlers forward that have the low doc_id
      Search::MoveCrawlersForward(crawlers, lowest_doc_id);
    } // end of while loop

    // Remove duplicates in doc_ids_with_all_terms
    Search::MakeUnique(doc_ids_with_all_terms);

    // Print out the files that have the terms
    cout << "Terms found in: " << endl;
    for (auto i : doc_ids_with_all_terms) {
      cout << kInputFilenames[i] << endl;
    }

  } // end of outer while loop
  return 0;
}
