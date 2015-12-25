#include "ofxPComponent.h"

// swap
void swap(ofxPComponent& lhs, ofxPComponent& rhs) {
	using std::swap;
	swap(lhs._minBox, rhs._minBox);
	swap(lhs._outerBox, rhs._outerBox);
	swap(lhs._parvenuPtr, rhs._parvenuPtr);
}

void ofxPComponent::drawDebug() {
	ofPushStyle();
	ofSetColor(_idColor);
	ofNoFill();
	ofRect(_outerBox);
	ofLine(_outerBox.x, _outerBox.y, _outerBox.x + 20, _outerBox.y + 20);
	ofDrawBitmapStringHighlight(std::to_string(_outerBox.x) + ", " + std::to_string(_outerBox.y), _outerBox.x + 20, _outerBox.y + 20, _idColor, ofColor::white);
	ofPopStyle();
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
	isMousePressed = true;
	if (mousePressedFunc) {
		mousePressedFunc(args);
	}

	if (_isDraggable) {
		_dragOffset.x = _outerBox.x - args.x;
		_dragOffset.y = _outerBox.y - args.y;
	}
}

void ofxPComponent::mouseReleased(ofMouseEventArgs &args) {
	isMousePressed = false;
	if (mouseReleasedFunc) {
		mouseReleasedFunc(args);
	}
}

void ofxPComponent::mouseMoved(ofMouseEventArgs &args) {
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

	if (mouseMovedFunc) {
		mouseMovedFunc(args);
	}
}

void ofxPComponent::mouseOver(ofMouseEventArgs &args) {
	isMouseOver = true;
	if (mouseOverFunc) {
		mouseOverFunc(args);
	}
}

void ofxPComponent::mouseOut(ofMouseEventArgs &args) {
	isMouseOver = false;
	mouseReleasedWrapper(args); // in ofxParvenu, if you press a button, move your mouse out, then the button is considered released
	if (mouseOverFunc) {
		mouseOverFunc(args);
	}
}

void ofxPComponent::mouseDragged(ofMouseEventArgs &args) {
	if (!_isDraggable) {
		return;
	}

	isDragged = true;
	_outerBox.x = args.x + _dragOffset.x;
	_outerBox.y = args.y + _dragOffset.y;

	if (mouseDraggedFunc) {
		mouseDraggedFunc(args);
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