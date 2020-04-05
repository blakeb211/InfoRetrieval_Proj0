#pragma once
#include <string>
using std::string;

class Posting {
public:
  Posting();
  Posting(int, int);
  ~Posting();

public:
  int doc_id;
  // TODO: Consider changing location to a better identifier like page and
  // paragraph
  int location;
};
