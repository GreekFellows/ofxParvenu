#ifndef OFXPHCONTAINER_H
#define OFXPHCONTAINER_H

#include "ofMain.h"
#include "ofxPContainer.h"

class ofxPHContainer;

void swap(ofxPHContainer&, ofxPHContainer&);

class ofxPHContainer :public ofxPContainer {
	friend void swap(ofxPHContainer&, ofxPHContainer&);

public:
	// ctors, dtors and copy-control members
	ofxPHContainer() :ofxPContainer() {
		calculateMinBox();
	}

	ofxPHContainer(ofxParvenu* cparvenuPtr) :ofxPContainer(cparvenuPtr) {
		calculateMinBox();
	}

	ofxPHContainer(const ofxPContainer& copy) :ofxPContainer(copy) {
		calculateMinBox();
	}

	ofxPHContainer(ofxPContainer&& rval) :ofxPContainer(rval) {
		calculateMinBox();
	}

	ofxPHContainer& operator=(ofxPHContainer copy) {
		ofxPContainer::operator=(copy);
		swap(*this, copy);
		return *this;
	}

	virtual ~ofxPHContainer() {

	}

	// member functions
	virtual void draw(bool = false) override;
	virtual void calculateMinBox() override;

	virtual void setComponentPositions() override;

	virtual ofxPHContainer& setOuterBox(const ofRectangle& rect) override {
		_outerBox = rect;
		return *this;
	}

	// overloaded operators
	virtual bool operator==(ofxPHContainer& rhs) const {
		return ofxPContainer::operator==(rhs) && (true);
	}

	virtual bool operator!=(ofxPHContainer& rhs) const {
		return !(*this == rhs);
	}

	// members
	double _verticalPadding = { 10 }, _horizontalPadding = { 10 };
	bool _padInsideOnly = { false };
};

#endif