#include "MapBuilder.h"
#include "Utility.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <map>
using namespace std;
typedef map<string, vector<Posting>> StringVecMap;

unsigned int MapBuilder::GetIndexSize() {
  int totalSize = sizeof(inverted_index);
  int noElements = 0;

  for (std::map<string, forward_list<Posting>>::iterator i =
           inverted_index.begin();
       i != inverted_index.end(); i++) {
    noElements++;
  }
  totalSize += noElements * sizeof(string);
  totalSize += noElements * sizeof(forward_list<Posting>);
  return totalSize / 1024;
}

// Description: Print a map<string, forward_list<Posting>> to an ostream
// Return Type: void
void MapBuilder::PrintMap(ostream &os) {
  for (auto map_iterator : inverted_index) {
    os << left << setw(20) << map_iterator.first;
    for (auto posting_vector_iterator : map_iterator.second) {
      os << setw(0) << "Doc" << posting_vector_iterator.DocId();
      os << " [";
      os << posting_vector_iterator.Location();
      ;
      os << "] ";
    }
    os << endl;
  }
}
// Count total number of postings for the term in the map
int MapBuilder::GetFrequency(string term) {
  Utility::ToLower(term);
  int count = 0;
  auto search_result = inverted_index.find(term);
  if (search_result == inverted_index.end()) {
    count = 0;
  } else {
    for (auto it = search_result->second.begin();
         it != search_result->second.end(); it++) {
      count++;
    }
  }
  return count;
}

forward_list<Posting>::iterator MapBuilder::GetIterator(string s) {
  return inverted_index.find(s)->second.begin();
}

forward_list<Posting>::iterator MapBuilder::GetEndIterator(string s) {
  return inverted_index.find(s)->second.end();
}

// Description: Load the words from a local
// file. Return Type: Return a vector of strings
void MapBuilder::LoadStopwords() {
  // Open stop_words file using constructor
  // that automatically opens the file in input mode.
  ifstream f_stop(stopwords_filename_, ios::in);
  // Read stop words into vector until EOF
  string tmp;
  while (true) {
    f_stop >> tmp;
    if (!f_stop.good())
      break;
    stopwords_.push_back(tmp);
  }
  f_stop.close();
}

bool MapBuilder::IsTokenValid(const string word_token) {
  // if word is a stop word, continue with next token
  if (count(stopwords_.begin(), stopwords_.end(), word_token))
    return false;
  // if word is a number, continue with next token
  return true;
}

void MapBuilder::ProcessInputFiles() {
  cout << "GetTermsAndPostings method started..." << endl;
  ifstream ifs; // declare reusable ifstream
  std::regex word_regex("([a-zA-Z]{1,}[']?[-]?[a-zA-Z]{1,})");
  string line, token;
  unsigned int line_count = 0;
  // Loop over filenames
  // doc_id holds the input_filenames_ array index of the current file
  // being processed
  cout << "Files to process: " << input_filenames_.size() << endl;
  for (int doc_id = 0; doc_id < input_filenames_.size(); doc_id++) {
    ifs = ifstream(input_filenames_[doc_id], ifstream::in);
    cout << "Opening " << input_filenames_[doc_id] << " ..." << endl;
    // Set line_count = 0 at the beginning of each file.

    do { // Start of loop over lines in file
      getline(ifs, line);
      line_count++;
      // Run the regex expression
      auto _begin = std::sregex_iterator(line.begin(), line.end(), word_regex);
      auto _end = std::sregex_iterator();
      // Iterate over the tokens
      for (auto word_iterator = _begin; word_iterator != _end;
           ++word_iterator) {
        // Convert token iterator to a std::string
        token = (*word_iterator).str();
        // Convert token to lowercase
        Utility::ToLower(token);
        // Filter out stopwords and other invalid tokens that
        // made it past the regex.
        if (!IsTokenValid(token))
          continue;
        AddPostingToMap(token, doc_id, line_count);
      }
    } while (ifs.good()); // End of loop over lines in file
    ifs.close();
  } // End of loop over filenames
}

void MapBuilder::AddPostingToMap(string term, int doc_id, int line_count) {
  // Check if term is already in map
  // If yes - check if there is a node with the same doc_Id
  //      If yes - increment frequency
  //      If no - add a node with this doc_id
  // If no - add word to map , create forward_list, and add first node
  auto search_result = inverted_index.find(term);
  if (search_result != inverted_index.end()) {
    // Increment frequency
    auto it = search_result->second.begin();
    auto end_it = search_result->second.end();
    // Iterate through until 'it' points to the correct Posting
    while (it != end_it && it->DocId() != doc_id) {
      it++;
    }
    if (it != end_it) {
      // Add an additional posting for this doc_id
      inverted_index[term].emplace_after(it, Posting(doc_id, line_count));
    } else {
      // No posting found with the same doc_id, so add a Posting
      search_result->second.push_front(Posting(doc_id, line_count));
    }
  } else {
    // Add the term to the map and initialize the forward_list
    // with the first Posting
    inverted_index.emplace(term,
                           forward_list<Posting>{Posting(doc_id, line_count)});
  }
}

// Sort the forward_list of postings by doc_id and then location
void MapBuilder::SortMap() {
  for (auto &pair_it : inverted_index) { // loop over pairs
    pair_it.second
        .reverse(); // reverse it first because we built the map backwards
    // sort the forward_list<Posting> using a lambda
    pair_it.second.sort([](Posting &a, Posting &b) {
      if ((a.DocId() < b.DocId()) ||
          (a.DocId() == b.DocId() && a.Location() < b.Location()))
        return true;
      else
        return false;
    });
  }
}

// Write the map to an output file
void MapBuilder::WriteInvertedIndexToFile() {
	ofstream outfile("output.txt", ios::out);
	PrintMap(outfile);
	outfile.close();
}
