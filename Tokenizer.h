#pragma once
#include <regex>
#include <string>
#include <vector>
using std::string;
using std::vector;
typedef vector<string>::iterator Vec_It;

// Tokenizer class takes a string and breaks it up into a
// vector<string> of words. The class is reusable.
class Tokenizer {
public:
  // set up tokenizer
  Tokenizer(){};
  ~Tokenizer() {}
  Vec_It Begin() { return begin_; }
  Vec_It End() { return end_; }
  void ParseInput(string s);

private:
  vector<string> tokens_{20};
  Vec_It begin_;
  Vec_It end_;
};
