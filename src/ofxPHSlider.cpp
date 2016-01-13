#include "ofxPHSlider.h"

// swap
void swap(ofxPHSlider& lhs, ofxPHSlider& rhs) {
	using std::swap;
	swap(lhs._stroke, rhs._stroke);
	swap(lhs._padding, rhs._padding);
}

void ofxPHSlider::draw(bool debug) {
	ofPushStyle();
	ofPushMatrix();

	ofTranslate(_outerBox.x, _outerBox.y);

	ofSetColor(_stroke * 0.5);
	ofSetLineWidth(2);
	ofLine(_padding, _outerBox.height / 2, _outerBox.width - _padding, _outerBox.height / 2);

	_btnSlider->draw(debug);

	ofPopMatrix();

	if (debug) {
		drawDebug();
	}

	if (_drawTag) {
		drawTag();
	}

	ofPopStyle();
}

void ofxPHSlider::calculateMinBox() {
	if (!_parvenuPtr) return;

	_btnSlider->_outerBox.width = _btnSlider->_minBox.width = std::max(_minDefaultWidth * 0.4, 40.0);
	_btnSlider->_outerBox.x = _padding + (_value - _minValue) / (_maxValue - _minValue) * (_outerBox.width - 2 * _padding - _btnSlider->_outerBox.width);
	_btnSlider->_outerBox.y = (_outerBox.height - _btnSlider->_outerBox.height) / 2;

	_minBox.x = _minBox.y = 0;
	_minBox.width = _minDefaultWidth + 2 * _padding;
	_minBox.height = _btnSlider->_outerBox.height;

	if (_outerBox.width < _minBox.width) {
		_outerBox.width = _minBox.width;
	}

	if (_outerBox.height < _minBox.height) {
		_outerBox.height = _minBox.height;
	}
}