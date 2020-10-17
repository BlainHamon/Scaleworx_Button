#include <Scaleworx_Button.h>
#include <Arduino.h>

#define LONGPRESSTIME	1000
#define CLICKTIMEOUT	500

Button::Button (uint8_t newPin, uint8_t startValue) :
    lastDown(0), lastUp(0), pin(newPin),
    state(ButtonStateIdle), value(startValue),
    numberOfPresses(0), isPressed(false),
    valueChanged(0)
{
	pinMode(pin, INPUT_PULLUP);
};

void Button::checkState() {
    isPressed = !digitalRead(pin);
	uint32_t time = millis();

	if (isPressed) {
		lastDown = time;
	} else {
		lastUp = time;
	}

	switch (state) {
		case ButtonStateIdle:
			if (isPressed) {
				state = ButtonStatePressed;
                numberOfPresses = 1;
			}
		break;
		case ButtonStatePressed:
			if (!isPressed) { // Button up
				state = ButtonStatePendingNextPress;
			} else if (time - lastUp > LONGPRESSTIME) {
				state = ButtonStateLongPressFired;
                value = 0;
                valueChanged = 1;
			}
		break;
		case ButtonStatePendingNextPress:
			if (isPressed) { //Next press
                numberOfPresses += 1;
				state = ButtonStatePressed;
			} else if (time - lastDown > CLICKTIMEOUT) {
                state = ButtonStateIdle;
                value = numberOfPresses;
                valueChanged = 1;
			}
		break;
		case ButtonStateLongPressFired:
			if (!isPressed) {
				state = ButtonStateIdle;
			}
		break;
		default:
			state = ButtonStateIdle;
		break;
	}
}
