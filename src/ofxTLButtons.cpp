/**
 * ofxTimeline
 * openFrameworks graphical timeline addon
 *
 * Copyright (c) 2011-2012 James George
 * Development Supported by YCAM InterLab http://interlab.ycam.jp/en/
 * http://jamesgeorge.org + http://flightphase.com
 * http://github.com/obviousjim + http://github.com/flightphase
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "ofxTLButtons.h"
#include "ofxTimeline.h"

ofxTLButtons::ofxTLButtons(){
    //Set up track GUI
    //trackGui = new ofxUICanvas(0,bounds.getMinY(),ofGetWidth(), 90);
    trackGui = new ofxUICanvas(0,0,200,200);
    //ofxUILabelButton* testButton = new ofxUILabelButton("cacca", false,0,0,0,0, OFX_UI_FONT_SMALL);
    ofxUIButton* testButton1 = new ofxUIButton("cacca", false,20,20,0,0);
    testButton1->setPadding(0);
    testButton1->setLabelVisible(false);
    trackGui->addWidgetRight(testButton1);
    ofxUITextInput* testInput1 = new ofxUITextInput("cacca_label", "/osc/cacca", 120, 20, 0, 0, OFX_UI_FONT_SMALL);
    trackGui->addWidgetRight(testInput1);
    ofxUIButton* testButton2 = new ofxUIButton("culo", false,20,20,0,0);
    testButton2->setPadding(0);
    testButton2->setLabelVisible(false);
    trackGui->addWidgetDown(testButton2);
    ofxUITextInput* testInput2 = new ofxUITextInput("culo_label", "/osc/culo", 120, 20, 0, 0, OFX_UI_FONT_SMALL);
    trackGui->addWidgetRight(testInput2);
    ofxUIButton* testButton3 = new ofxUIButton("merda", false,20,20,0,0);
    testButton3->setPadding(0);
    testButton3->setLabelVisible(false);
    trackGui->addWidgetRight(testButton3);
    ofxUITextInput* testInput3 = new ofxUITextInput("merda_label", "/osc/merda", 120, 20, 0, 0, OFX_UI_FONT_SMALL);
    trackGui->addWidgetRight(testInput3);
}

ofxTLButtons::~ofxTLButtons(){

}

//enable and disable are always automatically called
//in setup. Must call superclass's method as well as doing your own
//enabling and disabling
void ofxTLButtons::enable(){
	ofxTLTrack::enable();
	trackGui->enable();

	//other enabling
}

void ofxTLButtons::disable(){
	ofxTLTrack::disable();
    trackGui->disable();
	//other disabling
}

//update is called every frame.
//if your track triggers events it's good to do it here
//if timeline is set to thread this is called on the back thread so
//be careful if loading images in herre
void ofxTLButtons::update(){
    trackGui->getRect()->width = bounds.width;
    trackGui->getRect()->height = bounds.height;
    trackGui->getRect()->y = bounds.getMinY();
}

//draw your track contents. use ofRectangle bounds to know where to draw
//and the Track functions screenXToMillis() or millisToScreenX() to respect zoom
void ofxTLButtons::draw(){

    trackGui->draw();

	//this is just a simple example
	ofPushStyle();
	ofFill();
	if(isHovering()){
		ofSetColor(timeline->getColors().backgroundColor);
		ofRect(bounds);
	}

	ofNoFill();
	ofSetColor(timeline->getColors().keyColor);
	for(int i = 0; i < clickPoints.size(); i++){
		float screenX = millisToScreenX(clickPoints[i].time);
		if(screenX > bounds.x && screenX < bounds.x+bounds.width){
			float screenY = ofMap(clickPoints[i].value, 0.0, 1.0, bounds.getMinY(), bounds.getMaxY());
			ofCircle(screenX, screenY, 4);
		}
	}
}

//caled by the timeline, don't need to register events
bool ofxTLButtons::mousePressed(ofMouseEventArgs& args, long millis){
	/*
	createNewPoint = isActive();
	clickPoint = ofVec2f(args.x,args.y);
	return createNewPoint; //signals that the click made a selection
	*/
}

void ofxTLButtons::mouseMoved(ofMouseEventArgs& args, long millis){

}
void ofxTLButtons::mouseDragged(ofMouseEventArgs& args, long millis){

}
void ofxTLButtons::mouseReleased(ofMouseEventArgs& args, long millis){

	/*
	//need to create clicks on mouse up if the mouse hasn't moved in order to work
	//well with the click-drag rectangle thing
	if(createNewPoint && clickPoint.distance(ofVec2f(args.x, args.y)) < 4){
		ClickPoint newpoint;
		newpoint.value = ofMap(args.y, bounds.getMinY(), bounds.getMaxY(), 0, 1.0);
		newpoint.time = millis;
		clickPoints.push_back(newpoint);
		//call this on mouseup or keypressed after a click
		//will trigger save and needed for undo
		timeline->flagTrackModified(this);
	}
	*/
}

//keys pressed events, and nuding from arrow keys with normalized nudge amount 0 - 1.0
void ofxTLButtons::keyPressed(ofKeyEventArgs& args){

}
void ofxTLButtons::nudgeBy(ofVec2f nudgePercent){

}

//if your track has some selectable elements you can interface with snapping
//and selection/unselection here
void ofxTLButtons::getSnappingPoints(set<unsigned long>& points){

}
void ofxTLButtons::regionSelected(ofLongRange timeRange, ofRange valueRange){

}
void ofxTLButtons::unselectAll(){

}
void ofxTLButtons::selectAll(){

}

//return a unique name for your track
string ofxTLButtons::getTrackType(){
	return "EmptyTrack";
}

//for copy+paste you can optionaly implement ways
//of creating XML strings that represent your selected tracks
string ofxTLButtons::copyRequest(){
	return "";
}

string ofxTLButtons::cutRequest(){
	return "";
}

//will return the same type of strings you provide in copy and paste
//but may contain foreign data from other tracks so be careful
void ofxTLButtons::pasteSent(string pasteboard){

}

//for undo and redo you can implement a way of
//reperesnt your whole track as XML
string ofxTLButtons::getXMLRepresentation(){
	return "";
}

void ofxTLButtons::loadFromXMLRepresentation(string rep){

}

//serialize your track.
//use ofxTLTrack's string xmlFileName
void ofxTLButtons::save(){

}

void ofxTLButtons::load(){

}

void ofxTLButtons::clear(){

}
