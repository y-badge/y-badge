
#include "yboard.h"

void setup() {
    Serial.begin(9600);
    Yboard.setup();
}

void loop() {
    if (Yboard.get_switch(1)) {
        Yboard.set_led_color(0, 255, 0, 0);
    } else {
        Yboard.set_led_color(0, 0, 0, 0);
    }

    if (Yboard.get_switch(2)) {
        Yboard.set_led_color(1, 255, 0, 0);
    } else {
        Yboard.set_led_color(1, 0, 0, 0);
    }

    if (Yboard.get_button(1)) {
        Yboard.set_led_color(2, 255, 0, 0);
    } else {
        Yboard.set_led_color(2, 0, 0, 0);
    }

    if (Yboard.get_button(2)) {
        Yboard.set_led_color(3, 255, 0, 0);
    } else {
        Yboard.set_led_color(3, 0, 0, 0);
    }

    Yboard.set_led_color(4, map(Yboard.get_knob(), 0, 100, 0, 255), 0, 0);
}
