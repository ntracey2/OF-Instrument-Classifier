#pragma once

#include "ofMain.h"
#include "ofxAudioFile.h"
#include "ofxGist.h"
#include "ofxBaseGui.h"
#include "ofxGui.h"
#include "Classifier.h"

#define NUM_TRAINING_IMAGES 1497
#define NUM_FEATURES 14

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
private:
	std::array<std::array<float, NUM_FEATURES>, NUM_TRAINING_IMAGES> data_matrix;
	std::array<std::array<float, NUM_FEATURES>, 832> test_matrix;

	ofxButton button;
	ofxButton load_model;
	ofxButton test_dir_button;

	string model_path;
	string dir_path;
	string test_dir_path;

	ofxAudioFile audiofile;
	ofxGist gist;

	std::map<std::string, INSTRUMENTS> iMap;

	std::vector<ofxButton> classifiers;

	ofxButton nbc_select_button;
	ofxButton rf_select_button;

	ofxButton train_button;
	ofxButton save_model_button;
	ofxButton classify_button;

	Classifier classifier;

	ofxIntSlider class_slider;

	bool shouldDrawConfusionMatrix = false;

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



	std::vector<float> GetSampleVector(std::string file_name);



	void SetupGist(const std::vector<float> &audio);

	void PopulateTrainingMatrixFromDir(std::string dir_path);

	void PopulateTestingMatrixFromDir(std::string dir_path);

	void FillTrainingMatrixColumn(std::string file, int i);

	void FillTestingMatrixColumn(std::string file, int c);

	std::vector<float> GetFeatureVector(std::string file);


		
	void SaveTrainingMatrix();
	void SaveTestingMatrix();




	void fileButtonPressed();
	void modelButtonPressed();
	void loadTestButtonPressed();




	void nbcButtonPressed();
	void rfButtonPressed();



	void trainButtonPressed();
	void saveModelButtonPressed();
	void classifyButtonPressed();

	void classSliderMoved();
};
