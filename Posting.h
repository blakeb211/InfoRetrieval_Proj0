#pragma once
class Posting {
public:
  Posting(int, int);
  Posting();
  ~Posting(){};
  int DocId() { return doc_id_; }
  int Location() { return location_; }

private:
  int doc_id_;
  int location_;
};
