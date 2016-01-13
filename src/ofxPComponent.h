#ifndef OFXPCOMPONENT_H
#define OFXPCOMPONENT_H	

#include "ofMain.h"
#include "ofxParvenu.h"

extern class ofxParvenu;
class ofxPComponent;

void swap(ofxPComponent&, ofxPComponent&);

class ofxPComponent {
	friend void swap(ofxPComponent&, ofxPComponent&);

public:
	// ctors, dtors and copy-control members
	ofxPComponent() :_minBox(0, 0, 0, 0), _outerBox(0, 0, 0, 0), _parvenuPtr(nullptr) {}

	// constructor taking initializers for _parvenuPtr
	ofxPComponent(ofxParvenu* cparvenuPtr) :_minBox(0, 0, 0, 0), _outerBox(0, 0, 0, 0), _parvenuPtr(cparvenuPtr) {}

	// copy constructor
	ofxPComponent(const ofxPComponent& copy) :_minBox(copy._minBox), _outerBox(copy._outerBox), _parvenuPtr(copy._parvenuPtr) {}

	// move constructor
	ofxPComponent(ofxPComponent&& rval) :_minBox(rval._minBox), _outerBox(rval._outerBox), _parvenuPtr(rval._parvenuPtr) {}

	// copy- / move-assignment operator with copy-and-swap
	ofxPComponent& operator=(ofxPComponent copy) {
		swap(*this, copy);
		return *this;
	}

	virtual ~ofxPComponent() {
		_parvenuPtr = nullptr;
	}

	// member functions
	virtual void draw(bool = false) {}
	void drawDebug();
	void drawTag();
	virtual void calculateMinBox() {}
	
	void fitOuterBoxToMinBox();
	ofRectangle getGlobalOuterBox();

	virtual ofxPComponent& setOuterBox(const ofRectangle& rect) {
		_outerBox = rect;
		return *this;
	}

	// event listeners
	virtual void mousePressed(ofMouseEventArgs& args);
	virtual void mouseReleased(ofMouseEventArgs& args);
	virtual void mouseMoved(ofMouseEventArgs& args);
	virtual void mouseOver(ofMouseEventArgs& args);
	virtual void mouseOut(ofMouseEventArgs& args);
	virtual void mouseDragged(ofMouseEventArgs& args);

	// this function is called whenever there is an mouseReleased event
	// this function checks if isMousePressed is true; if so, it calls the actual mouseReleased()
	// in container components, this function should call mouseReleasedWrapper() of all its children
	virtual void mouseReleasedWrapper(ofMouseEventArgs&);

	// overloaded operators
	virtual bool operator==(ofxPComponent& rhs) const {
		return (_minBox == rhs._minBox) && (_outerBox == rhs._outerBox);
	}

	virtual bool operator!=(ofxPComponent& rhs) const {
		return !(*this == rhs);
	}

	// members
	ofRectangle _minBox, _outerBox;										// the minimum bounding box and the actual bounding box
	ofxParvenu* _parvenuPtr;											// the pointer to ofxParvenu, mainly used in drawing texts. ofxParvenu is not dynamically allocated.
	std::shared_ptr<ofxPComponent> _parent = { nullptr };				// the pointer to this component's parent, dynamically allocated
	std::vector<std::shared_ptr<ofxPComponent>> _nonContainerChildren;	// components that make up a bigger component which is not necessarily a container, e.g. the button in ofxPHSlider
	ofColor _idColor = { rand() % 255, rand() % 255, rand() % 255 };	// randomly generated color that is used in this ofxPComponent exclusively in drawDebug()
	std::string _tag = { "" };											// a tag is not part of _outerBox; it's just a little "tag" that floats on the top-left corner of the window. in fact i was just too lazy to draw it out.
	bool _drawTag = { false };
	
	bool _isDraggable = { false };			// by default this is false. some ofxPComponent-derived classes have this yes, like ofxPWindow. ONLY SET NON-CHILD COMPONENTS TO BE DRAGGABLE. OR WEIRD THINGS HAPPEN.
	ofVec2f _dragOffset;

	bool isMousePressed = { false }, isMouseOver = { false }, isDragged = { false };/*
	void(*mousePressedFunc)(ofMouseEventArgs&) = { nullptr };
	void(*mouseReleasedFunc)(ofMouseEventArgs&) = { nullptr };
	void(*mouseMovedFunc)(ofMouseEventArgs&) = { nullptr };
	void(*mouseOverFunc)(ofMouseEventArgs&) = { nullptr };
	void(*mouseOutFunc)(ofMouseEventArgs&) = { nullptr };
	void(*mouseDraggedFunc)(ofMouseEventArgs&) = { nullptr };*/

	std::function<void(ofMouseEventArgs&)> mousePressedFunc, mouseReleasedFunc, mouseMovedFunc, mouseOverFunc, mouseOutFunc, mouseDraggedFunc;
	bool _deleteMe = { false };				// set this to true if you wish the component to be deleted from ofxParvenu::_comps.
};

#endif