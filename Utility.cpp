#include "Utility.h"
#include <algorithm>
#include <string>
#include <vector>
#include "boost/algorithm/string.hpp"
using namespace Utility;
using namespace std;
// Convert a string to a lowercase version by modifying it.
void Utility::ToLower(std::string &str) {
  // May be faster to merge terms than to do this for every token
  string tmp = str;
  boost::algorithm::to_lower(tmp);
  str = tmp;
}

// Check if a string is a sequence of integers
bool Utility::IsNumber(const std::string &s) {
  std::string::const_iterator it = s.begin();
  while (it != s.end() && isdigit(*it))
    ++it;
  return !s.empty() && it == s.end();
}
