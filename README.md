an addon to ofxTimeline to add a track with UI widgets meant to manually send no-time-based OSC messages

to use it with ofxTimeline basically you have to do the following:
in addons.make after ofxTimeline and its dependencies add:

	ofxTLButtons

in you header file add:

	include "ofxTLButtons.h"

and the in your cpp file you can add buttons track with something like this:

	buttonsTrack = new ofxTLButtons(int rows, int columns, string osc_target_ip ,int osc_target_port);
        timeline.addTrack(trackName, buttonsTrack);
        timeline.bringTrackToTop(buttonsTrack);
        newTrack = buttonsTrack;

where obviously rows and columns give you the number of osc buttons you want to add,
while osc_target_ip and osc_target_port are the ip and port number of the target you want to manually send osc messages to.
