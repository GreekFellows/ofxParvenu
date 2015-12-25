#ifndef OFXPTEXTAREA_H
#define OFXPTEXTAREA_H

#include "ofMain.h"
#include "ofxPComponent.h"

class ofxPTextArea;

void swap(ofxPTextArea&, ofxPTextArea&);

class ofxPTextArea :public ofxPComponent {
	friend void swap(ofxPTextArea&, ofxPTextArea&);

public:
	// ctors, dtors and copy-control members
	ofxPTextArea() :ofxPComponent() {
		calculateMinBox();
	}

	ofxPTextArea(ofxParvenu* cparvenuPtr) :ofxPComponent(cparvenuPtr) {
		calculateMinBox();
	}

	ofxPTextArea(ofxParvenu* cparvenuPtr, const std::string& ctext, ofxParvenu::FontStyle cfs = ofxParvenu::FontStyle::R) :ofxPComponent(cparvenuPtr), _text(ctext), _fontStyle(cfs) {
		calculateMinBox();
	}

	ofxPTextArea(const ofxPTextArea& copy) :ofxPComponent(copy) {
		calculateMinBox();
	}

	ofxPTextArea(ofxPTextArea&& rval) :ofxPComponent(rval) {
		calculateMinBox();
	}

	ofxPTextArea& operator=(ofxPTextArea copy) {
		ofxPComponent::operator=(copy);
		swap(*this, copy);
		return *this;
	}

	virtual ~ofxPTextArea() {

	}

	// member functions
	virtual void draw(bool = false) override;
	virtual void calculateMinBox() override;

	virtual ofxPTextArea& setOuterBox(const ofRectangle& rect) override {
		_outerBox = rect;
		return *this;
	}

	ofxPTextArea& setFontStyle(ofxParvenu::FontStyle fs) {
		_fontStyle = fs;
		return *this;
	}

	// overloaded operators
	virtual bool operator==(ofxPTextArea& rhs) const {
		return ofxPComponent::operator==(rhs) && (true);
	}

	virtual bool operator!=(ofxPTextArea& rhs) const {
		return !(*this == rhs);
	}

	// members
	std::string _text = { "lorem ipsum dolor sit amet.\nlorem ipsum dolor sit amet.\nlorem ipsum dolor sit amet." };
	ofRectangle _textBoundingBox;

	double _textPadding = { 5 };

	ofxParvenu::FontStyle _fontStyle = { ofxParvenu::FontStyle::R };
};

#endif