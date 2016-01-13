#include "ofxPComponent.h"

// swap
void swap(ofxPComponent& lhs, ofxPComponent& rhs) {
	using std::swap;
	swap(lhs._minBox, rhs._minBox);
	swap(lhs._outerBox, rhs._outerBox);
	swap(lhs._parvenuPtr, rhs._parvenuPtr);
}

void ofxPComponent::drawDebug() {
	double rx = sin(ofGetElapsedTimef() * 1.5 * ofNoise(_outerBox.x / 10.0)) * 20;
	double ry = cos(ofGetElapsedTimef() * 1.7 * -ofNoise(_outerBox.x / 10.0)) * 20;

	ofPushStyle();
	if (isMouseOver) {
		ofPushStyle();
		ofSetLineWidth(5);
	}

	ofSetColor(_idColor);
	ofNoFill();
	ofRect(_outerBox);
	ofLine(_outerBox.x, _outerBox.y, _outerBox.x + rx, _outerBox.y + ry);
	ofDrawBitmapStringHighlight(std::to_string((int)_outerBox.x) + ", \t" + std::to_string((int)_outerBox.y) + "\n" + std::to_string((int)_outerBox.width) + ", \t" + std::to_string((int)_outerBox.height), _outerBox.x + rx, _outerBox.y + ry, _idColor, ofColor::white);
	ofPopStyle();

	if (isMouseOver) {
		ofPopStyle();
	}
}

void ofxPComponent::drawTag() {
	ofPushStyle();
	ofDrawBitmapStringHighlight(_tag, _outerBox.x + 4, _outerBox.y - 4, ofColor::white, ofColor::black);
	ofSetColor(_idColor);
	ofNoFill();
	ofRect(_outerBox.x, _outerBox.y - 20, _tag.size() * 8 + 8, 20);
	ofPopStyle();
}

void ofxPComponent::fitOuterBoxToMinBox() {
	_outerBox.width = _minBox.width;
	_outerBox.height = _minBox.height;
}

ofRectangle ofxPComponent::getGlobalOuterBox() {
	return (!_parent) ? _outerBox : ofRectangle(_outerBox.x + _parent->getGlobalOuterBox().x, _outerBox.y + _parent->getGlobalOuterBox().y, _outerBox.width, _outerBox.height);
}

void ofxPComponent::mousePressed(ofMouseEventArgs &args) {
	for (auto ptr = _nonContainerChildren.rbegin(), end = _nonContainerChildren.rend(); ptr != end; ++ptr) {
		ofRectangle rect = (*ptr)->getGlobalOuterBox();
		if (rect.inside(args.x, args.y)) {
			(*ptr)->mousePressed(args);
			break;
		}
	}

	if (_isDraggable) {
		_dragOffset.x = _outerBox.x - args.x;
		_dragOffset.y = _outerBox.y - args.y;
	}

	isMousePressed = true;
	try {
		mousePressedFunc(args);
	}
	catch (std::bad_function_call) {
		// ugh
	}
}

void ofxPComponent::mouseReleased(ofMouseEventArgs &args) {
	for (auto ptr : _nonContainerChildren) {
		ptr->mouseReleasedWrapper(args);
	}

	isMousePressed = false;
	try {
		mouseReleasedFunc(args);
	}
	catch (std::bad_function_call) {
		// ugh
	}
}

void ofxPComponent::mouseMoved(ofMouseEventArgs &args) {
	for (auto ptr : _nonContainerChildren) {
		ptr->mouseMoved(args);
	}

	// if the mouse was not inside the box but is inside now, call mouseOver()
	if (getGlobalOuterBox().inside(args.x, args.y)) {
		if (!isMouseOver) {
			mouseOver(args);
		}
	}
	else {
		// if the mouse is not inside but it was before, call mouseOut()
		if (isMouseOver) {
			mouseOut(args);
		}
	}

	try {
		mouseMovedFunc(args);
	}
	catch (std::bad_function_call) {
		// ugh
	}
}

void ofxPComponent::mouseOver(ofMouseEventArgs &args) {
	isMouseOver = true;
	try {
		mouseOverFunc(args);
	}
	catch (std::bad_function_call) {
		// ugh
	}
}

void ofxPComponent::mouseOut(ofMouseEventArgs &args) {
	isMouseOver = false;
	// mouseReleasedWrapper(args); // in ofxParvenu, if you press a button, move your mouse out, then the button is considered released
	try {
		mouseOverFunc(args);
	}
	catch (std::bad_function_call) {
		// ugh
	}
}

void ofxPComponent::mouseDragged(ofMouseEventArgs &args) {
	for (auto ptr = _nonContainerChildren.rbegin(), end = _nonContainerChildren.rend(); ptr != end; ++ptr) {
		if ((*ptr)->isMousePressed) {
			(*ptr)->mouseDragged(args);
			break;
		}
	}

	if (!_isDraggable) {
		return;
	}

	isDragged = true;
	_outerBox.x = args.x + _dragOffset.x;
	_outerBox.y = args.y + _dragOffset.y;

	try {
		mouseDraggedFunc(args);
	}
	catch (std::bad_function_call) {
		// ugh
	}
}

void ofxPComponent::mouseReleasedWrapper(ofMouseEventArgs &args) {
	if (isMousePressed) {
		mouseReleased(args);
	}

	if (isDragged) {
		isDragged = false;
	}
}