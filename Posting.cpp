#include "Posting.h"

Posting::Posting(int in_doc_id, int in_location) {
  doc_id = in_doc_id;
  location = in_location;
}

Posting::Posting() {
  doc_id = -1;
  location = -1;
}

Posting::~Posting() {}
