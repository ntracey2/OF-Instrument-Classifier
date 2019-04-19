#pragma once

//#define NOMINMAX
#include "ofMain.h"
#include "ofxMaxim.h"

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

		void audioOut(float *buffer, int bufferSize, int nChannels);
		void play(double *output);
		maxiSample testSample;
		

		maxiOsc osc;
		double frequency;
		double currentSample;
		unsigned bufferSize;
		unsigned sampleRate;


		ofSoundPlayer soundPlayer;
		ofSoundPlayer soundPlayer1;
		ofSoundStream soundStream;
		
};
