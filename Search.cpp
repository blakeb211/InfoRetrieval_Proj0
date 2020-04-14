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