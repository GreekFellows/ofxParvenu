#include "ofxPVContainer.h"

// swap
void swap(ofxPVContainer& lhs, ofxPVContainer& rhs) {
	using std::swap;
	swap(lhs._horizontalPadding, rhs._horizontalPadding);
	swap(lhs._verticalPadding, rhs._verticalPadding);
	swap(lhs._padInsideOnly, rhs._padInsideOnly);
}

void ofxPVContainer::draw(bool debug) {
	ofPushStyle();
	ofPushMatrix();

	if (debug) {
		drawDebug();
	}

	if (_drawTag) {
		drawTag();
	}

	ofTranslate(_outerBox.x, _outerBox.y);

	int sepCount = 0, maxCount = _drawSeparators.size() - 1;
	for (auto ptr : _children) {
		ptr->draw(debug);

		if (sepCount < maxCount) {
			if (_drawSeparators[sepCount]) {
				ofPushStyle();
				ofSetColor(_separatorStroke);
				ofLine(_outerBox.width * (0.5 - __separatorFactor), ptr->_outerBox.y + ptr->_outerBox.height + _verticalPadding / 2.0, _outerBox.width * (0.5 + __separatorFactor), ptr->_outerBox.y + ptr->_outerBox.height + _verticalPadding / 2.0);
				ofPopStyle();
			}
		}

		++sepCount;
	}

	ofPopMatrix();
	ofPopStyle();
}

void ofxPVContainer::calculateMinBox() {
	double maxwidth = 0, totheight = _verticalPadding;
	for (auto ptr : _children) {
		ptr->calculateMinBox();
		ptr->fitOuterBoxToMinBox();
		totheight += ptr->_minBox.height;
		totheight += _verticalPadding;

		maxwidth = (maxwidth < ptr->_minBox.width) ? ptr->_minBox.width : maxwidth;
	}

	_minBox.width = maxwidth + (_padInsideOnly ? 0 : 2 * _horizontalPadding);
	_minBox.height = totheight + (_padInsideOnly ? -2 * _verticalPadding : 0);

	if (_outerBox.width < _minBox.width) {
		_outerBox.width = _minBox.width;
	}

	if (_outerBox.height < _minBox.height) {
		_outerBox.height = _minBox.height;
	}
}

void ofxPVContainer::setComponentPositions() {
	double y = (_padInsideOnly ? 0 : _verticalPadding);
	auto alignpair = _alignments.begin();
	for (auto ptr : _children) {
		// http://stackoverflow.com/questions/6805026
		// so let's use switch!
		switch ((*alignpair).first) {
		case ContentAlignment::HL:
			ptr->_outerBox.x = (_padInsideOnly ? 0 : _horizontalPadding);
			break;

		case ContentAlignment::HC:
			ptr->_outerBox.x = (_outerBox.width - ptr->_outerBox.width) / 2;
			break;

		case ContentAlignment::HR:
			ptr->_outerBox.x = _outerBox.width - ptr->_outerBox.width + (_padInsideOnly ? 0 : -_horizontalPadding);
			break;
		}

		// so far the vertical alignment is not working
		// but we will have a vector of ofRectangles that holds information for space allocated for each component
		ptr->_outerBox.y = y;

		y += ptr->_outerBox.height;
		y += _verticalPadding;

		++alignpair;
	}
}