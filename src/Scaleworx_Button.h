//
//  Scaleworx_Button.h
//  
//
//  Created by Blain Hamon on 10/19/19.
//

#include <inttypes.h>

typedef enum : uint8_t {
    ButtonStateIdle,
	ButtonStatePressed,
	ButtonStatePendingNextPress,
	ButtonStateLongPressFired,
} ButtonFiniteState;

class Button { //Ground = 'pressed'
protected:
    uint32_t lastDown;
    uint32_t lastUp;
    uint8_t pin;
    ButtonFiniteState state;
    uint8_t value;
    uint8_t numberOfPresses;
    uint8_t isPressed;
    uint8_t valueChanged;
public:
	Button (uint8_t newPin);
    uint8_t getHasValueChanged() {
        uint8_t result = valueChanged;
        valueChanged = 0;
        return result;
    };
    uint8_t getValue() { return value; };
    void checkState();
};
