#ifndef OFXPCONTAINER_H
#define OFXPCONTAINER_H

#include "ofMain.h"
#include "ofxPComponent.h"

class ofxPContainer;

void swap(ofxPContainer&, ofxPContainer&);

// ofxPContainer must be inherited
class ofxPContainer :public ofxPComponent, public std::enable_shared_from_this<ofxPContainer> {
	friend void swap(ofxPContainer&, ofxPContainer&);

public:
	// enumerations to specify content alignment in each "cell"
	enum class ContentAlignment {
		HL, HC, HR, VT, VM, VB // Horizontal Left, Center, Right, Vertical Top, Middle, Bottom
	};

	// ctors, dtors and copy-control members
	ofxPContainer() :ofxPComponent() {
		calculateMinBox();
	}

	ofxPContainer(ofxParvenu* cparvenuPtr) :ofxPComponent(cparvenuPtr) {
		calculateMinBox();
	}

	ofxPContainer(const ofxPContainer& copy) :ofxPComponent(copy) {
		calculateMinBox();
	}

	ofxPContainer(ofxPContainer&& rval) :ofxPComponent(rval) {
		calculateMinBox();
	}

	ofxPContainer& operator=(ofxPContainer copy) {
		ofxPComponent::operator=(copy);
		swap(*this, copy);
		return *this;
	}

	virtual ~ofxPContainer() {

	}

	// member functions
	virtual void draw(bool = false) override {}
	virtual void calculateMinBox() override {}

	virtual void mousePressed(ofMouseEventArgs& args) override;
	virtual void mouseReleased(ofMouseEventArgs& args) override;
	virtual void mouseMoved(ofMouseEventArgs& args) override;
	virtual void mouseDragged(ofMouseEventArgs& args) override;

	// sets the positions of components (_outerBox.x, _outerBox.y)
	virtual void setComponentPositions();

	virtual void pushComponent(std::shared_ptr<ofxPComponent>, ContentAlignment, ContentAlignment, bool);
	virtual void pushComponent(std::shared_ptr<ofxPComponent>, ContentAlignment, ContentAlignment);
	virtual void pushComponent(std::shared_ptr<ofxPComponent>, bool);
	virtual void pushComponent(std::shared_ptr<ofxPComponent>);

	virtual ofxPContainer& setOuterBox(const ofRectangle& rect) override {
		_outerBox = rect;
		return *this;
	}

	void deleter();

	// overloaded operators
	virtual bool operator==(ofxPContainer& rhs) const {
		return ofxPComponent::operator==(rhs) && (true);
	}

	virtual bool operator!=(ofxPContainer& rhs) const {
		return !(*this == rhs);
	}

	// members
	std::vector<std::shared_ptr<ofxPComponent>> _children;
	std::vector<std::pair<ContentAlignment, ContentAlignment>> _alignments;
	bool _childIsMousePressed = { false }; // used to check if the component can be dragged. see _noDragIfChildPressed.
	bool _noDragIfChildPressed = { true };	// prevents a draggable component from being dragged when a child of it is pressed. true by default.

	std::vector<bool> _drawSeparators; // contains as many bools as many components in _children. each bool specifies whether a separator is drawn after the corresponding element. since separators are drawn BETWEEN components, the last bool in this vector is ignored.
	ofColor _separatorStroke = { 0, 64 };

	static const double __separatorFactor;
};

#endif