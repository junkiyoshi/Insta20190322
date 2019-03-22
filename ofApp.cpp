#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofEnableDepthTest();
	ofSetLineWidth(2);

	this->size = 100;
	this->span = this->size * 1.5;
	ofColor color;
	int hue = 0;
	for (int x = -this->span; x <= this->span; x += this->span) {

		color.setHsb(hue, 180, 255);
		hue += 85;
		for (int y = -this->span; y <= this->span; y += this->span) {

			for (int z = -this->span; z <= this->span; z += this->span) {

				this->locations.push_back(glm::vec3(x, y, z));
				this->colors.push_back(color);
			}
		}
	}
	
	this->speed = 2;
	this->axis = { glm::vec3(1, 0,0), glm::vec3(0, 1,0) , glm::vec3(0, 0,1) };
	this->axis_index = 0;
	this->col = 0;
	this->direction = 1;
}

//--------------------------------------------------------------
void ofApp::update() {

	if (ofGetFrameNum() % (90 / this->speed) == 0) {

		this->axis_index = ofRandom(3);
		this->col = (int)ofRandom(3) * this->span - this->span;
		this->direction = ofRandom(2) < 1 ? this->speed : -this->speed;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	int color_index = 0;
	for (auto& location : this->locations) {

		if ((this->axis_index == 0 && (int)location.x == this->col) || (this->axis_index == 1 && (int)location.y == this->col) || (this->axis_index == 2 && (int)location.z == this->col)) {

			auto rotation = glm::rotate(glm::mat4(), (float)DEG_TO_RAD * this->direction, this->axis[this->axis_index]);
			location = glm::vec4(location, 0) * rotation;
		}

		ofFill();
		ofSetColor(this->colors[color_index++]);
		ofDrawBox(location, this->size * 0.99);

		ofNoFill();
		ofSetColor(39);
		ofDrawBox(location, this->size);
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}