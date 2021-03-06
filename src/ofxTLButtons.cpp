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

    rows = 3;
    cols = 4;
    oscTarget = "localhost";
    oscPort = 12345;
    type = OFXTLBUTTONS_TYPE_BUTTONS;
    setupTrack();

}


ofxTLButtons::ofxTLButtons(int _rows, int _cols, string _oscTarget = "localhost", int _oscPort = 12345, ofxTLButtonsType _type=OFXTLBUTTONS_TYPE_BUTTONS){

    rows = _rows;
    cols = _cols;
    oscTarget = _oscTarget;
    oscPort = _oscPort;
    type = _type;
    setupTrack();

}

ofxTLButtons::ofxTLButtons(int _b_rows, int _b_cols, int _s_rows, int _s_cols, string _oscTarget = "localhost", int _oscPort = 12345, ofxTLButtonsType _type=OFXTLBUTTONS_TYPE_MIXED){

    button_rows = _b_rows;
    button_cols = _b_cols;
    slider_rows = _s_rows;
    slider_cols = _s_cols;
    oscTarget = _oscTarget;
    oscPort = _oscPort;
    type = _type;
    setupTrack();

}

ofxTLButtons::~ofxTLButtons(){
    delete trackGui;
}



void ofxTLButtons::setupTrack(){

    // OSC setup
    sender.setup(oscTarget, oscPort);


    //Set up track GUI
    //trackGui = new ofxUICanvas(0,bounds.getMinY(),ofGetWidth(), 90);
    trackGui = new ofxUICanvas(0,0,200,200);
    trackGui->setWidgetSpacing(10.0);
    //ofxUILabelButton* testButton = new ofxUILabelButton("cacca", false,0,0,0,0, OFX_UI_FONT_SMALL);
    ofxUITextInput* trackOscTarget = new ofxUITextInput("osc target", oscTarget, 120, 20, 0, 0, OFX_UI_FONT_SMALL);
    trackGui->addWidgetRight(trackOscTarget);
    ofxUILabel* trackOscTargetLabel = new ofxUILabel(0,0,"osc out IP",OFX_UI_FONT_SMALL);
    trackGui->setWidgetSpacing(5.0);
    trackGui->addWidgetDown(trackOscTargetLabel);
    ofxUITextInput* trackOscPort = new ofxUITextInput("osc port", ofToString(oscPort), 120, 20, 0, 0, OFX_UI_FONT_SMALL);
    trackGui->setWidgetSpacing(10.0);
    trackGui->addWidgetDown(trackOscPort);
    ofxUILabel* trackOscPortLabel = new ofxUILabel(0,0,"osc out port",OFX_UI_FONT_SMALL);
    trackGui->setWidgetSpacing(5.0);
    trackGui->addWidgetDown(trackOscPortLabel);
    trackGui->setWidgetSpacing(10.0);

    if(type == OFXTLBUTTONS_TYPE_BUTTONS){
        // building a matrix of buttons with corresponding editable message
        for(int i=0; i<rows; i++){
            for(int j=0; j<cols; j++){
                int number = (i*cols)+(j+1);
                string id = ofToString(number);
                ofxUIButton* Button = new ofxUIButton(id, false,20,20,0,0);
                Button->setPadding(0);
                Button->setLabelVisible(false);
                ofxUITextInput* testInput = new ofxUITextInput(id+"_label", "/mybutton/"+ofToString(number), 120, 20, 0, 0, OFX_UI_FONT_SMALL);
                if (number == 1){
                    trackGui->addWidgetEastOf(Button, "osc target");
                    trackGui->setWidgetSpacing(2.0);
                    trackGui->addWidgetRight(testInput);
                    trackGui->setWidgetSpacing(10.0);
                }
                else if (j==0 && number > 1){
                    trackGui->addWidgetSouthOf(Button, ofToString(number-cols));
                    trackGui->setWidgetSpacing(2.0);
                    trackGui->addWidgetRight(testInput);
                    trackGui->setWidgetSpacing(10.0);
                }
                else {
                    trackGui->addWidgetRight(Button);
                    trackGui->setWidgetSpacing(2.0);
                    trackGui->addWidgetRight(testInput);
                    trackGui->setWidgetSpacing(10.0);
                }
            }
        }
    }

    else if(type == OFXTLBUTTONS_TYPE_SLIDERS){
        // building a matrix of buttons with corresponding editable message
        for(int i=0; i<rows; i++){
            for(int j=0; j<cols; j++){
                int number = (i*cols)+(j+1);
                string id = ofToString(number);
                ofxUISlider* Slider = new ofxUISlider(id, 0.0, 1.0, 0.0, 120,15,0,0);
                Slider->setPadding(0);
                Slider->setLabelVisible(false);
                ofxUITextInput* testInput = new ofxUITextInput(id+"_label", "/myslider/"+ofToString(number), 120, 20, 0, 0, OFX_UI_FONT_SMALL);
                if (number == 1){
                    trackGui->addWidgetEastOf(Slider, "osc target");
                    trackGui->setWidgetSpacing(0.0);
                    trackGui->addWidgetSouthOf(testInput, ofToString(number));
                    trackGui->setWidgetSpacing(10.0);
                }
                else if (j==0 && number > 1){
                    trackGui->addWidgetSouthOf(Slider, ofToString(number-cols)+"_label");
                    trackGui->setWidgetSpacing(0.0);
                    trackGui->addWidgetSouthOf(testInput, ofToString(number));
                    trackGui->setWidgetSpacing(10.0);
                }
                else {
                    trackGui->addWidgetEastOf(Slider, ofToString(number-1));
                    trackGui->setWidgetSpacing(0.0);
                    trackGui->addWidgetSouthOf(testInput, ofToString(number));
                    trackGui->setWidgetSpacing(10.0);
                }
            }
        }
    }
    else if(type == OFXTLBUTTONS_TYPE_MIXED){
        // building a matrix of buttons with corresponding editable message
        int number = 0;
        for(int i=0; i<button_rows; i++){
            for(int j=0; j<button_cols; j++){
                number++;
                string id = ofToString(number);
                ofxUIButton* Button = new ofxUIButton(id, false,20,20,0,0);
                Button->setPadding(0);
                Button->setLabelVisible(false);
                ofxUITextInput* testInput = new ofxUITextInput(id+"_label", "/mybutton/"+ofToString(number), 120, 20, 0, 0, OFX_UI_FONT_SMALL);
                if (number == 1){
                    trackGui->addWidgetEastOf(Button, "osc target");
                    trackGui->setWidgetSpacing(2.0);
                    trackGui->addWidgetRight(testInput);
                    trackGui->setWidgetSpacing(10.0);
                }
                else if (j==0 && number > 1){
                    trackGui->addWidgetSouthOf(Button, ofToString(number-button_cols));
                    trackGui->setWidgetSpacing(2.0);
                    trackGui->addWidgetRight(testInput);
                    trackGui->setWidgetSpacing(10.0);
                }
                else {
                    trackGui->addWidgetRight(Button);
                    trackGui->setWidgetSpacing(2.0);
                    trackGui->addWidgetRight(testInput);
                    trackGui->setWidgetSpacing(10.0);
                }
            }
        }
        for(int i=0; i<slider_rows; i++){
            for(int j=0; j<slider_cols; j++){
                number++;
                string id = ofToString(number);
                ofxUISlider* Slider = new ofxUISlider(id, 0.0, 1.0, 0.0, 120,15,0,0);
                Slider->setPadding(0);
                Slider->setLabelVisible(false);
                ofxUITextInput* testInput = new ofxUITextInput(id+"_label", "/myslider/"+ofToString(number), 120, 20, 0, 0, OFX_UI_FONT_SMALL);
                if (number == (button_cols*button_rows)+1){
                    trackGui->addWidgetEastOf(Slider, ofToString(button_cols)+"_label");
                    trackGui->setWidgetSpacing(0.0);
                    trackGui->addWidgetSouthOf(testInput, ofToString(number));
                    trackGui->setWidgetSpacing(5.0);
                }
                else if (j==0 && number > (button_cols*button_rows)+1){
                    trackGui->addWidgetSouthOf(Slider, ofToString(number-slider_cols)+"_label");
                    trackGui->setWidgetSpacing(0.0);
                    trackGui->addWidgetSouthOf(testInput, ofToString(number));
                    trackGui->setWidgetSpacing(5.0);
                }
                else {
                    trackGui->addWidgetEastOf(Slider, ofToString(number-1));
                    trackGui->setWidgetSpacing(0.0);
                    trackGui->addWidgetSouthOf(testInput, ofToString(number));
                    trackGui->setWidgetSpacing(5.0);
                }
            }
        }

    }


    ofAddListener(trackGui->newGUIEvent, this, &ofxTLButtons::trackGuiEvent);


}


void ofxTLButtons::trackGuiEvent(ofxUIEventArgs& e){

    if(type == OFXTLBUTTONS_TYPE_BUTTONS){
        if(e.widget->getKind() == OFX_UI_WIDGET_BUTTON){
            ofxUIButton *button = (ofxUIButton *) e.widget;
            if(button->getValue() == 0){
                ofxUITextInput *label = (ofxUITextInput *) trackGui->getWidget(e.widget->getName()+"_label");
                string labelString = label->getTextString();
                cout << labelString << endl;
                sendOscMessage(labelString);
            }
        }

        /*
        else if(e.widget->getName() == "osc target" || e.widget->getName() == "osc port" ) {
            ofxUITextInput *textinput = (ofxUITextInput *) e.widget;
            cout << textinput->getTriggerType() << endl;
        }
        */
    }

    else if(type == OFXTLBUTTONS_TYPE_SLIDERS){
        if(e.widget->getKind() == OFX_UI_WIDGET_SLIDER_H){
            ofxUISlider *slider = (ofxUISlider *) e.widget;
            ofxUITextInput *label = (ofxUITextInput *) trackGui->getWidget(e.widget->getName()+"_label");
            string labelString = label->getTextString();
            float oscValue = slider->getScaledValue();
            cout << labelString << " " << "- value:" << oscValue << endl;
            sendOscMessage(labelString, oscValue);

        }

        /*
        else if(e.widget->getName() == "osc target" || e.widget->getName() == "osc port" ) {
            ofxUITextInput *textinput = (ofxUITextInput *) e.widget;
            cout << textinput->getTriggerType() << endl;
        }
        */
    }
    else if(type == OFXTLBUTTONS_TYPE_MIXED){
        if(e.widget->getKind() == OFX_UI_WIDGET_SLIDER_H){
            ofxUISlider *slider = (ofxUISlider *) e.widget;
            ofxUITextInput *label = (ofxUITextInput *) trackGui->getWidget(e.widget->getName()+"_label");
            string labelString = label->getTextString();
            float oscValue = slider->getScaledValue();
            cout << labelString << " " << "- value:" << oscValue << endl;
            sendOscMessage(labelString, oscValue);

        }
        else if(e.widget->getKind() == OFX_UI_WIDGET_BUTTON){
            ofxUIButton *button = (ofxUIButton *) e.widget;
            if(button->getValue() == 0){
                ofxUITextInput *label = (ofxUITextInput *) trackGui->getWidget(e.widget->getName()+"_label");
                string labelString = label->getTextString();
                cout << labelString << endl;
                sendOscMessage(labelString);
            }
        }

        /*
        else if(e.widget->getName() == "osc target" || e.widget->getName() == "osc port" ) {
            ofxUITextInput *textinput = (ofxUITextInput *) e.widget;
            cout << textinput->getTriggerType() << endl;
        }
        */
    }
}

void ofxTLButtons::sendOscMessage(string _message){

        string message = _message;
        ofxOscMessage m;
        m.setAddress(message);
        sender.sendMessage(m);
}

void ofxTLButtons::sendOscMessage(string _message, float _value){

        string message = _message;
        float argument = _value;
        ofxOscMessage m;
        m.setAddress(message);
        m.addFloatArg(argument);
        sender.sendMessage(m);
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

void ofxTLButtons::trackGuiDelete(){
    trackGui->disable();
    ofRemoveListener(trackGui->newGUIEvent, this, &ofxTLButtons::trackGuiEvent);
}

//update is called every frame.
//if your track triggers events it's good to do it here
//if timeline is set to thread this is called on the back thread so
//be careful if loading images in herre
void ofxTLButtons::update(){
    //trackGui->update();
    trackGui->getRect()->width = bounds.width;
    trackGui->getRect()->height = bounds.height;
    trackGui->getRect()->y = bounds.getMinY();
}

//draw your track contents. use ofRectangle bounds to know where to draw
//and the Track functions screenXToMillis() or millisToScreenX() to respect zoom
void ofxTLButtons::draw(){

    trackGui->draw();
	//this is just a simple example
	/*
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
	*/
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
	return "Buttons";
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
