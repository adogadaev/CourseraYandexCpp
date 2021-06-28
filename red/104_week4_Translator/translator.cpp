#include "test_runner.h"
#include <string>
#include <string_view>
#include <vector>
#include <map>
#include <set>

using namespace std;

class Translator {
public:
	Translator() {
		words_ = {};
	}

	void Add(string_view source, string_view target) {
		auto it_source = words_.insert(string(source));
		auto it_target = words_.insert(string(target));

		fwtrans_[*(it_source.first)] = it_target.first;
		bwtrans_[*(it_target.first)] = it_source.first;
	}

	string_view TranslateForward(string_view source) const {
		if (fwtrans_.find(source) == fwtrans_.end()) {
			return "";
		}
		return *(fwtrans_.at(source));
	}

	string_view TranslateBackward(string_view target) const {
		if (bwtrans_.find(target) == bwtrans_.end()) {
			return "";
		}
		return *(bwtrans_.at(target));
	}

private:
	set<string> words_;
	map<string_view, set<string>::iterator> fwtrans_;
	map<string_view, set<string>::iterator> bwtrans_;
};

void TestSimple() {
	Translator translator;
	translator.Add(string("okno"), string("window"));
	translator.Add(string("stol"), string("table"));

	ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
	ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
	ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestSimple);
	return 0;
}
