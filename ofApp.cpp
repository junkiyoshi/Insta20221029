#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetColor(255);
	ofSetLineWidth(0.5);

	ofNoFill();
	ofSetCircleResolution(120);

	this->mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh.clear();
	int max_radius = 300;

	for (float deg = 0; deg < 360; deg += 0.2) {

		int base = ofRandom(max_radius);
		int speed = ofRandom(2, 10);
		int tmp_deg = deg + ofGetFrameNum() * speed;

		auto radius = max_radius - (base + ofGetFrameNum() * speed) % max_radius;
		auto location_1 = glm::vec3(radius * cos(tmp_deg * DEG_TO_RAD), radius * sin(tmp_deg * DEG_TO_RAD), 0);
		auto color_1 = ofColor(255, radius > max_radius - 50 ? 255 : radius < 50 ? 0 : ofMap(radius, 50, max_radius - 50, 0, 255));

		tmp_deg += speed;
		
		radius = max_radius - (base + (ofGetFrameNum() + 2) * speed) % max_radius;
		auto location_2 = glm::vec3(radius * cos(tmp_deg * DEG_TO_RAD), radius * sin(tmp_deg * DEG_TO_RAD), 0);
		auto color_2 = ofColor(255, radius > max_radius - 50 ? 255 : radius < 50 ? 0 : ofMap(radius, 50, max_radius - 50, 0, 255));

		if (glm::distance(location_1, location_2) < 100) {

			this->mesh.addVertex(location_1);
			this->mesh.addVertex(location_2);

			this->mesh.addColor(color_1);
			this->mesh.addColor(color_2);

			this->mesh.addIndex(this->mesh.getNumVertices() - 1);
			this->mesh.addIndex(this->mesh.getNumVertices() - 2);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	this->mesh.drawWireframe();

	ofNoFill();
	ofSetColor(255);
	ofDrawCircle(glm::vec2(), 300);
}


//--------------------------------------------------------------
int main() {
	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}