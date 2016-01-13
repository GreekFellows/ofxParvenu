#include "ofxPVContainerWindow.h"

// swap
void swap(ofxPVContainerWindow& lhs, ofxPVContainerWindow& rhs) {
	using std::swap;
}

void ofxPVContainerWindow::draw(bool debug) {
	ofPushStyle();

	ofSetColor(128, 64 * _fill.a / 255);
	ofFill();
	ofRect(ofRectangle(_outerBox.x, _outerBox.y + 5, _outerBox.width, _outerBox.height));
	ofSetColor(_fill);
	ofRect(_outerBox);
	ofSetColor(_stroke);
	ofNoFill();
	ofRect(_outerBox);

	ofPopStyle();

	ofPushMatrix();
	ofTranslate(_outerBox.x, _outerBox.y);
	ofSetColor(_fill.r * 0.8, _fill.g * 0.8, _fill.b * 0.8, 128);
	ofRect(0, 0, _outerBox.width, _wndTitleTextArea->_outerBox.height + _verticalPadding * 1.5);
	_wndTitleTextArea->draw(debug);
	ofPopMatrix();

	ofxPVContainer::draw(debug);
}

void ofxPVContainerWindow::calculateMinBox() {
	double maxwidth = _wndTitleTextArea->_outerBox.width, totheight = _verticalPadding * 2 + _wndTitleTextArea->_outerBox.height;
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

void ofxPVContainerWindow::setComponentPositions() {
	_wndTitleTextArea->_outerBox.x = (_outerBox.width - _wndTitleTextArea->_outerBox.width) / 2;
	_wndTitleTextArea->_outerBox.y = _verticalPadding;

	double y = (_padInsideOnly ? 0 : _verticalPadding) + _verticalPadding + _wndTitleTextArea->_outerBox.height;
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