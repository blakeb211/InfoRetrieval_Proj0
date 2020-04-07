#pragma once
#include <string>
#include <vector>
using std::vector;

class Posting {
public:
  Posting();
  Posting(int, int);
  ~Posting();

public:
  int doc_id;
  // TODO: Consider changing location to a better identifier like page and
  // paragraph
  vector<int> location;
};
