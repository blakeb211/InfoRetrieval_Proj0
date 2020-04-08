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
  void LoadStopwords();
  bool IsTokenValid(const string word_token);
  void GetTermsAndPostings();
  void SortTerms();
  void BuildDictionary();

  map<string, vector<Posting>> BuildMap();
  static void PrintMap(ostream &, map<string, vector<Posting>> &);
  static bool IsNumber(const string &s);

private:
  string stopwords_filename_;
  vector<string> stopwords_;
  vector<string> input_filenames_;
};
