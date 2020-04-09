#pragma once
#include <regex>
#include <string>
#include <vector>
using std::sregex_iterator;
using std::string;
using std::vector;

// Tokenizer class takes a string and breaks it up into a
// vector<string> of words. The class is reusable.
class Tokenizer {
public:
  // set up tokenizer
  Tokenizer(){};
  ~Tokenizer() {}
  sregex_iterator Begin() { return begin_; }
  sregex_iterator End() { return end_; }
  void ParseString(string &s, vector<string> &);

private:
  vector<string> tokens_{20};
  sregex_iterator begin_;
  sregex_iterator end_;
};
