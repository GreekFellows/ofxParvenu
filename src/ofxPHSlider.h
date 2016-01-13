#ifndef OFXPHSLIDER_H
#define OFXPHSLIDER_H

#define $getStrredValue (_useInt ? std::to_string((int)_value) : std::to_string(_value))

#include "ofMain.h"
#include "ofxPComponent.h"
#include "ofxPButton.h"

class ofxPHSlider;

void swap(ofxPHSlider&, ofxPHSlider&);

class ofxPHSlider :public ofxPComponent, public std::enable_shared_from_this<ofxPHSlider> {
	friend void swap(ofxPHSlider&, ofxPHSlider&);

public:
	// ctors, dtors and copy-control members
	ofxPHSlider() :ofxPComponent() {
		makeButtonSlider();
		calculateMinBox();
	}

	ofxPHSlider(ofxParvenu* cparvenuPtr) :ofxPComponent(cparvenuPtr) {
		makeButtonSlider();
		calculateMinBox();
	}

	ofxPHSlider(ofxParvenu* cparvenuPtr, const double& cmin, const double& cmax, const double& cval) :ofxPComponent(cparvenuPtr), _minValue(cmin), _maxValue(cmax), _value(cval) {
		makeButtonSlider();
		calculateMinBox();
	}

	ofxPHSlider(const ofxPHSlider& copy) :ofxPComponent(copy) {
		makeButtonSlider();
		calculateMinBox();
	}

	ofxPHSlider(ofxPHSlider&& rval) :ofxPComponent(rval) {
		makeButtonSlider();
		calculateMinBox();
	}

	ofxPHSlider& operator=(ofxPHSlider copy) {
		ofxPComponent::operator=(copy);
		swap(*this, copy);
		return *this;
	}

	virtual ~ofxPHSlider() {

	}

	// member functions
	virtual void draw(bool = false) override;
	virtual void calculateMinBox() override;

	virtual ofxPHSlider& setOuterBox(const ofRectangle& rect) override {
		_outerBox = rect;
		return *this;
	}

	// this is internally called, but
	void makeButtonSlider() {
		_btnSlider = std::make_shared<ofxPButton>(_parvenuPtr, $getStrredValue);
		_btnSlider->_isDraggable = true;
		_btnSlider->mouseDraggedFunc = [this](ofMouseEventArgs&){
			if (_btnSlider->_outerBox.x < _padding) {
				_btnSlider->_outerBox.x = _padding;
			}
			else if (_btnSlider->_outerBox.x > _outerBox.width - _padding - _btnSlider->_outerBox.width) {
				_btnSlider->_outerBox.x = _outerBox.width - _padding - _btnSlider->_outerBox.width;
			}
			_btnSlider->_outerBox.y = (_outerBox.height - _btnSlider->_outerBox.height) / 2;
			_value = _minValue + (_maxValue - _minValue) * (_btnSlider->_outerBox.x - _padding) / (_outerBox.width - _padding * 2 - _btnSlider->_outerBox.width);
			if ($getStrredValue != _btnSlider->_label) {
				_btnSlider->_label = $getStrredValue;
				_btnSlider->calculateMinBox();
				_btnSlider->fitOuterBoxToMinBox();
			}
		};
		_btnSlider->_labelVerticalPadding = 5;
		_btnSlider->calculateMinBox();
		_btnSlider->fitOuterBoxToMinBox();
	}

	// THIS MUST BE CALLED RIGHT AFTER THE std::shared_ptr<ofxPHSlider> IS CREATED OR THE BUTTON WOULD LOOK WEIRD
	void setupButtonSlider() {
		_btnSlider->_parent = shared_from_this();
		_nonContainerChildren.push_back(_btnSlider);
		_parvenuPtr->pushComponent(_btnSlider);
	}

	// overloaded operators
	virtual bool operator==(ofxPHSlider& rhs) const {
		return ofxPComponent::operator==(rhs) && (true);
	}

	virtual bool operator!=(ofxPHSlider& rhs) const {
		return !(*this == rhs);
	}

	// members
	ofColor _stroke = { 0 }, _labelColor = { 0 };

	bool _useInt = { true };
	double _minValue = { 0 }, _maxValue = { 1 }, _value = { 0.5 };
	double _minDefaultWidth = { 100 };
	double _padding = { 5 };
	std::shared_ptr<ofxPButton> _btnSlider;
};

#endif