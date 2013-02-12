an addon to ofxTimeline to add a pseudo-track with UI widgets meant to manually send no-time-based OSC messages

to use it with ofxTimeline basically you have to do the following:
in addons.make after ofxTimeline and its dependencies add:

	ofxTLButtons

in you header file add:

	include "ofxTLButtons.h"

and the in your cpp file you can add buttons track with something like this:

	buttonsTrack = new ofxTLButtons(int rows, int columns, string osc_target_ip ,int osc_target_port, ofxTLButtonsType type);
    timeline.addTrack(trackName, buttonsTrack);
    timeline.bringTrackToTop(buttonsTrack);
        
where obviously rows and columns give you the number of osc buttons you want to add,
while osc_target_ip and osc_target_port are the ip and port number of the target you want to manually send osc messages to.
in case you want a pseudo-track with only buttons to send simple osc messages, then type will be set to OFXTLBUTTONS_TYPE_BUTTONS.
Associated to each button you will have a editable text label containing the message you want to send when clicking the button.

You can have a pseudo-track containing only sliders too, and in this case the constructor will be the same, but last argument will be set to OFXTLBUTTONS_TYPE_SLIDERS
Each slider message can be edited and customized too, and it will be sent with a float value as payload depending on the movement of the slider and in range 0.0 - 1.0.

![Schermata del 2013-02-12 10:47:20](https://f.cloud.github.com/assets/614123/148273/8fc588a2-74f9-11e2-918b-294f7083bf39.png)

You have a third option too, that will present you a pseudo-track with both buttons and sliders. In this case the constructor will be slightly different and will take the form:

    mixedControlsTrack = new ofxTLButtons(int button_rows, int button_columns, int slider_rows, int slider_columns, string osc_target_ip ,int osc_target_port, ofxTLButtonsType type);
    
type must be set to OFXTLBUTTONS_TYPE_MIXED, and as you can see there are arguments for both the buttons and sliders number of rows and columns.
As stated above, buttons will send simple argument messages, while sliders will append the corresponding float value to the user customizable argument.

![Schermata del 2013-02-12 18:29:10](https://f.cloud.github.com/assets/614123/149804/4a47f1ac-753a-11e2-9e52-1cd7b508ac88.png)

