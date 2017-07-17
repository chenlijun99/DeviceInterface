#include <configuration/Configuration.hpp>
#include <iostream>
#include <string>
#include <fstream>

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>
#include <json.hpp>

TEST_CASE("Configuration module", "[configuration]") {

	std::ifstream fin;
	fin.open("doc/fpga.json", std::ios::in);

	Configuration c(fin);

	fin.close();
	REQUIRE( c.getDeviceConfiguration().maxAddress() == 41);
}
