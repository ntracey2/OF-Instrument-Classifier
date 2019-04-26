#pragma once

#include "ofMain.h"
#include "ofxAudioFile.h"
#include "ofxGist.h"
//#include "ofxDir.h"
//#include "ofxFile.h"

typedef enum INSTRUMENTS {
	cel,
	cla,
	flu,
	gac,
	gel,
	org,
	pia,
	sax,
	tru,
	vio,
	voi
};


class ofApp : public ofBaseApp{

	public:
		void setup();
		
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofxAudioFile audiofile;
		ofxGist gist;

		std::vector<float> GetSampleVector(std::string file_name);

		std::map<std::string, INSTRUMENTS> iMap;
		

		/*
		float GetZCR(const std::vector<float> &audio);
		float GetPeakEnergy(const std::vector<float> &audio);
		float GetRMS(const std::vector<float> &audio);
		float GetPitch(const std::vector<float> &audio);
		float GetSpecCentroid(const std::vector<float> &audio);
		float GetSpecCrest(const std::vector<float> &audio);
		float GetMFCC(const std::vector<float> &audio);
		*/

		void SetupGist(const std::vector<float> &audio);

		void PopulateTrainingMatrixFromDir(std::string dir_path);

		void FillTrainingMatrixColumn(std::string file, int i);

		std::vector<float> GetFeatureVector(std::string file);

		std::array<std::array<float, 6705>, 10> data_matrix;
		
};
