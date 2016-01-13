#include "ofxPHContainer.h"

// swap
void swap(ofxPHContainer& lhs, ofxPHContainer& rhs) {
	using std::swap;
	swap(lhs._horizontalPadding, rhs._horizontalPadding);
	swap(lhs._verticalPadding, rhs._verticalPadding);
	swap(lhs._padInsideOnly, rhs._padInsideOnly);
}

void ofxPHContainer::draw(bool debug) {
	ofPushStyle();
	ofPushMatrix();

	ofTranslate(_outerBox.x, _outerBox.y);

	int sepCount = 0, maxCount = _drawSeparators.size() - 1;
	for (auto ptr : _children) {
		ptr->draw(debug);

		if (sepCount < maxCount) {
			if (_drawSeparators[sepCount]) {
				ofPushStyle();
				ofSetColor(_separatorStroke);
				ofLine(
					ptr->_outerBox.x + ptr->_outerBox.width + _horizontalPadding / 2.0,
					_outerBox.height * (0.5 - __separatorFactor),
					ptr->_outerBox.x + ptr->_outerBox.width + _horizontalPadding / 2.0,
					_outerBox.height * (0.5 + __separatorFactor)
					);
				ofPopStyle();
			}
		}

		++sepCount;
	}

	ofPopMatrix();

	if (debug) {
		drawDebug();
	}

	if (_drawTag) {
		drawTag();
	}

	ofPopStyle();

	ofxPContainer::deleter();
}

void ofxPHContainer::calculateMinBox() {
	// double maxwidth = 0, totheight = _verticalPadding;
	double maxheight = 0, totwidth = _horizontalPadding;
	for (auto ptr : _children) {
		ptr->calculateMinBox();
		ptr->fitOuterBoxToMinBox();
		// totheight += ptr->_minBox.height;
		totwidth += ptr->_minBox.width;
		// totheight += _verticalPadding;
		totwidth += _horizontalPadding;

		// maxwidth = (maxwidth < ptr->_minBox.width) ? ptr->_minBox.width : maxwidth;
		maxheight = (maxheight < ptr->_minBox.height) ? ptr->_minBox.height : maxheight;
	}

	// _minBox.width = maxwidth + (_padInsideOnly ? 0 : 2 * _horizontalPadding);
	// _minBox.height = totheight + (_padInsideOnly ? -2 * _verticalPadding : 0);
	_minBox.height = maxheight + (_padInsideOnly ? 0 : 2 * _verticalPadding);
	_minBox.width = totwidth + (_padInsideOnly ? -2 * _horizontalPadding : 0);

	if (_outerBox.width < _minBox.width) {
		_outerBox.width = _minBox.width;
	}

	if (_outerBox.height < _minBox.height) {
		_outerBox.height = _minBox.height;
	}
}

void ofxPHContainer::setComponentPositions() {
	// double y = (_padInsideOnly ? 0 : _verticalPadding);
	double x = (_padInsideOnly ? 0 : _horizontalPadding);
	auto alignpair = _alignments.begin();
	for (auto ptr : _children) {
		// http://stackoverflow.com/questions/6805026
		// so let's use switch!
		/*switch ((*alignpair).first) {
		case ContentAlignment::HL:
			ptr->_outerBox.x = (_padInsideOnly ? 0 : _horizontalPadding);
			break;

		case ContentAlignment::HC:
			ptr->_outerBox.x = (_outerBox.width - ptr->_outerBox.width) / 2;
			break;

		case ContentAlignment::HR:
			ptr->_outerBox.x = _outerBox.width - ptr->_outerBox.width + (_padInsideOnly ? 0 : -_horizontalPadding);
			break;
		}*/

		switch ((*alignpair).second) {
		case ContentAlignment::VT:
			ptr->_outerBox.y = (_padInsideOnly ? 0 : _verticalPadding);
			break;

		case ContentAlignment::VM:
			ptr->_outerBox.y = (_outerBox.height - ptr->_outerBox.height) / 2;
			break;

		case ContentAlignment::VB:
			ptr->_outerBox.y = _outerBox.height - ptr->_outerBox.height + (_padInsideOnly ? 0 : -_verticalPadding);
			break;
		}

		// so far the vertical alignment is not working
		// but we will have a vector of ofRectangles that holds information for space allocated for each component
		// ptr->_outerBox.y = y;

		ptr->_outerBox.x = x;

		// y += ptr->_outerBox.height;
		// y += _verticalPadding;
		x += ptr->_outerBox.width;
		x += _horizontalPadding;

		++alignpair;
	}
}