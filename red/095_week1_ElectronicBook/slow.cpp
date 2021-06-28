#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>
#include <utility>

using namespace std;

class ReadingManager {
public:
	ReadingManager() : mActiveUsersCount_(0) {}

	void Read(int user_id, int page_count) {
		if (aUserFinishedPagesNum_[user_id] == 0) {
			mActiveUsersCount_++;
		}
		else {
			aUsersToReachPage_[aUserFinishedPagesNum_[user_id]]--;
		}
		aUserFinishedPagesNum_[user_id] = page_count;
		aUsersToReachPage_[page_count]++;

		if (mActiveUsersCount_ == 1) {
			aUserRatingByFinishedPages_[page_count] = 1;
			return;
		}

		int losers_count = 0;
		for (int i = 1; i <= MAX_PAGE_COUNT_; i++) {
			aUserRatingByFinishedPages_[i] = losers_count * 1.0 / (mActiveUsersCount_ - 1);
			losers_count += aUsersToReachPage_[i];
		}
	}

	double Cheer(int user_id) const {
		return aUserRatingByFinishedPages_[aUserFinishedPagesNum_[user_id]];
	}

private:
	// Статическое поле не принадлежит какому-то конкретному
	// объекту класса. По сути это глобальная переменная,
	// в данном случае константная.
	// Будь она публичной, к ней можно было бы обратиться снаружи
	// следующим образом: ReadingManager::MAX_USER_COUNT.
	static const int MAX_USER_COUNT_ = 100'000;
	static const int MAX_PAGE_COUNT_ = 1'000;

	array<int, MAX_USER_COUNT_ + 1> aUserFinishedPagesNum_{0};
	size_t mActiveUsersCount_;
	array<int, MAX_PAGE_COUNT_ + 1> aUsersToReachPage_{0};
	array<double, MAX_USER_COUNT_ + 1> aUserRatingByFinishedPages_{0};
};

int main() {
	// Для ускорения чтения данных отключается синхронизация
	// cin и cout с stdio,
	// а также выполняется отвязка cin от cout
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ReadingManager manager;

	int query_count;
	cin >> query_count;

	for (int query_id = 0; query_id < query_count; ++query_id) {
		string query_type;
		cin >> query_type;
		int user_id;
		cin >> user_id;

		if (query_type == "READ") {
			int page_count;
			cin >> page_count;
			manager.Read(user_id, page_count);
		} else if (query_type == "CHEER") {
			cout << setprecision(6) << manager.Cheer(user_id) << "\n";
		}
	}

	return 0;
}
