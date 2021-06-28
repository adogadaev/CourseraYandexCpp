#pragma once

#include "http_request.h"

#include <algorithm>
#include <array>
#include <string_view>
#include <string>
#include <map>
using namespace std;

class Stats {
public:
	Stats();

	void AddMethod(string_view method);
	void AddUri(string_view uri);

	const map<string_view, int>& GetMethodStats() const;
	const map<string_view, int>& GetUriStats() const;

private:
	inline static array<const string, 4> METHODS = {"GET", "POST", "PUT", "DELETE"};
	inline static array<const string, 5> URIS = {"/", "/order", "/product", "/basket", "/help"};
	inline static const string UNKNOWN_METHOD = "UNKNOWN";
	inline static const string UNKNOWN_URI = "unknown";
	map<string_view, int> m_methods;
	map<string_view, int> m_uri;
};

HttpRequest ParseRequest(string_view line);
