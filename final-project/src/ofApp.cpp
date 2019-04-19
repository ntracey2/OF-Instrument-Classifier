#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	sampleRate = 44100;
	bufferSize = 512;
	ofBackground(0);
	frequency = 440;

	//soundPlayer.load("C:/Users/nigel/Documents/CS 126/MusicDataTesting/0061.wav");
	soundPlayer1.load("C:/Users/nigel/Documents/CS 126/MusicDataTesting/0141.wav");
	soundPlayer1.setLoop(true);
	soundPlayer1.play();
	//ofSoundBuffer b;

	

	ofSoundStreamSetup(2, 0, this, sampleRate, bufferSize, 4);
	testSample.load("C:/Users/nigel/Documents/CS 126/MusicDataTesting/0061.wav");
	//printf("Summary:\n%s", testSample.getSummary());
}

//--------------------------------------------------------------
void ofApp::update(){
	float *s = ofSoundGetSpectrum(128);
	for (int i = 0; i < 128; i++) {
		cout << s[i] << "_";
	}
	cout << endl;
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
	frequency = (double) ofMap(x, 0, ofGetWidth(), 50, 800);
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

void ofApp::audioOut(float * buffer, int bufferSize, int nChannels)
{
	/*for (unsigned i = 0; i < bufferSize; i++) {
		currentSample = osc.square(frequency);

		buffer[i * nChannels] = currentSample;
		buffer[i * nChannels + 1] = currentSample;
	}*/
}

void ofApp::play(double * output)
{
	//output[0] = testSample.play(.25);
	//output[1] = output[0];
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
