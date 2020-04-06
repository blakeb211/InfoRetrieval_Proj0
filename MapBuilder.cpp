#include "MapBuilder.h"

#include <fstream>
#include <iomanip>
using namespace std;
typedef map<string, vector<Posting>> StringVecMap;

MapBuilder::MapBuilder(string StopwordsFilename, vector<string> InputFiles) {}

// Destructor
MapBuilder::~MapBuilder() {}

// Description: Print a map<string, vector<Posting>> to an ostream
// Return Type: void
void MapBuilder::PrintMap(ostream& os, map<string, vector<Posting>>& map) {
  for (auto map_iterator : map) {
    os << left << setw(20) << map_iterator.first;
    for (auto posting_vector_iterator : map_iterator.second) {
      os << setw(0) << "Doc" << posting_vector_iterator.doc_id;
      os << " [";
      int num_postings = posting_vector_iterator.location.size();
      for (int location_id = 0; location_id < num_postings; location_id++) {
        os << posting_vector_iterator.location[location_id] << " ";
        if (location_id != num_postings - 1)
          os << ", ";
      }
      os << "] ";
    }
    os << endl;
  }
}

// Description: Iterate through the files. Tokenize the words.').
// Remove stop words. Add doc_id and location to the dictionary.
// Return Type: Map of strings to vector<Posting>
StringVecMap MapBuilder::BuildMap(const vector<string>& files,
                                  vector<string>& v_stop) {
  cout << "Map is being built..." << endl;
  ifstream ifs;          // declare reusable ifstream
  StringVecMap tmp_map;  // declare map to be returned
  // Loop over filenames
  for (int doc_id = 0; doc_id < kInputFilenames.size(); doc_id++) {
    ifs = ifstream(files[doc_id], ios::in);
    string line;
    while (true) {
      getline(ifs, line, '\n');
      // Tokenize the line with boost tokenizer.
      boost::tokenizer<> tok(line);
      // TODO: fix the tokenizer to not include numbers
      // Loop over tokens
      for (auto word_iterator = tok.begin(); word_iterator != tok.end();
           word_iterator++) {
        // convert token to lowercase
        string lowercase = *word_iterator;
        boost::algorithm::to_lower(lowercase);
        if (!is_Token_Valid(v_stop, lowercase))
          continue;
        // check whether term is already stored in map
        StringVecMap::iterator term_it = tmp_map.find(lowercase);
        if (term_it == tmp_map.end()) {
          // Term was *not* found in map, so add a new map entry
          vector<Posting> v_post{Posting(doc_id, -1)};
          tmp_map.emplace(lowercase, v_post);
        } else {
          // Term *was* found in map.
          // Check if term was already found in this document.
          // If it was already found, set flag to true and
          // save the index in vector<posting> where it was already stored.
          bool post_for_this_doc_id_already_exists = false;
          int index_of_matching_post = -1;
          for (int post_index = 0; post_index < (*term_it).second.size();
               post_index++) {
            if (term_it->second[post_index].doc_id == doc_id) {
              post_for_this_doc_id_already_exists = true;
              index_of_matching_post = post_index;
            }
          }
          if (!post_for_this_doc_id_already_exists) {
            // add this new word to the map
            tmp_map[lowercase].emplace_back(Posting(doc_id, -1));
          } else {
            // add an additional location to the location vector
            (tmp_map[lowercase])[index_of_matching_post].location.push_back(-1);
          }
        }
      }  // End of loop over tokens
      if (!ifs.good())
        break;
    }
    ifs.close();
  }  // end of loop over files
  return tmp_map;
}

// Description: Load the words from a local
// file. Return Type: Return a vector of strings
vector<string> MapBuilder::LoadStopWords() {
  // Open stop_words file using constructor
  // that automatically opens the file in input mode.
  ifstream f_stop(StopwordFile, ios::in);
  // Read stop words into vector until EOF
  vector<string> v_words(0);
  string tmp;
  while (true) {
    f_stop >> tmp;
    if (!f_stop.good())
      break;
    v_words.push_back(tmp);
  }
  f_stop.close();
  return v_words;
}

bool MapBuilder::is_number(const string& s) {
  string::const_iterator it = s.begin();
  while (it != s.end() && isdigit(*it))
    ++it;
  return !s.empty() && it == s.end();
}

bool MapBuilder::is_Token_Valid(const vector<string>& stopwords,
                                const string word_token) {
  // if word is a stop word, continue with next token
  if (count(stopwords.begin(), stopwords.end(), word_token))
    return false;
  // if word is a number, continue with next token
  if (is_number(word_token))
    return false;
  return true;
}
