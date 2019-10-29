/*
 * bus_manager.h
 *
 *  Created on: Nov 23, 2018
 *      Author: Anton Dogadaev
 */

#pragma once

#include <vector>
#include <string>
#include <map>

#include "responses.h"

class BusManager {
public:
	void AddBus(const std::string& bus, const std::vector<std::string>& stops);
	BusesForStopResponse GetBusesForStop(const std::string& stop) const;
	StopsForBusResponse GetStopsForBus(const std::string& bus) const;
	AllBusesResponse GetAllBuses() const;
private:
	std::map<std::string, std::vector<std::string>>
					buses_to_stops_, stops_to_buses_;
};
