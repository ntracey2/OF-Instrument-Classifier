#include "ofApp.h"
//#include "FeatureExtraction.h"

//--------------------------------------------------------------
void ofApp::setup(){

	classifiers.push_back(nbc_select_button);
	classifiers.push_back(rf_select_button);

	class_slider.setup("Number of Classes", 0, 0, 20);
	class_slider.addListener(this, &ofApp::classSliderMoved);
	
	ofSetBackgroundColor(ofColor::teal);
	button.setBackgroundColor(ofColor::white);
	button.setTextColor(ofColor::black);
	button.addListener(this, &ofApp::fileButtonPressed);
	button.setup("Select Training Directory");

	load_model.setBackgroundColor(ofColor::white);
	load_model.setTextColor(ofColor::black);
	load_model.addListener(this, &ofApp::modelButtonPressed);
	load_model.setup("Load Model");

	test_dir_button.setBackgroundColor(ofColor::white);
	test_dir_button.setTextColor(ofColor::black);
	test_dir_button.addListener(this, &ofApp::modelButtonPressed);
	test_dir_button.setup("Select Test Directory");

	nbc_select_button.setBackgroundColor(ofColor::white);
	nbc_select_button.setTextColor(ofColor::black);
	nbc_select_button.addListener(this, &ofApp::nbcButtonPressed);
	nbc_select_button.setup("Naive Bayes");

	rf_select_button.setBackgroundColor(ofColor::white);
	rf_select_button.setTextColor(ofColor::black);
	rf_select_button.addListener(this, &ofApp::rfButtonPressed);
	rf_select_button.setup("Random Forest");

	train_button.setBackgroundColor(ofColor::white);
	train_button.setTextColor(ofColor::black);
	train_button.addListener(this, &ofApp::trainButtonPressed);
	train_button.setup("Train Model");

	save_model_button.setBackgroundColor(ofColor::white);
	save_model_button.setTextColor(ofColor::black);
	save_model_button.addListener(this, &ofApp::saveModelButtonPressed);
	save_model_button.setup("Save Model");

	classify_button.setBackgroundColor(ofColor::white);
	classify_button.setTextColor(ofColor::black);
	classify_button.addListener(this, &ofApp::classifyButtonPressed);
	classify_button.setup("Classify");

	
	gist.setDetect(GIST_PEAK_ENERGY);
	gist.setDetect(GIST_ROOT_MEAN_SQUARE);
	gist.setDetect(GIST_ZERO_CROSSING_RATE);
	gist.setDetect(GIST_PITCH);	//ludicrously slow
	gist.setDetect(GIST_SPECTRAL_CENTROID);
	gist.setDetect(GIST_SPECTRAL_CREST);
	gist.setDetect(GIST_SPECTRAL_DIFFERENCE);
	gist.setDetect(GIST_NOTE);
	gist.setDetect(GIST_SPECTRAL_DIFFERENCE_COMPLEX);
	gist.setDetect(GIST_SPECTRAL_DIFFERENCE_HALFWAY);
	gist.setDetect(GIST_SPECTRAL_FLATNESS);

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


	//class_slider.
	//std::string path = "[sax][cla]1573__1.wav";
	
	//std::vector<float> sample_vector;

	//PopulateTrainingMatrixFromDir("");

	//SaveTrainingMatrix();

	//PopulateTestingMatrixFromDir("");

	//SaveTestingMatrix();
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
	gist.processAudio(audio, 512, 1, 44100);

	//std::cout << "DONE!" << std::endl;
}

void ofApp::PopulateTrainingMatrixFromDir(std::string dir_path)
{
	//thank stack overflow for file iteration
	HANDLE hFind;
	WIN32_FIND_DATA FindFileData;
	dir_path.append("/*.wav");
	std::wstring stemp = std::wstring(dir_path.begin(), dir_path.end());
	LPCWSTR d = stemp.c_str();
	int sample = 0;
	if ((hFind = FindFirstFile(d, &FindFileData)) != INVALID_HANDLE_VALUE) {
		do {
			std::wstring ws(FindFileData.cFileName);
			std::string s(ws.begin(), ws.end());
			
			//FILL COLUMN
			std::cout << "processing " + s << std::endl;
			FillTrainingMatrixColumn(ofToDataPath("ReducedSetTest_\\" + s), sample);
			sample++;

		} while (FindNextFile(hFind, &FindFileData));
		FindClose(hFind);
	}
	else {
		std::cout << "something went wrong, check file path" << std::endl;
	}
}

void ofApp::PopulateTestingMatrixFromDir(std::string dir_path)
{
	//thank stack overflow for file iteration
	HANDLE hFind;
	WIN32_FIND_DATA FindFileData;
	dir_path.append("/*.wav");
	std::wstring stemp = std::wstring(dir_path.begin(), dir_path.end());
	LPCWSTR d = stemp.c_str();
	int sample = 0;
	if ((hFind = FindFirstFile(d, &FindFileData)) != INVALID_HANDLE_VALUE) {
		do {
			std::wstring ws(FindFileData.cFileName);
			std::string s(ws.begin(), ws.end());

			//FILL COLUMN
			std::cout << "processing " + s << std::endl;
			FillTrainingMatrixColumn(ofToDataPath("ReducedTesting_\\" + s), sample);
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
void ofApp::FillTestingMatrixColumn(std::string file, int c) {
	std::vector<float> features(GetFeatureVector(file));
	int i = 0;
	for (auto f : features) {
		test_matrix[c][i] = f;
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
	features.push_back(gist.getValue(GIST_PITCH));
	features.push_back(gist.getValue(GIST_SPECTRAL_CENTROID));
	features.push_back(gist.getValue(GIST_SPECTRAL_CREST));
	features.push_back(gist.getValue(GIST_SPECTRAL_DIFFERENCE));
	features.push_back(gist.getValue(GIST_SPECTRAL_DIFFERENCE_HALFWAY));
	features.push_back(gist.getValue(GIST_SPECTRAL_DIFFERENCE_COMPLEX));
	//features.push_back(gist.getValue(GIST_NOTE)); //returning NaN
	//features.push_back(gist.getValue(GIST_HIGH_FREQUENCY_CONTENT));
	features.push_back(gist.getValue(GIST_SPECTRAL_FLATNESS));
	features.push_back(gist.getMFCCAvg(12));
	features.push_back(gist.getMFCCMax(12));
	features.push_back(gist.getMFCCMin(12));



	features.push_back(iMap[file.substr(26, 3)]);	//label in last row

	return features;
}

void ofApp::SaveTrainingMatrix()
{
	std::cout << "WRITING TRAINING DATA TO CSV FILE" << std::endl;
	std::ofstream file;
	file.open("example.csv");
	for (int i = 0; i < data_matrix.size(); i++) {
		for (int j = 0; j < data_matrix[0].size(); j++) {
			file << data_matrix[i][j] << ",";
		}
		file << "\n";
	}
	file.close();
	std::cout << "DONE" << std::endl;
}
void ofApp::SaveTestingMatrix()
{
	std::cout << "WRITING TESTING DATA TO CSV FILE" << std::endl;
	std::ofstream file;
	file.open("testdata.csv");
	for (int i = 0; i < test_matrix.size(); i++) {
		for (int j = 0; j < data_matrix[0].size(); j++) {
			file << data_matrix[i][j] << ",";
		}
		file << "\n";
	}
	file.close();
	std::cout << "DONE" << std::endl;
}

std::vector<float> ofApp::GetSampleVector(std::string file_path) {
	if (ofFile::doesFileExist(file_path)) {
		audiofile.load(file_path);
		if (!audiofile.loaded()) {
			std::cout << "error loading file, double check the file path" << std::endl;
		}
	} else {
		std::cout << "input file does not exist" << std::endl;
	}

	float* samples_data = audiofile.data();

	std::vector<float> to_ret(samples_data, samples_data + audiofile.length());
	return to_ret;
}


//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofDrawBitmapString("Setup", 0, 15);

	button.draw();
	button.setPosition(0, 20);

	load_model.draw();
	load_model.setPosition(0, 50);
	test_dir_button.draw();
	test_dir_button.setPosition(0, 80);

	ofDrawBitmapString(dir_path, 100, 100);
	ofDrawBitmapString("Classifier Type", 0, 120);

	nbc_select_button.draw();
	nbc_select_button.setPosition(0, 125);

	rf_select_button.draw();
	rf_select_button.setPosition(0, 155);

	ofDrawBitmapString("Actions", 0, 195);

	train_button.draw();
	train_button.setPosition(0, 200);

	save_model_button.draw();
	save_model_button.setPosition(0, 230);

	classify_button.draw();
	classify_button.setPosition(0, 250);

	class_slider.setPosition(0, 300);
	class_slider.draw();

	ofDrawLine(205, 0, 205, 1000);

	if (shouldDrawConfusionMatrix) {
		std::vector<std::vector<float>> matr;
		for (int i = 0; i < matr.size(); i++) {
			for (int j = 0; j < matr[0].size(); j++) {
				ofDrawBitmapString(matr[i][j], 300 + (i * 20), 300 + (j * 20));
			}
		}
		shouldDrawConfusionMatrix = false;
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

void ofApp::fileButtonPressed()
{
	ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a training directory", true);

	if (nbc_select_button.getBackgroundColor() == ofColor::purple) {
		classifier.LoadData(openFileResult.getPath());
	}
	else {
		classifier.LoadData(openFileResult.getPath());
	}
}

void ofApp::modelButtonPressed() {
	ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a compatible training model");

	if (nbc_select_button.getBackgroundColor() == ofColor::purple) {
		classifier.LoadNBCModel(openFileResult.getPath());
	}
	else { 
		classifier.LoadRFModel(openFileResult.getPath());
	}
}

void ofApp::loadTestButtonPressed()
{
	ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a testing directory", true);

	if (nbc_select_button.getBackgroundColor() == ofColor::purple) {
		classifier.LoadTestData(openFileResult.getPath());
	}
	else {
		classifier.LoadTestData(openFileResult.getPath());
	}
}

void ofApp::nbcButtonPressed()
{
	rf_select_button.setBackgroundColor(ofColor::white);
	nbc_select_button.setBackgroundColor(ofColor::purple);
}

void ofApp::rfButtonPressed()
{
	nbc_select_button.setBackgroundColor(ofColor::white);
	rf_select_button.setBackgroundColor(ofColor::purple);
}

void ofApp::trainButtonPressed()
{
	if (nbc_select_button.getBackgroundColor() == ofColor::purple) {
		classifier.TrainNBC();
	} else { //default to random forrest if no selection
		classifier.TrainRF();
	}
}

void ofApp::saveModelButtonPressed()
{
	if (nbc_select_button.getBackgroundColor() == ofColor::purple) {
		classifier.SaveNBCModel();
	} else { 
		classifier.SaveRFModel();
	}
}

void ofApp::classifyButtonPressed()
{
	if (nbc_select_button.getBackgroundColor() == ofColor::purple) {
		classifier.ClassifyNBC();
	}
	else { 
		classifier.ClassifyRF();
	}
	shouldDrawConfusionMatrix = true;
}

void ofApp::classSliderMoved()
{
	classifier.setNumClasses(class_slider);
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
