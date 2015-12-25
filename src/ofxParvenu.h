#ifndef OFXPARVENU_H
#define OFXPARVENU_H

#include "ofMain.h"
#include "ofxPComponent.h"

extern class ofxPComponent;
class ofxParvenu;

class ofxParvenu {
public:
	// enumerations to specify font style
	enum class FontStyle {
		R, B, I, BI
	};

	// ctors, dtors and copy-control members
	ofxParvenu() {
		setup();
	}

	// copy constructor
	ofxParvenu(const ofxParvenu& copy) = delete;

	// move constructor
	ofxParvenu(ofxParvenu&& rval) = delete;

	// copy- / move-assignment operator with copy-and-swap
	ofxParvenu& operator=(ofxParvenu copy) = delete;

	// member functions
	void setup();
	void draw(bool = false);
	void drawText(const std::string&, const double&, const double&);

	void pushComponent(std::shared_ptr<ofxPComponent>);

	// event listeners and stuff
	void onMousePressed(ofMouseEventArgs&);
	void onMouseReleased(ofMouseEventArgs&);
	void onMouseMoved(ofMouseEventArgs&);
	void onMouseDragged(ofMouseEventArgs&);
	void setupEventListeners();

	// font stuff
	void loadFont();
	ofTrueTypeFont& getUsingFont(FontStyle = FontStyle::R);

	// members
	ofTrueTypeFont _aileronFont;
	ofTrueTypeFont _liberationSansRegularFont, _liberationSansBoldFont, _liberationSansItalicFont, _liberationSansBoldItalicFont;
	std::vector<std::shared_ptr<ofxPComponent>> _comps;

	ofColor _textColor = { 0 };
};

#endif