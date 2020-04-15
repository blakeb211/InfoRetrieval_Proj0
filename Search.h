#pragma once
#include "Posting.h"
#include <forward_list>
#include <string>
#include <vector>
using std::forward_list;
using std::string;
using std::vector;

typedef forward_list<Posting>::iterator Post_It;

namespace Search {

vector<string> GetSearchTerms();

void MakeUnique(vector<int> &);

int CountDocId(forward_list<Posting>::iterator it,
               forward_list<Posting>::iterator end_it, int docid);
} // namespace Search
