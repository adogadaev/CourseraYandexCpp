#pragma once

#include "iterator_range.h"

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <tuple>
using namespace std;

//using IndexData = map<size_t, size_t>;
using IndexData = vector<pair<size_t, size_t>>;

class InvertedIndex {
public:
	void Add(string&& document);
	const IndexData& Lookup(string_view word) const;
	const size_t GetDocsSize() const;

private:
	IndexData empty_data = {};
	map<string_view, IndexData> index;

	list<string> documents;
};

class SearchServer {
public:
	SearchServer() = default;
	explicit SearchServer(istream& document_input);
	void UpdateDocumentBase(istream& document_input);
	void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
	InvertedIndex index;
};
