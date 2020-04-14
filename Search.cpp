#include "Search.h"
#include "boost/algorithm/string.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

// Ask the user for white space separated line of input.
// Return a vector<string> of the strings in the line.
vector<string> Search::GetSearchTerms() {	
	cout << "Enter terms to search (or q to quit):" << endl;
	string user_input;
	getline(cin, user_input);
	if (user_input == "q")
	  exit(EXIT_SUCCESS);
  
  	// split the string on whitespace and return
  	vector<string> result{};
    boost::split(result, user_input, boost::is_any_of(" "));
	return result;
}


Search::Crawler::Crawler(Post_It mover, Post_It end, string term) {
	Mover = mover;
	End_Marker = end;
	Term = term;
	Has_Reached_End = false;
}

// Move iterator forward in Linked List
// and set Has_Reached_End flag if reach the end of forward_list
Search::Crawler::MoveForward() {
	if (Mover != End_Marker) {
		Mover++;
	}
	if (Mover == End_Marker)
		Has_Reached_End = true;
}

// Return lowest docid of a vector of crawlers.
// If a crawler has already reached the end then
// it is skipped.
// *If this function returns -1, then all crawlers have reached the end.*
int Search::GetLowestDocId(const vector<Crawler>& c_vec) {
	int lowest_doc_id = 99999;	// magic number
	int docid = -1;
	for(auto &c : c_vec)
	{
		if (c.Has_Reached_End) continue;
		docid = c.Mover->DocId();
		if (docid < lowest_doc_id)
		{
			lowest_doc_id = docid;
		}
	}
	return docid;
}

// Move crawlers forward if their docid matches the given docid.
void Search::MoveCrawlersForward(vector<Crawler>& c_vec, int docid) {
	
}

// TODO: Read this function and see if its right
bool Search::AreAllDocIdsTheSame(const vector<crawler>&) {
	if (count(current_doc_ids.begin(),current_doc_ids.end(), current_doc_ids[0]) == current_doc_ids.size()) {
		doc_ids_with_all_terms.push_back(current_doc_ids[0]);  
	}
}
