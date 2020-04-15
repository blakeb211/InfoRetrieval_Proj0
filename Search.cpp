#include "Search.h"
#include "boost/algorithm/string.hpp"
#include <cstdlib>
#include <iostream>

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

// TODO: Read this function and see if its right

void Search::MakeUnique(vector<int> &num) {
  // order of unique elements is preserved
  auto end_unique = end(num);
  for (auto iter = begin(num); iter != end_unique; ++iter) {
    // use std::remove
    end_unique = remove(iter + 1, end_unique, *iter);
  }
  num.erase(end_unique, end(num));
}
