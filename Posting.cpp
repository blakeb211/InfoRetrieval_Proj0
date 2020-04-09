#include "Posting.h"

Posting::Posting(int in_doc_id) {
  doc_id = in_doc_id;
  // add first element to the location vector
}

Posting::Posting() {
  doc_id = -1;
  frequency = 0;
}

Posting::~Posting() {}
