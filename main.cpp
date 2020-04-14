/*  main.cpp :    Blake Baird
    Description:  This file has the 'main' function that runs the program.
    */
#include "MapBuilder.h"
#include "Posting.h"
#include "Search.h"
#include <cassert>
#include <algorithm>

using namespace std;

// Type defs
typedef map<string, vector<Posting>> StringVecMap;

// Define global constants
const vector<string> kInputFilenames = {
    "alice_wonderland_carroll.txt",           "devils_dictionary_pierce.txt",
	"great_expectations_dickens.txt",         "pride_prejudice_austen.txt"};
 //   "principles_of_philosophy_descartes.txt", "turn_screw_james.txt"};
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
	
	// Get two iterators for each search term. 
	// 		+	One is a "moving_iterator" that will move forward as the search 
	//			algorithm progresses.
	// 		+	The other is an end iterator to tell when the "moving_iterator" gets to the 
	// 			end.
	
	vector<Search::Crawler> crawlers;
    bool SOME_TERMS_NOT_IN_MAP = false;
	for (auto word : search_words) {
      if (mb.GetFrequency(word) == 0) {
		  SOME_TERMS_NOT_IN_MAP = true; 
		  break;
	  }
		// Build a vector of Search::Crawler that holds the moving iterator, the end iterator, the word, and a flag
		// for whether we have reached the end with that crawler.
		// Search is over when all crawlers have reached the end.
		crawlers.emplace_back(Crawler(mb.GetIterator(word), mb.GetEndIterator(word), word);
    }
	if (SOME_TERMS_NOT_IN_MAP) {
		cout << "One or more search terms not found in any files." << endl;
		continue;
	}	
    

	// Start the search algorithm
    /* Maintain markers into both lists and walk through the two postings lists simultaneously.
	At each step, compare the DocID pointed to by both pointers.
	If they are the same, put that DocID in a result list, else advance the pointer pointing to the smaller docID. */
	
	vector<int> doc_ids_with_all_terms{};
    
	
	while (1) {
      // check if all ptrs point to the same doc_id
      // if yes - add that document to the result
	  vector<int> current_doc_ids{};
	  for(auto &i : moving_iterators) {
		  current_doc_ids.push_back(i->DocId());
	  }
	  // Check if doc_id for all the moving_iterators is the same
	  if (count(current_doc_ids.begin(),current_doc_ids.end(), current_doc_ids[0]) == current_doc_ids.size()) {
		doc_ids_with_all_terms.push_back(current_doc_ids[0]);  
	  }
	  // Move Iterator with lowest doc_id forward
	  // start by sorting current doc_id, low to high
	  // Lowest doc_id pointed to is thus current_doc_ids[0].
	  current_doc_ids.sort();
	  	  
	} // End of search while loop
    
	
	// Print out the files that have the terms
	cout << "Terms found in: " << endl;
    for (auto i : doc_ids_with_all_terms) {
      cout << kInputFilenames[i] << endl;
    } 
  } 
  return 0;
}
