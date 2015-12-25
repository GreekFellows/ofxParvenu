#ifndef OFXPVCONTAINERWINDOW_H
#define OFXPVCONTAINERWINDOW_H

#include "ofMain.h"
#include "ofxPVContainer.h"
#include "ofxPTextArea.h"

class ofxPVContainerWindow;

void swap(ofxPVContainerWindow&, ofxPVContainerWindow&);

class ofxPVContainerWindow :public ofxPVContainer {
	friend void swap(ofxPVContainerWindow&, ofxPVContainerWindow&);

public:
	// ctors, dtors and copy-control members
	ofxPVContainerWindow() :ofxPVContainer() {
		calculateMinBox();
		_isDraggable = true;
	}

	// the only reason _wndTitleTextArea is constructed and pushed before calculateMinBox() is that calc..() is dependent on _wndTitleTextArea

	ofxPVContainerWindow(ofxParvenu* cparvenuPtr) :ofxPVContainer(cparvenuPtr) {
		_wndTitleTextArea = std::make_shared<ofxPTextArea>(_parvenuPtr, _wndTitle, ofxParvenu::FontStyle::B);
		calculateMinBox();
		_isDraggable = true;
	}

	ofxPVContainerWindow(ofxParvenu* cparvenuPtr, std::string cwndt) :ofxPVContainer(cparvenuPtr), _wndTitle(cwndt) {
		_wndTitleTextArea = std::make_shared<ofxPTextArea>(_parvenuPtr, _wndTitle, ofxParvenu::FontStyle::B);
		calculateMinBox();
		_isDraggable = true;
	}

	ofxPVContainerWindow(const ofxPVContainerWindow& copy) :ofxPVContainer(copy) {
		_wndTitleTextArea = std::make_shared<ofxPTextArea>(_parvenuPtr, _wndTitle, ofxParvenu::FontStyle::B);
		calculateMinBox();
		_isDraggable = true;
	}

	ofxPVContainerWindow(ofxPVContainerWindow&& rval) :ofxPVContainer(rval) {
		_wndTitleTextArea = std::make_shared<ofxPTextArea>(_parvenuPtr, _wndTitle, ofxParvenu::FontStyle::B);
		calculateMinBox();
		_isDraggable = true;
	}

	ofxPVContainerWindow& operator=(ofxPVContainerWindow copy) {
		ofxPVContainer::operator=(copy);
		swap(*this, copy);
		return *this;
	}

	virtual ~ofxPVContainerWindow() {

	}

	// member functions
	virtual void draw(bool = false) override;
	virtual void calculateMinBox() override;

	virtual void setComponentPositions() override;

	virtual ofxPVContainerWindow& setOuterBox(const ofRectangle& rect) override {
		_outerBox = rect;
		return *this;
	}

	// overloaded operators
	virtual bool operator==(ofxPVContainerWindow& rhs) const {
		return ofxPVContainer::operator==(rhs) && (true);
	}

	virtual bool operator!=(ofxPVContainerWindow& rhs) const {
		return !(*this == rhs);
	}

	// members
	ofColor _fill = { 255 }, _stroke = { 0 };
	std::string _wndTitle = { "window" };
	std::shared_ptr<ofxPTextArea> _wndTitleTextArea;
};

#endif