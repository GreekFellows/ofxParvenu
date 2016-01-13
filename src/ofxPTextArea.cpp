#include "ofxPTextArea.h"

// swap
void swap(ofxPTextArea& lhs, ofxPTextArea& rhs) {
	using std::swap;
	swap(lhs._text, rhs._text);
	swap(lhs._textBoundingBox, rhs._textBoundingBox);
	swap(lhs._textPadding, rhs._textPadding);
}

void ofxPTextArea::draw(bool debug) {
	ofPushStyle();
	ofPushMatrix();

	ofTranslate(_outerBox.x, _outerBox.y);

	ofSetColor(0);
	ofFill();
	_parvenuPtr->getUsingFont(_fontStyle).drawString(_text, _textPadding, _parvenuPtr->getUsingFont().getLineHeight() + _textPadding);

	ofPopMatrix();

	if (debug) {
		drawDebug();
	}

	if (_drawTag) {
		drawTag();
	}

	ofPopStyle();
}

void ofxPTextArea::calculateMinBox() {
	if (!_parvenuPtr) return;

	// if it's multiline text, we need to know the width of the line of text with the maximum width
	if (_text.find('\n') < _text.size()) {
		std::istringstream iss(_text);
		double maxwidth = 0;
		int numlines = 0;

		std::string str;
		while (std::getline(iss, str)) {
			double width = _parvenuPtr->getUsingFont(_fontStyle).getStringBoundingBox(str, 0, 0).width;
			if (maxwidth < width) {
				maxwidth = width;
			}
			++numlines;
		}

		_minBox.width = maxwidth + 2 * _textPadding;
		_minBox.height = _parvenuPtr->getUsingFont(_fontStyle).getLineHeight() * numlines + 2 * _textPadding;
	}
	else {
		_minBox.width = _parvenuPtr->getUsingFont(_fontStyle).getStringBoundingBox(_text, 0, 0).width + 2 * _textPadding;
		_minBox.height = _parvenuPtr->getUsingFont(_fontStyle).getLineHeight() + 2 * _textPadding;
	}

	_minBox.x = _minBox.y = 0;

	if (_outerBox.width < _minBox.width) {
		_outerBox.width = _minBox.width;
	}

	if (_outerBox.height < _minBox.height) {
		_outerBox.height = _minBox.height;
	}
}