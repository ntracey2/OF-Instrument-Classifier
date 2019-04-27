#include "ofApp.h"
//#include "FeatureExtraction.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	//ofBackground(0);

	gist.setDetect(GIST_PEAK_ENERGY);
	gist.setDetect(GIST_ROOT_MEAN_SQUARE);
	gist.setDetect(GIST_ZERO_CROSSING_RATE);
	//gist.setDetect(GIST_PITCH);
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

	PopulateTrainingMatrixFromDir("");

	SaveTrainingMatrix();

	//for (int i = 0; i < data_matrix.size(); i++) {
	//	for (int j = 0; j < data_matrix[0].size(); j++) {
	//		std::cout << data_matrix[i][j] << ", ";
	//	}
	//	std::cout << std::endl;
	//}



	//std::vector<float> features(GetFeatureVector(ofToDataPath(path)));

	/*for (auto f : features) {
		std::cout << f << std::endl;
	}*/

	//sample_vector = GetSampleVector(ofToDataPath(path));

	//RetrieveData(sample_vector);
}




void ofApp::SetupGist(const std::vector<float> &audio)
{

	//int frameSize = 512;
	//int sampleRate = 44100;
	

	
	gist.clearHistory();

	std::vector<float> audioFrame(audio); //fill audio frame with samples


	//gist.processAudio(audioFrame);
	gist.processAudio(audio);

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
			std::cout << "processing " + s << std::endl;
			FillTrainingMatrixColumn(ofToDataPath("TrainingSamples\\" + s), sample);
			sample++;

		} while (FindNextFile(hFind, &FindFileData));
		FindClose(hFind);
	}
	else {
		std::cout << "something went wrong, check file path" << std::endl;
	}
}

void ofApp::FillTrainingMatrixColumn(std::string file, int c) {
	std::vector<float> features(GetFeatureVector(file));
	int i = 0;
	for (auto f : features) {
		data_matrix[c][i] = f;
		i++;
	}
}

std::vector<float> ofApp::GetFeatureVector(std::string file) {
	//std::vector<float> audio(GetSampleVector(file));
	SetupGist(GetSampleVector(file));

	std::vector<float> features;
	features.push_back(gist.getValue(GIST_ZERO_CROSSING_RATE));
	features.push_back(gist.getValue(GIST_PEAK_ENERGY));
	features.push_back(gist.getValue(GIST_ROOT_MEAN_SQUARE));
	//features.push_back(gist.getValue(GIST_PITCH));
	features.push_back(gist.getValue(GIST_SPECTRAL_CENTROID));
	features.push_back(gist.getValue(GIST_SPECTRAL_CREST));
	features.push_back(gist.getMFCCAvg(12));
	features.push_back(iMap[file.substr(26, 3)]);	//label in last row

	return features;
}

void ofApp::SaveTrainingMatrix()
{
	std::ofstream file;
	file.open("example.csv");
	for (int i = 0; i < data_matrix.size(); i++) {
		for (int j = 0; j < data_matrix[0].size(); j++) {
			file << data_matrix[i][j] << ",";
		}
		file << "\n";
	}
	file.close();
}

std::vector<float> ofApp::GetSampleVector(std::string file_path) {

	std::cout << file_path << std::endl;
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
