#include <iostream>
#include <list>
#include <map>

using namespace std;

class Athletes {
public:
	void insert(int id, int before) {
		auto it = positions.find(before);
		if (it == positions.end()) {
			athletes.push_back(id);
			positions[id] = prev(athletes.end());
		} else {
			positions[id] = athletes.insert(it->second, id);
		}
	}

	friend ostream& operator<<(ostream& out, const Athletes& a) {
		for (const auto& el: a.athletes) {
			out << el << "\n";
		}
		return out;
	}

private:
	list<int> athletes;
	map<int, list<int>::iterator> positions;
};

int main() {
	Athletes a;

	int count;
	cin >> count;

	for (int i = 0; i < count; i++) {
		int new_id, before_id;
		cin >> new_id >> before_id;

		a.insert(new_id, before_id);
	}

	cout << a;

	return 0;
}
