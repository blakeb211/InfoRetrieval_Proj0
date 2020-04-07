#pragma once
#include "Posting.h"
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

using std::map;
using std::ostream;
using std::string;
using std::vector;

// Class with only object of it instantiated
class MapBuilder {
public:
  // Constructor & Destructors
  MapBuilder(string StopwordsFilename, vector<string> InputFiles);
  ~MapBuilder();
  // Function declarations
  void load_Stopwords();
  bool is_Token_Valid(const string word_token);
  map<string, vector<Posting>> BuildMap();
  static void print_Map(ostream &, map<string, vector<Posting>> &);
  static bool is_Number(const string &s);

private:
  string stopwords_filename_;
  vector<string> stopwords_;
  vector<string> input_filenames_;
};
