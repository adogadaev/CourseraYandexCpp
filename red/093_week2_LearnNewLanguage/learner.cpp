#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <sstream>

using namespace std;

class Learner {
 private:
  set<string> dict;

 public:
  int Learn(const vector<string>& words) {
	size_t oldSize = dict.size();
	dict.insert(words.begin(), words.end());

    return dict.size() - oldSize;
  }

  vector<string> KnownWords() {
    return vector<string>{dict.begin(), dict.end()};
  }
};

// plane car bike bicycle scooter
// bicycle scooter car bike unicycle
/*
int main() {
	Learner learner;
	string line;
	while (getline(cin, line)) {
		vector<string> words;
		stringstream ss(line);
		string word;
		while (ss >> word) {
			words.push_back(word);
		}
		cout << learner.Learn(words) << "\n";

		if (word == "exit")
			break;
	}
	cout << "=== known words ===\n";
	for (auto word : learner.KnownWords()) {
		cout << word << "\n";
	}
}
*/
