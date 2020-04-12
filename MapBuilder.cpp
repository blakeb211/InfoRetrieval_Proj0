#include "MapBuilder.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <map>
using namespace std;
typedef map<string, vector<Posting>> StringVecMap;

// Description: Print a map<string, forward_list<Posting>> to an ostream
// Return Type: void
void MapBuilder::PrintMap(ostream &os) {
  for (auto map_iterator : inverted_index) {
    os << left << setw(20) << map_iterator.first;
    for (auto posting_vector_iterator : map_iterator.second) {
      os << setw(0) << "Doc" << posting_vector_iterator.doc_id_;
      os << " [";
      os << posting_vector_iterator.location_;
      ;
      os << "] ";
    }
    os << endl;
  }
}

void MapBuilder::ToLower(string &s) {
  // May be faster to merge terms than to do this for every token
  transform(s.begin(), s.end(), s.begin(), tolower);
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

bool MapBuilder::IsNumber(const string &s) {
  string::const_iterator it = s.begin();
  while (it != s.end() && isdigit(*it))
    ++it;
  return !s.empty() && it == s.end();
}

bool MapBuilder::IsTokenValid(const string word_token) {
  // if word is a stop word, continue with next token
  if (count(stopwords_.begin(), stopwords_.end(), word_token))
    return false;
  // if word is a number, continue with next token
  if (IsNumber(word_token))
    return false;
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
        ToLower(token);
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
  // If yes - increment frequency
  // If no - add a node with this doc_id
  // If no - add word to map , create forward_list, and add first node
  auto search_result = inverted_index.find(term);
  if (search_result != inverted_index.end()) {
    // Increment frequency
    auto it = search_result->second.begin();
    auto end_it = search_result->second.end();
    // Iterate through until 'it' points to the correct Posting
    while (it != end_it && it->doc_id_ != doc_id) {
      it++;
    }
    if (it != end_it) {
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
