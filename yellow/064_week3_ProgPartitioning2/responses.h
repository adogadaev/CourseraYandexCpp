/*
 * responses.h
 *
 *  Created on: Nov 23, 2018
 *      Author: Anton Dogadaev
 */

#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>

struct BusesForStopResponse {
	// Наполните полями эту структуру
	std::vector<std::string> buses;
};

struct StopsForBusResponse {
	// Наполните полями эту структуру
	std::string bus;
	std::vector<std::string> bus_stops;
	std::map<std::string, std::vector<std::string>> stops_to_buses;
};

struct AllBusesResponse {
	// Наполните полями эту структуру
	std::map<std::string, std::vector<std::string>> buses_to_stops;
};

std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r);
std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r);
std::ostream& operator << (std::ostream& os, const AllBusesResponse& r);
