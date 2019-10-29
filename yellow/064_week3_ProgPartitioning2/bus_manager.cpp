/*
 * bus_manager.cpp
 *
 *  Created on: Nov 23, 2018
 *      Author: Anton Dogadaev
 */
#include "bus_manager.h"
#include "responses.h"

void BusManager::AddBus(const std::string& bus,
		const std::vector<std::string>& stops) {
	// Реализуйте этот метод
	for (const std::string& stop : stops) {
		buses_to_stops_[bus].push_back(stop);
		stops_to_buses_[stop].push_back(bus);
	}
}

BusesForStopResponse BusManager::GetBusesForStop(const std::string& stop) const {
	// Реализуйте этот метод
	if (stops_to_buses_.count(stop) == 0) {
		return {};
	}
	return {stops_to_buses_.at(stop)};
}

StopsForBusResponse BusManager::GetStopsForBus(const std::string& bus) const {
	// Реализуйте этот метод
	if (buses_to_stops_.count(bus) == 0) {
		return {"", {}, {}};
	}
	return {bus, buses_to_stops_.at(bus), stops_to_buses_};
}

AllBusesResponse BusManager::GetAllBuses() const {
	// Реализуйте этот метод
	return {buses_to_stops_};
}



