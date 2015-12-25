#ifndef OFXPBUTTON_H
#define OFXPBUTTON_H

#include "ofMain.h"
#include "ofxPComponent.h"

class ofxPButton;

void swap(ofxPButton&, ofxPButton&);

class ofxPButton :public ofxPComponent {
	friend void swap(ofxPButton&, ofxPButton&);
	
public:
	// ctors, dtors and copy-control members
	ofxPButton() :ofxPComponent() {
		calculateMinBox();
	}

	ofxPButton(ofxParvenu* cparvenuPtr) :ofxPComponent(cparvenuPtr) {
		calculateMinBox();
	}

	ofxPButton(ofxParvenu* cparvenuPtr, const std::string& clabel) :ofxPComponent(cparvenuPtr), _label(clabel) {
		calculateMinBox();
	}

	ofxPButton(const ofxPButton& copy) :ofxPComponent(copy) {
		calculateMinBox();
	}

	ofxPButton(ofxPButton&& rval) :ofxPComponent(rval) {
		calculateMinBox();
	}

	ofxPButton& operator=(ofxPButton copy) {
		ofxPComponent::operator=(copy);
		swap(*this, copy);
		return *this;
	}

	virtual ~ofxPButton() {

	}

	// member functions
	virtual void draw(bool = false) override;
	virtual void calculateMinBox() override;

	virtual ofxPButton& setOuterBox(const ofRectangle& rect) override {
		_outerBox = rect;
		return *this;
	}

	// overloaded operators
	virtual bool operator==(ofxPButton& rhs) const {
		return ofxPComponent::operator==(rhs) && (true);
	}

	virtual bool operator!=(ofxPButton& rhs) const {
		return !(*this == rhs);
	}

	// members
	std::string _label = { "click me :)" };
	ofRectangle _labelBoundingBox;
	ofxParvenu::FontStyle _fontStyle = { ofxParvenu::FontStyle::B };

	ofColor _fill = { 255, 51, 102 }, _stroke = { 0, 0 }, _labelColor = { 0 };

	double _labelPadding = { 15 };
};

#endif