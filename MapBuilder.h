#include "Posting.h"
#include <algorithm>
#include <forward_list>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <regex>

using std::forward_list;
using std::map;
using std::ostream;
using std::string;
using std::vector;

class MapBuilder {
public:
  // Constructor & Destructors
  MapBuilder(const string &StopwordsFilename,
             const vector<string> &InputFilenames)
      : stopwords_filename_(StopwordsFilename),
        input_filenames_(InputFilenames) {}
  ~MapBuilder(){};

  // Function declarations
  void LoadStopwords();
  bool IsTokenValid(const string);
  void ProcessInputFiles();
  void AddPostingToMap(string, int, int);
  void SortMap();
  unsigned int GetIndexSize();
  void PrintMap(ostream &);
  static void ToLower(string &);
  static bool IsNumber(const string &s);

private:
  string stopwords_filename_;
  vector<string> stopwords_;
  const vector<string> input_filenames_;
  map<string, forward_list<Posting>> inverted_index;
};
