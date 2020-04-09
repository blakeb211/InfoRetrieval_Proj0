#include "Tokenizer.h"
#include <iostream>

void Tokenizer::ParseString(string &s, vector<string> &matches) {
  // build the regex for words with hyphens or apostrophes
  std::regex word_regex("([a-zA-Z\-\']+)");
  begin_ = std::sregex_iterator(s.begin(), s.end(), word_regex);
  end_ = std::sregex_iterator();
  std::cout << "Parsing string into tokens" << std::endl;
  for (auto i = begin_; i != end_; ++i) {
    matches.emplace_back(i->str());
  }
}
