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

static const size_t MAX_DOC_COUNT = 50000;

using IndexData = map<size_t, size_t>;
//using IndexData = vector<size_t>;

class InvertedIndex {
public:
	void Add(string&& document);
	const IndexData& Lookup(string_view word) const;

private:
	IndexData empty_data = {};
	map<string_view, IndexData> index;

	list<string> documents;
};

class SearchServer {
public:
	SearchServer() = default;
//	SearchServer() : search_results(MAX_DOC_COUNT) {}
	explicit SearchServer(istream& document_input);
	void UpdateDocumentBase(istream& document_input);
	void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
	InvertedIndex index;
	array<pair<size_t, size_t>, MAX_DOC_COUNT> search_results;
//	vector<pair<size_t, size_t>> search_results;
};
