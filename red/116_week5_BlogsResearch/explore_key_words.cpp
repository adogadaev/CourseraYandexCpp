#include "test_runner.h"
#include "profile.h"

#include <functional>
#include <future>
#include <map>
#include <numeric>
#include <string>
#include <vector>
using namespace std;

template <typename Iterator>
class IteratorRange {
public:
	IteratorRange(Iterator f, Iterator l) : first(f), last(l), size_(distance(first, last)) {}

	Iterator begin() const { return first; }
	Iterator end() const { return last; }

	size_t size() const { return size_; }
private:
	Iterator first, last;
	size_t size_;
};

template <typename Iterator>
class Paginator {
public:
	Paginator(Iterator begin, Iterator end, size_t page_size) {
		while (begin != end) {
			size_t dist = distance(begin, end);
			mPages.push_back({begin, next(begin, min(page_size, dist))});
			begin = next(begin, min(page_size, dist));
		}
	}

	auto begin() const { return mPages.begin(); }
	auto end() const { return mPages.end(); }

	size_t size() const { return mPages.size(); }
private:
	vector<IteratorRange<Iterator>> mPages;
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
	return Paginator{c.begin(), c.end(), page_size};
}

struct Stats {
	map<string, int> word_frequences;

	void operator += (const Stats& other) {
		for (const auto& [w, freq] : other.word_frequences) {
			word_frequences[w] += freq;
		}
	}

//	void operator += (const Stats& other) {
//		word_frequences = accumulate(other.word_frequences.begin(),
//									 other.word_frequences.end(),
//									 word_frequences,
//									 [](map<string, int>& m, const std::pair<const string, int>& p) {
//										 return (m[p.first] += p.second, m);
//									 });
//	}
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
	Stats result;
	vector<string> words;
	size_t pos = line.find_first_not_of(' ', 0);
	const size_t posEnd = string::npos;

	while (pos != posEnd) {
		size_t space = line.find(' ', pos);
		words.push_back(line.substr(pos, space - pos));
		pos = (space == posEnd) ?
			  posEnd : line.find_first_not_of(' ', space);
	}

	for (const auto& elem : words) {
		if (key_words.count(elem)) {
			result.word_frequences[elem] += 1;
		}
	}

	return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
	// Реализуйте эту функцию
	vector<string> data;
	for (string line; getline(input, line);) {
		data.push_back(move(line));
	}

	const size_t max_thread_num = 32;
	const size_t page_size = (data.size() % max_thread_num == 0) ?
					   (data.size() / max_thread_num) :
					   (data.size() / max_thread_num + 1);
	vector<future<Stats>> threads;

	for (auto page : Paginate(data, page_size)) {
		threads.push_back(async(
			[&key_words, page] {
				Stats interim_stats;
				for (const auto& line : page) {
					interim_stats += ExploreLine(key_words, line);
				}
				return interim_stats;
			})
		);
	}

	Stats final_stats;
	for (auto& t : threads) {
		final_stats += t.get();
	}

	return final_stats;
}

void TestBasic() {
	const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

	stringstream ss;
	ss << "\n";
	ss << "this new yangle service really rocks\n";
	ss << "It sucks when yangle isn't available\n";
	ss << "10 reasons why yangle is the best IT company\n";
	ss << "yangle rocks others suck\n";
	ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

	const auto stats = ExploreKeyWords(key_words, ss);
	const map<string, int> expected = {
			{"yangle", 6},
			{"rocks", 2},
			{"sucks", 1}
	};
	ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestBasic);
}
