/*
 * main.cpp
 *
 *  Created on: Oct 15, 2018
 *      Author: Anton Dogadaev
 */
#include <map>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main() {
	int req_num;
	map<string, vector<string>> map_stops;
	map<string, vector<string>> map_buses;
	string command;

	cin >> req_num;
	for (int i = 0; i < req_num; i++) {
		cin >> command;
		if (command == "NEW_BUS") {
			string bus, stop;
			int stop_count;

			cin >> bus >> stop_count;
			for (int j = 0; j < stop_count; j++) {
				cin >> stop;
				map_buses[bus].push_back(stop);
				map_stops[stop].push_back(bus);
			}
		}
		else if (command == "BUSES_FOR_STOP") {
			string stop;

			cin >> stop;
			if (map_stops.count(stop) == 0) {
				cout << "No stop" << endl;
			}
			else {
				for (const auto& bus_entry : map_stops[stop]) {
					cout << bus_entry << " ";
				}
				cout << endl;
			}
		}
		else if (command == "STOPS_FOR_BUS") {
			string bus;

			cin >> bus;
			if (map_buses.count(bus) == 0) {
				cout << "No bus" << endl;
			}
			else {
				for (const auto& stop_entry : map_buses[bus]) {
					cout << "Stop " << stop_entry << ": ";

					const auto& vStop = map_stops[stop_entry];
					if (vStop.size() == 1 && vStop[0] == bus) {
						cout << "no interchange";
					}
					else {
						for (const auto& bus_entry : vStop) {
							if (bus_entry != bus) {
								cout << bus_entry << " ";
							}
						}
					}
					cout << endl;
				}
			}
		}
		else if (command == "ALL_BUSES") {
			if (map_buses.size() == 0) {
				cout << "No buses" << endl;
			}
			else {
				for (const auto& bus_entry : map_buses) {
					cout << "Bus " << bus_entry.first << ": ";
					for (const auto& stop_entry : bus_entry.second) {
						cout << stop_entry << " ";
					}
					cout << endl;
				}
			}
		}
	}

	return 0;
}



