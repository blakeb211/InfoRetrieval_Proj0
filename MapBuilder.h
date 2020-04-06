#pragma once
#include <fstream>
#include <iostream>
#include <map>

#include "Posting.h"
using std::map;
using std::ostream;

// Class with only object of it instantiated
class MapBuilder {
 public:
  // Constructor & Destructors
  MapBuilder(string StopwordsFilename, vector<string> InputFiles);
  ~MapBuilder();
  // Function declarations
  vector<string> LoadStopWords();
  map<string, vector<Posting>> BuildMap(const vector<string>&, vector<string>&);
  void PrintMap(ostream&, map<string, vector<Posting>>&);
  bool is_number(const string& s);
  bool is_Token_Valid(const vector<string>& stopwords, const string word_token);

 private:
  static string StopwordFile;
  static vector<string> InputFilenames;
};
