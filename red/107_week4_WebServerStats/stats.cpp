#include "stats.h"

HttpRequest ParseRequest(string_view line) {
	string_view data[3];
	size_t pos = line.find_first_not_of(' ');
	const size_t pos_end = line.npos;

	for (size_t i = 0; i < 3; i++) {
		size_t space = line.find(' ', pos);
		data[i] = (space == pos_end) ? line.substr(pos) : line.substr(pos, space - pos);

		if (space == pos_end) {
			break;
		} else {
			pos = space + 1;
		}
	}

	return {data[0], data[1], data[2]};
}

Stats::Stats() {
	for (const auto& el : METHODS) {
		m_methods[el] = 0;
	}
	m_methods[UNKNOWN_METHOD] = 0;

	for (const auto& el : URIS) {
		m_uri[el] = 0;
	}
	m_uri[UNKNOWN_URI] = 0;
}

void Stats::AddMethod(string_view method) {
	auto it = find(METHODS.begin(), METHODS.end(), method);
	if (it == METHODS.end()) {
		m_methods[UNKNOWN_METHOD]++;
	} else {
		m_methods[*it]++;
	}
}

void Stats::AddUri(string_view uri) {
	auto it = find(URIS.begin(), URIS.end(), uri);
	if (it == URIS.end()) {
		m_uri[UNKNOWN_URI]++;
	} else {
		m_uri[*it]++;
	}
}

const map<string_view, int>& Stats::GetMethodStats() const {
	return m_methods;
}

const map<string_view, int>& Stats::GetUriStats() const {
	return m_uri;
}
