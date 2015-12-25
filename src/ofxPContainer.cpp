#include "ofxPContainer.h"
#include "ofxPVContainer.h"
#include "ofxPHContainer.h"

const double ofxPContainer::__separatorFactor = 0.3;

// swap
void swap(ofxPContainer& lhs, ofxPContainer& rhs) {
	using std::swap;
	swap(lhs._children, rhs._children);
}

void ofxPContainer::setComponentPositions() {

}

// the pointer comp is also pushed to _parvenuPtr
// this is the general pushComponent() function
// no separator is drawn by default
void ofxPContainer::pushComponent(std::shared_ptr<ofxPComponent> comp, ContentAlignment chora, ContentAlignment cvera, bool cdsep) {
	if (!_parvenuPtr) return;

	if (dynamic_cast<ofxPVContainer*>(comp.get())) {
		std::dynamic_pointer_cast<ofxPVContainer>(comp)->_padInsideOnly = true;
	}
	else if (dynamic_cast<ofxPHContainer*>(comp.get())) {
		std::dynamic_pointer_cast<ofxPHContainer>(comp)->_padInsideOnly = true;
	}

	comp->_parent = shared_from_this();
	_children.push_back(comp);
	_parvenuPtr->pushComponent(comp);

	_alignments.push_back(std::make_pair(chora, cvera));
	_drawSeparators.push_back(cdsep);
}

void ofxPContainer::pushComponent(std::shared_ptr<ofxPComponent> comp, ContentAlignment chora, ContentAlignment cvera) {
	pushComponent(comp, chora, cvera, false);
}

void ofxPContainer::pushComponent(std::shared_ptr<ofxPComponent> comp, bool cdsep) {
	pushComponent(comp, ContentAlignment::HC, ContentAlignment::VM, cdsep);
}

void ofxPContainer::pushComponent(std::shared_ptr<ofxPComponent> comp) {
	pushComponent(comp, ContentAlignment::HC, ContentAlignment::VM, false);
}

void ofxPContainer::mousePressed(ofMouseEventArgs& args) {
	_childIsMousePressed = false;
	for (auto ptr = _children.rbegin(), end = _children.rend(); ptr != end; ++ptr) {
		ofRectangle rect = (*ptr)->getGlobalOuterBox();
		if (rect.inside(args.x, args.y)) {
			(*ptr)->mousePressed(args);
			_childIsMousePressed = true;
			break;
		}
	}

	ofxPComponent::mousePressed(args);
}

void ofxPContainer::mouseReleased(ofMouseEventArgs& args) {
	for (auto ptr : _children) {
		ptr->mouseReleasedWrapper(args);
	}

	ofxPComponent::mouseReleased(args);
	_childIsMousePressed = false;
}

void ofxPContainer::mouseMoved(ofMouseEventArgs& args) {
	for (auto ptr : _children) {
		ptr->mouseMoved(args);
	}

	ofxPComponent::mouseMoved(args);
}

void ofxPContainer::mouseDragged(ofMouseEventArgs &args) {
	if (_childIsMousePressed && _noDragIfChildPressed) {
		return;
	}

	ofxPComponent::mouseDragged(args);
}