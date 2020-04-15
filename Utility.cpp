#include "Utility.h"
#include <algorithm>
#include <string>
#include <vector>
#include <cctype>
using namespace Utility;
using namespace std;
// Convert a string to a lowercase version by modifying it.
void Utility::ToLower(std::string &s) {
  // May be faster to merge terms than to do this for every token
  string tmp = s;
  for (int i = 0; i < s.size(); i++)
    std::tolower(tmp[i]);

  s = tmp;
}

// Check if a string is a sequence of integers
bool Utility::IsNumber(const std::string &s) {
  std::string::const_iterator it = s.begin();
  while (it != s.end() && isdigit(*it))
    ++it;
  return !s.empty() && it == s.end();
}
