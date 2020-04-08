#pragma once
#include <iostream>
#include <map>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include <fstream>
#include <iomanip>
#include <map>
#include <string>
#include <vector>
#include "Posting.h"

using std::map;
using std::ostream;

// Class with only object of it instantiated
class MapBuilder {
 public:
  // Constructor & Destructors
  MapBuilder(const string& StopwordsFilename, const vector<string>& InputFilenames)
      : stopwords_filename_(StopwordsFilename), input_filenames_(InputFilenames) {}
    ~MapBuilder(){};
  
  // Function declarations
  void loadStopwords();
  bool is_Token_Valid(const string word_token);
  map<string, vector<Posting>> BuildMap();
  static void printMap(ostream&, map<string, vector<Posting>>&);
  static bool is_Number(const string& s);

 private:
  // const member variables can only be modified in the constructor
  const string stopwords_filename_;
  const vector<string> input_filenames_;
  vector<string> stopwords_;
};
