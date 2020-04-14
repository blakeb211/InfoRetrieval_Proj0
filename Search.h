#pragma once
#include <vector>
#include <string>
#include <forward_list>
#include "Posting.h"
using std::vector; 
using std::string;
using std::forward_list;

typedef forward_list<Posting>::iterator Post_It;

namespace Search {

vector<string> GetSearchTerms();

struct Crawler {
	Crawler(Post_It mover, Post_It end, string term);
	Post_It Mover;
	Post_It End_Marker;
	string Term;
	bool Has_Reached_End = false;
};

}