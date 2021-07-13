#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <array>
#include <iterator>
#include <sstream>
#include <iostream>

vector<string_view> SplitIntoWords(string_view line) {
//	istringstream words_input(line);
//	return {istream_iterator<string_view>(words_input), istream_iterator<string_view>()};

	vector<string_view> words;
	size_t pos = line.find_first_not_of(' ', 0);
	const size_t posEnd = string::npos;

	while (pos != posEnd) {
		size_t space = line.find(' ', pos);
		words.push_back(line.substr(pos, space - pos));
		pos = (space == posEnd) ?
				posEnd : line.find_first_not_of(' ', space);
	}

	return words;
}

SearchServer::SearchServer(istream& document_input) {
	UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
	InvertedIndex new_index;

	for (string current_document; getline(document_input, current_document); ) {
		new_index.Add(move(current_document));
	}

	index = move(new_index);
}

void SearchServer::AddQueriesStream(
		istream& query_input, ostream& search_results_output
) {
	for (string current_query; getline(query_input, current_query); ) {
		fill(search_results.begin(), search_results.end(), make_pair(0, 0));
		for (const auto& word : SplitIntoWords(current_query)) {
			for (const auto& [docid, count] : index.Lookup(word)) {
				search_results[docid].first = docid;
				search_results[docid].second += count;
			}
		}

		partial_sort(begin(search_results),
					 begin(search_results) + 5,
					 end(search_results),
					 [](const pair<size_t, size_t>& lhs, const pair<size_t, size_t>& rhs) {
						 int64_t lhs_docid = -lhs.first;
						 auto lhs_hit_count = lhs.second;
						 int64_t rhs_docid = -rhs.first;
						 auto rhs_hit_count = rhs.second;
						 return tie(lhs_hit_count, lhs_docid) > tie(rhs_hit_count, rhs_docid);
					 }
		);

		search_results_output << current_query << ':';
		for (auto [docid, hitcount] : Head(search_results, 5)) {
			if (hitcount != 0) {
				search_results_output << " {"
						<< "docid: " << docid << ", "
						<< "hitcount: " << hitcount << '}';
			}
		}
		search_results_output << endl;
	}
}

void InvertedIndex::Add(string&& document) {
	documents.push_back(move(document));
	const size_t docid = documents.size() - 1;
	for (const auto& word : SplitIntoWords(documents.back())) {
		index[word][docid]++;
	}
}

const IndexData& InvertedIndex::Lookup(string_view word) const {
	if (auto it = index.find(word); it != index.end()) {
		return it->second;
	}
	return empty_data;
}
