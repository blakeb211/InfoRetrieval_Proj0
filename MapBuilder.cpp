#include "MapBuilder.h"
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
      os << setw(0) << "Doc" << posting_vector_iterator.doc_id;
      os << " [";
      int num_postings = posting_vector_iterator.frequency;
      os << num_postings;
      os << "] ";
    }
    os << endl;
  }
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
  // Loop over filenames
  // doc_id holds the input_filenames_ array index of the current file
  // being processed
  cout << "Files to process: " << input_filenames_.size() << endl;
  for (int doc_id = 0; doc_id < input_filenames_.size(); doc_id++) {
    ifs = ifstream(input_filenames_[doc_id], ifstream::in);
    cout << "Opening " << input_filenames_[doc_id] << " ..." << endl;

    do { // Start of loop over lines in file
      getline(ifs, line);
      // Run the regex expression
      auto _begin = std::sregex_iterator(line.begin(), line.end(), word_regex);
      auto _end = std::sregex_iterator();
      for (auto word_iterator = _begin; word_iterator != _end;
           ++word_iterator) {
        token = (*word_iterator).str();
        // Convert token to lowercase before next step
        transform(token.begin(), token.end(), token.begin(),
                  [](unsigned char c) { return std::tolower(c); });
        // Filter out stopwords and other invalid tokens that
        // made it past the regex.
        if (!IsTokenValid(token))
          continue;
        AddPostingToMap(token, doc_id);
      }

    } while (ifs.good()); // End of loop over lines in file
    ifs.close();
  } // End of loop over filenames
}

void MapBuilder::AddPostingToMap(string term, int doc_id) {
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
    while (it != end_it && it->doc_id != doc_id) {
      it++;
    }
    if (it != end_it) {
      it->frequency++;
    } else {
      // no Posting found with the same doc_id, so add a Posting
      search_result->second.emplace_after(search_result->second.before_begin(),
                                          Posting(doc_id));
    }
  } else {
    // Add the term to the map
    inverted_index.emplace(term, forward_list<Posting>{Posting(doc_id)});
    // Add term and posting to map
  }
}
