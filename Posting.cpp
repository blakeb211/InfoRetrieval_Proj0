#include "Posting.h"

Posting::Posting(int in_doc_id, int in_location) {
  doc_id = in_doc_id;
  // add first element to the location vector
  location.emplace_back(in_location);
}

Posting::Posting() {
  doc_id = -1;
  location = {-1};
}

Posting::~Posting() {}
