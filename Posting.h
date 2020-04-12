#pragma once
class Posting {
public:
  Posting(int, int);
  Posting();
  ~Posting(){};

  int doc_id_;
  int location_;
};
