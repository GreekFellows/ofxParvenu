#include "ofxParvenu.h"

void ofxParvenu::setup() {
	loadFont();
	setupEventListeners();
}

void ofxParvenu::draw(bool debug) {
	for (auto &ptr : _comps) {
		// if this component had a parent then we don't need to draw it here
		if (!ptr->_parent) {
			ptr->draw(debug);
		}
	}
	
	deleter();
}

// deletes all that wishes to be deleted.
// _deleteMe of children of a to-be-deleted is also set to true; they are left for their own parents to delete them.
void ofxParvenu::deleter() {
	_comps.erase(std::remove_if(_comps.begin(), _comps.end(), [](std::shared_ptr<ofxPComponent> comp){
		std::shared_ptr<ofxPComponent> ccomp = comp;
		while (ccomp) {
			if (ccomp->_deleteMe) {
				comp->_deleteMe = true;
				return true;
			}
			else {
				ccomp = ccomp->_parent;
			}
		}

		return false;
	}), _comps.end());
}

void ofxParvenu::drawText(const std::string &str, const double &x, const double &y) {
	getUsingFont().drawString(str, x, y);
}

void ofxParvenu::drawFPS() {
	ofPushStyle();
	ofSetColor(0);
	ofDrawBitmapString(std::to_string(ofGetFrameRate()), 10, 16);
	ofSetColor(128);
	ofRect(10, 20, 130, 30);
	ofSetColor(0);
	ofRect(10, 20, 10 + ofGetFrameRate() * 2, 30);
	ofPopStyle();
}

void ofxParvenu::pushComponent(const std::shared_ptr<ofxPComponent>& comp) {
	_comps.push_back(comp);
}

void ofxParvenu::onMousePressed(ofMouseEventArgs& args) {
	for (auto ptr = _comps.rbegin(), end = _comps.rend(); ptr != end; ++ptr) {
		ofRectangle rect = (*ptr)->getGlobalOuterBox();
		if (rect.inside(args.x, args.y)) {
			(*ptr)->mousePressed(args);
			break;
		}
	}
}

void ofxParvenu::onMouseReleased(ofMouseEventArgs& args) {
	for (auto ptr : _comps) {
		ptr->mouseReleasedWrapper(args);
	}
}

void ofxParvenu::onMouseMoved(ofMouseEventArgs& args) {
	for (auto ptr : _comps) {
		ptr->mouseMoved(args);
	}
}

void ofxParvenu::onMouseDragged(ofMouseEventArgs& args) {
	for (auto ptr : _comps) {
		for (auto ptr = _comps.rbegin(), end = _comps.rend(); ptr != end; ++ptr) {
			if ((*ptr)->isMousePressed) {
				(*ptr)->mouseDragged(args);
				break;
			}
		}
	}
}

void ofxParvenu::setupEventListeners() {
	ofAddListener(ofEvents().mousePressed, this, &ofxParvenu::onMousePressed);
	ofAddListener(ofEvents().mouseReleased, this, &ofxParvenu::onMouseReleased);
	ofAddListener(ofEvents().mouseMoved, this, &ofxParvenu::onMouseMoved);
	ofAddListener(ofEvents().mouseDragged, this, &ofxParvenu::onMouseDragged);
}

void ofxParvenu::loadFont() {
	// TrimImage();

	_aileronFont.loadFont("Aileron-Regular.otf", 12, true, false, false);
	_liberationSansRegularFont.loadFont("LiberationSans-Regular.ttf", 12, true, false, false, 0.3, 90);
	_liberationSansBoldFont.loadFont("LiberationSans-Bold.ttf", 12, true, false, false, 0.3, 90);
	_liberationSansItalicFont.loadFont("LiberationSans-Italic.ttf", 12, true, false, false, 0.3, 90);
	_liberationSansBoldItalicFont.loadFont("LiberationSans-BoldItalic.ttf", 12, true, false, false, 0.3, 90);

	_aileronFont.setSpaceSize(0.6);
	_liberationSansRegularFont.setSpaceSize(0.6);
	_liberationSansBoldFont.setSpaceSize(0.6);
	_liberationSansItalicFont.setSpaceSize(0.6);
	_liberationSansBoldItalicFont.setSpaceSize(0.6);
}

ofTrueTypeFont& ofxParvenu::getUsingFont(FontStyle fs) {
	if (fs == FontStyle::R) {
		return _liberationSansRegularFont;
	}
	else if (fs == FontStyle::B) {
		return _liberationSansBoldFont;
	}
	else if (fs == FontStyle::I) {
		return _liberationSansItalicFont;
	}
	else if (fs == FontStyle::BI) {
		return _liberationSansBoldItalicFont;
	}

	return _liberationSansRegularFont;
	// return _aileronFont;
}