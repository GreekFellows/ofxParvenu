#ifndef OFXPVCONTAINER_H
#define OFXPVCONTAINER_H

#include "ofMain.h"
#include "ofxPContainer.h"

class ofxPVContainer;

void swap(ofxPVContainer&, ofxPVContainer&);

class ofxPVContainer :public ofxPContainer {
	friend void swap(ofxPVContainer&, ofxPVContainer&);

public:
	// ctors, dtors and copy-control members
	ofxPVContainer() :ofxPContainer() {
		calculateMinBox();
	}

	ofxPVContainer(ofxParvenu* cparvenuPtr) :ofxPContainer(cparvenuPtr) {
		calculateMinBox();
	}

	ofxPVContainer(const ofxPContainer& copy) :ofxPContainer(copy) {
		calculateMinBox();
	}

	ofxPVContainer(ofxPContainer&& rval) :ofxPContainer(rval) {
		calculateMinBox();
	}

	ofxPVContainer& operator=(ofxPVContainer copy) {
		ofxPContainer::operator=(copy);
		swap(*this, copy);
		return *this;
	}

	virtual ~ofxPVContainer() {

	}

	// member functions
	virtual void draw(bool = false) override;
	virtual void calculateMinBox() override;

	virtual void setComponentPositions() override;

	virtual ofxPVContainer& setOuterBox(const ofRectangle& rect) override {
		_outerBox = rect;
		return *this;
	}

	// overloaded operators
	virtual bool operator==(ofxPVContainer& rhs) const {
		return ofxPContainer::operator==(rhs) && (true);
	}

	virtual bool operator!=(ofxPVContainer& rhs) const {
		return !(*this == rhs);
	}

	// members
	double _verticalPadding = { 10 }, _horizontalPadding = { 10 };
	bool _padInsideOnly = { false };
};

#endif