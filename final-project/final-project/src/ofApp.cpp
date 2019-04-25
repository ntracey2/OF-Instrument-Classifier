#include "ofApp.h"
//#include "FeatureExtraction.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);

	std::string path = "[sax][cla]1573__1.wav";
	
	std::vector<float> sample_vector;

	sample_vector = GetSampleVector(ofToDataPath(path));

	RetrieveData(sample_vector);
}


void ofApp::RetrieveData(std::vector<float> audio)
{

	int frameSize = 512;
	int sampleRate = 44100;
	
	ofxGist gist;
	
	

	std::vector<float> audioFrame = audio;

	// !
	// fill audio frame with samples here
	// !
	gist.setDetect(GIST_PEAK_ENERGY);
	gist.setDetect(GIST_ROOT_MEAN_SQUARE);
	gist.setDetect(GIST_ZERO_CROSSING_RATE);
	gist.processAudio(audio);
	//gist.

	// Root Mean Square (RMS)
	float rms = gist.getValue(GIST_ROOT_MEAN_SQUARE);
	std::cout << rms << std::endl;
	//float rms = gist.rootMeanSquare();

	// Peak Energy
	float peakEnergy = gist.getValue(GIST_PEAK_ENERGY);
	std::cout << peakEnergy << std::endl;
	//float peakEnergy = gist.peakEnergy();

	// Zero Crossing rate
	float zcr = gist.getValue(GIST_ZERO_CROSSING_RATE);
	std::cout << zcr << std::endl;
	//float zcr = gist.zeroCrossingRate();
	std::cout << "DONE!" << std::endl;
}


std::vector<float> ofApp::GetSampleVector(std::string file_path) {


	if (ofFile::doesFileExist(file_path)) {
		audiofile.load(file_path);
		if (!audiofile.loaded()) {
			std::cout << "error loading file, double check the file path" << std::endl;
		}
	}
	else {
		std::cout << "input file does not exist" << std::endl;
	}

	//audiofile.load(file_path);

	float* samples_data = audiofile.data();
	if (audiofile.loaded()) {
		//std::cout << "Attempting to print audio buffer" << std::endl;
		/*for (int i = 0; i < audiofile.length(); i++) {
			std::cout << samples_data[i] << std::endl;
		}*/
	}
	else {
		std::cout << "file not loaded properly!" << std::endl;
	}

	std::vector<float> to_ret(samples_data, samples_data + audiofile.length());
	return to_ret;
}








//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
