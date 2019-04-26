#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ofApp.h"
#include "ofMain.h"

ofApp *app = new ofApp();


TEST_CASE("Catch Test") {
	REQUIRE(1 == 1);
}

TEST_CASE("Iterate through files") {
	app->setup();
	//app->PopulateTrainingMatrixFromDir("");
}