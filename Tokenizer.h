#pragma once
#include <iostream>
#include <regex>
#include <string>
#include <vector>

using std::sregex_iterator;
using std::string;
using std::vector;

namespace Tokenizer {

static void ParseString(string &s, vector<string> &matches) {
  // build the regex for words with hyphens or apostrophes
  std::regex word_regex("([a-zA-Z-']{2,})");
  auto _begin = std::sregex_iterator(s.begin(), s.end(), word_regex);
  auto _end = std::sregex_iterator();
  std::cout << "Parsing string into tokens" << std::endl;
  for (auto i = _begin; i != _end; ++i) {
    matches.push_back(i->str());
  }
}

} // namespace Tokenizer
