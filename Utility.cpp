#include "Utility.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace Utility;

// Convert a string to a lowercase version by modifying it.
void Utility::ToLower(std::string &s) {
  // May be faster to merge terms than to do this for every token
  transform(s.begin(), s.end(), s.begin(), tolower);
}

// Check if a string is a sequence of integers
bool Utility::IsNumber(const std::string &s) {
  std::string::const_iterator it = s.begin();
  while (it != s.end() && isdigit(*it))
    ++it;
  return !s.empty() && it == s.end();
}
