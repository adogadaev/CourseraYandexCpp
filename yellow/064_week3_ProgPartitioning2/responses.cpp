/*
 * responses.cpp
 *
 *  Created on: Nov 23, 2018
 *      Author: Anton Dogadaev
 */
#include "responses.h"

std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r) {
	// Реализуйте эту функцию
	if (r.buses.empty()) {
		os << "No stop";
	} else {
		for (const std::string& bus : r.buses) {
			os << bus << " ";
		}
	}
	return os;
}

std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r) {
	// Реализуйте эту функцию
	if (r.bus_stops.empty()) {
		os << "No bus";
	} else {
		bool first = true;
		for (const std::string& stop : r.bus_stops) {
			if (first == true) {
				first = false;
			} else {
				os << std::endl;
			}
			os << "Stop " << stop << ": ";
			if (r.stops_to_buses.at(stop).size() == 1) {
				os << "no interchange";
			} else {
				for (const std::string& other_bus : r.stops_to_buses.at(stop)) {
					if (r.bus != other_bus) {
						os << other_bus << " ";
					}
				}
			}
		}
	}

	return os;
}

std::ostream& operator << (std::ostream& os, const AllBusesResponse& r) {
	// Реализуйте эту функцию
	if (r.buses_to_stops.empty()) {
		os << "No buses";
	} else {
		bool first = true;
		for (const auto& bus_item : r.buses_to_stops) {
			if (first == true) {
				first = false;
			} else {
				os << std::endl;
			}
			os << "Bus " << bus_item.first << ": ";
			for (const std::string& stop : bus_item.second) {
				os << stop << " ";
			}
		}
	}
	return os;
}


