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

	// User defined type for crawling the inverted_index.
	// Each word being searched has 1 crawler.
	// Crawler sets its own Has_Reached_End flag.

	struct Crawler {
		public:
			Crawler(Post_It mover, Post_It end, string term);
			Post_It Mover;
			string Term;
			bool Has_Reached_End = false;
			void MoveForward();
		private:
			Post_It End_Marker;
	};

	// Return lowest docid of a vector of crawlers.
	// If -1 is returned, all crawlers have reached the end.
	int GetLowestDocId(const vector<Crawler>&);

	// Move crawlers forward if their docid matches the given docid.
	void MoveCrawlersForward(vector<Crawler>&, int);
	
	bool AreAllDocIdsTheSame(const vector<crawler>&);
} // end of namespace