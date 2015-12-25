#include "ofxPButton.h"

// swap
void swap(ofxPButton& lhs, ofxPButton& rhs) {
	using std::swap;
	swap(lhs._label, rhs._label);
	swap(lhs._labelBoundingBox, rhs._labelBoundingBox);
	swap(lhs._fill, rhs._fill);
	swap(lhs._stroke, rhs._stroke);
	swap(lhs._labelPadding, rhs._labelPadding);
}

void ofxPButton::draw(bool debug) {
	ofPushStyle();
	ofPushMatrix();

	if (debug) {
		drawDebug();
	}

	if (_drawTag) {
		drawTag();
	}

	ofTranslate(_outerBox.x, _outerBox.y);

	ofSetColor(128, 64);
	ofFill();
	ofRect(ofRectangle(0, 5, _outerBox.width, _outerBox.height));

	if (!isMousePressed) {
		if (!isMouseOver) {
			ofSetColor(_fill);
		}
		else {
			ofSetColor(_fill * 0.75 + ofColor(255) * 0.25);
		}
	}
	else {
		ofSetColor(_fill * 0.5);
	}
	ofRect(0, isMousePressed ? 2.5 : 0, _outerBox.width, _outerBox.height);

	ofSetColor(_stroke);
	ofNoFill();
	ofRect(0, isMousePressed ? 2.5 : 0, _outerBox.width, _outerBox.height);

	ofSetColor(_labelColor);
	ofFill();
	_parvenuPtr->getUsingFont(_fontStyle).drawString(_label, (_outerBox.width - _labelBoundingBox.width) / 2, (isMousePressed ? 2.5 : 0) + _outerBox.height / 2 + _labelBoundingBox.height / 2);

	ofPopMatrix();
	ofPopStyle();
}

void ofxPButton::calculateMinBox() {
	if (!_parvenuPtr) return;

	_labelBoundingBox = _parvenuPtr->getUsingFont(_fontStyle).getStringBoundingBox(_label, 0, 0);

	_minBox.x = _minBox.y = 0;
	_minBox.width = _labelBoundingBox.width + 2 * _labelPadding;
	_minBox.height = _labelBoundingBox.height + 2 * _labelPadding;

	if (_outerBox.width < _minBox.width) {
		_outerBox.width = _minBox.width;
	}

	if (_outerBox.height < _minBox.height) {
		_outerBox.height = _minBox.height;
	}
}