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
