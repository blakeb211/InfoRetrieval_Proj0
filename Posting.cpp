#include "Posting.h"

Posting::Posting(int doc_id, int location) {
  doc_id_ = doc_id;
  location_ = location;
}

Posting::Posting() {
  doc_id_ = -1;
  location_ = -1;
}
