/*#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ofApp.h"
#include "ofMain.h"

using std::cout;
using std::vector;
using std::endl;

ofApp app;


TEST_CASE("Catch test") {
	REQUIRE(1 == 1);
}

TEST_CASE("Iterate through files") {
	//app->setup();
	//app->PopulateTrainingMatrixFromDir("");
}
/*
TEST_CASE("Get basic features") {
	app.setup();
	vector<float> buffer = app.GetSampleVector(ofToDataPath("[sax][cla]1573__1.wav"));
	app.SetupGist(buffer);

	SECTION("Get ZCR") {
		cout << app.gist.getValue(GIST_ZERO_CROSSING_RATE) << endl;
	}
	SECTION("Get peak energy") {
		cout << app.gist.getValue(GIST_PEAK_ENERGY) << endl;
	}
	SECTION("Get RMS") {
		cout << app.gist.getValue(GIST_ROOT_MEAN_SQUARE) << endl;
	}
	SECTION("Get Pitch") {
		cout << app.gist.getValue(GIST_PITCH) << endl;
	}
	SECTION("Get Spectral Centroid") {
		cout << app.gist.getValue(GIST_SPECTRAL_CENTROID) << endl;
	}
	SECTION("Get Spectral Crest") {
		cout << app.gist.getValue(GIST_SPECTRAL_CREST) << endl;
	}
	SECTION("Get MFCC") {
		//cout << app->gist.getMFCCAvg(12) << endl;
	}
}
*//*
TEST_CASE("Get feature vector") {
	app.setup();
	//vector<float> buffer = app.GetSampleVector();
	vector<float> features = app.GetFeatureVector(ofToDataPath("[sax][cla]1573__1.wav"));

	for (auto f : features) {
		cout << f << endl;
	}
}*/

TEST_CASE("Test classification") {
	SECTION("") {
		
	}
}