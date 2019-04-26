#include "ofApp.h"
//#include "FeatureExtraction.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	//ofBackground(0);

	gist.setDetect(GIST_PEAK_ENERGY);
	gist.setDetect(GIST_ROOT_MEAN_SQUARE);
	gist.setDetect(GIST_ZERO_CROSSING_RATE);
	gist.setDetect(GIST_PITCH);
	gist.setDetect(GIST_SPECTRAL_CENTROID);
	gist.setDetect(GIST_SPECTRAL_CREST);

	iMap.insert(pair<std::string, INSTRUMENTS>("cel", cel));
	iMap.insert(pair<std::string, INSTRUMENTS>("cla", cla));
	iMap.insert(pair<std::string, INSTRUMENTS>("flu", flu));
	iMap.insert(pair<std::string, INSTRUMENTS>("gac", gac));
	iMap.insert(pair<std::string, INSTRUMENTS>("gel", gel));
	iMap.insert(pair<std::string, INSTRUMENTS>("org", org));
	iMap.insert(pair<std::string, INSTRUMENTS>("pia", pia));
	iMap.insert(pair<std::string, INSTRUMENTS>("sax", sax));
	iMap.insert(pair<std::string, INSTRUMENTS>("tru", tru));
	iMap.insert(pair<std::string, INSTRUMENTS>("vio", vio));
	iMap.insert(pair<std::string, INSTRUMENTS>("voi", voi));

	//std::string path = "[sax][cla]1573__1.wav";
	
	//std::vector<float> sample_vector;



	//sample_vector = GetSampleVector(ofToDataPath(path));

	//RetrieveData(sample_vector);
}




void ofApp::SetupGist(const std::vector<float> &audio)
{

	//int frameSize = 512;
	//int sampleRate = 44100;
	

	
	gist.clearHistory();

	std::vector<float> audioFrame(audio);

	// !
	// fill audio frame with samples here
	// !

	gist.processAudio(audioFrame);

	//std::cout << "DONE!" << std::endl;
}

void ofApp::PopulateTrainingMatrixFromDir(std::string dir_path)
{
	//thank stack overflow for file iteration
	HANDLE hFind;
	WIN32_FIND_DATA FindFileData;
	LPCWSTR d = L"bin/data/TrainingSamples/*.wav";
	int sample = 0;
	if ((hFind = FindFirstFile(d, &FindFileData)) != INVALID_HANDLE_VALUE) {
		do {
			std::wstring ws(FindFileData.cFileName);
			std::string s(ws.begin(), ws.end());
			
			//FILL COLUMN

			FillTrainingMatrixColumn("bin/data/TrainingSamples/" + s, sample);
			sample++;

		} while (FindNextFile(hFind, &FindFileData));
		FindClose(hFind);
	}
	else {
		std::cout << "something went wrong" << std::endl;
	}
}

void ofApp::FillTrainingMatrixColumn(std::string file, int c) {
	std::vector<float> features = GetFeatureVector(file);
	int i = 0;
	for (auto f : features) {
		data_matrix[c][i];
		i++;
	}
}

std::vector<float> ofApp::GetFeatureVector(std::string file) {
	std::vector<float> audio(GetSampleVector(file));
	SetupGist(audio);

	std::vector<float> features;
	features.push_back(gist.getValue(GIST_ZERO_CROSSING_RATE));
	features.push_back(gist.getValue(GIST_PEAK_ENERGY));
	features.push_back(gist.getValue(GIST_ROOT_MEAN_SQUARE));
	features.push_back(gist.getValue(GIST_PITCH));
	features.push_back(gist.getValue(GIST_SPECTRAL_CENTROID));
	features.push_back(gist.getValue(GIST_SPECTRAL_CREST));
	features.push_back(gist.getMFCCAvg(12));
	features.push_back(iMap[file.substr(1, 3)]);	//label in last row

	return features;
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
