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

Search::Crawler::Crawler(Post_It mover, Post_It end, string term) {
  Mover = mover;
  End_Marker = end;
  Term = term;
  Has_Reached_End = false;
}

// Move iterator forward in Linked List
// and set Has_Reached_End flag if reach the end of forward_list
void Search::Crawler::MoveForward() {
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
int Search::GetLowestDocId(const vector<Crawler> &c_vec) {
  int lowest_doc_id = 99999; // magic number
  int docid = -1;
  for (auto &c : c_vec) {
    if (c.Has_Reached_End)
      continue;
    docid = c.Mover->DocId();
    if (docid < lowest_doc_id) {
      lowest_doc_id = docid;
    }
  }
  return docid;
}

// Move crawlers forward if their docid matches the given docid.
void Search::MoveCrawlersForward(vector<Crawler> &cvec, int docid) {
  for (auto &i : cvec) {
    if (!i.Has_Reached_End && i.Mover->DocId() == docid) {
      i.MoveForward();
    }
  }
}

// TODO: Read this function and see if its right
bool Search::AllDocIdsTheSame(const vector<Crawler> &cvec) {
  int count = 0;
  int first_docid = cvec[0].Mover->DocId();
  for (auto &i : cvec) {
    if (i.Has_Reached_End)
      continue;
    if (i.Mover->DocId() == first_docid)
      count++;
  }
  if (count == cvec.size())
    return true;
  else
    return false;
}

void Search::MakeUnique(vector<int> &num) {
  // order of unique elements is preserved
  auto end_unique = end(num);
  for (auto iter = begin(num); iter != end_unique; ++iter) {
    // use std::remove
    end_unique = remove(iter + 1, end_unique, *iter);
  }
  num.erase(end_unique, end(num));
}
