#include <iostream>
#include <string>
#include <map>
#include <queue>

using namespace std;

class BookingSystem {
private:
	struct Booking {
		int64_t time;
		int client;
		int room_count;
		string hotel;
	};

public:
	BookingSystem() {}

	void Book(int64_t time, const string& hotel, int client, int room_count) {
		while (bookingQueue_.size() > 0 &&
			   time - 86400 >= bookingQueue_.front().time) {
			string h = bookingQueue_.front().hotel;
			int cl = bookingQueue_.front().client;
			int r_num = bookingQueue_.front().room_count;

			hotelRoomBookings_[h] -= r_num;
			hotelClientBookings_[h][cl]--;
			if (hotelClientBookings_[h][cl] == 0) {
				hotelClientNum_[h]--;
			}

			bookingQueue_.pop();
		}

		ResetHotelIfInactive(hotel);
		ResetHotelClientIfInactive(hotel, client);

		if (hotelClientBookings_[hotel][client] == 0) {
			hotelClientNum_[hotel]++;
		}
		hotelClientBookings_[hotel][client]++;
		hotelRoomBookings_[hotel] += room_count;

		bookingQueue_.push({time, client, room_count, hotel});
	}

	uint64_t GetClientsNumber(const string& hotel) {
		ResetHotelIfInactive(hotel);
		return hotelClientNum_[hotel];
	}

	uint64_t GetRoomsNumber(const string& hotel) {
		ResetHotelIfInactive(hotel);
		return hotelRoomBookings_[hotel];
	}

private:
	void ResetHotelClientIfInactive(const string& hotel, int client) {
		if (hotelClientBookings_.find(hotel) == hotelClientBookings_.end() ||
				hotelClientBookings_[hotel].find(client) == hotelClientBookings_[hotel].end()) {
			hotelClientBookings_[hotel][client] = 0;
		}
	}

	void ResetHotelIfInactive(const string& hotel) {
		if (hotelClientNum_.find(hotel) == hotelClientNum_.end()) {
			hotelClientNum_[hotel] = 0;
		}
		if (hotelRoomBookings_.find(hotel) == hotelRoomBookings_.end()) {
			hotelRoomBookings_[hotel] = 0;
		}
	}

private:
	map<string, uint64_t> hotelRoomBookings_; // room bookings per hotel in past 24 hours
	map<string, uint64_t> hotelClientNum_;	  // total clients number per hotel in past 24 hours
	map<string, map<uint32_t, uint32_t>> hotelClientBookings_; // bookings per client per hotel in past 24 hours
	queue<Booking> bookingQueue_;
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	BookingSystem bs;

	int query_count;
	cin >> query_count;

	for (int query = 0; query < query_count; ++query) {
		string query_type;
		cin >> query_type;

		if (query_type == "BOOK") {
			long int time;
			string hotel;
			int client;
			int room_count;

			cin >> time >> hotel >> client >> room_count;
			bs.Book(time, hotel, client, room_count);
		} else if (query_type == "CLIENTS") {
			string hotel;
			cin >> hotel;
			cout << bs.GetClientsNumber(hotel) << "\n";
		} else if (query_type == "ROOMS") {
			string hotel;
			cin >> hotel;
			cout << bs.GetRoomsNumber(hotel) << "\n";
		}
	}

	return 0;
}
