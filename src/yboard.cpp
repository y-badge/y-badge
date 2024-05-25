#include "yboard.h"

YBoard::YBoard(int led_pin, int led_count, int knob_pin)
    : led_pin(led_pin), led_count(led_count), knob_pin(knob_pin),
      strip(YBoard::led_count, YBoard::led_pin, NEO_GRB + NEO_KHZ800) {}

YBoard::~YBoard() {}

void YBoard::setup() {
    // Initialize the board
    setup_leds();
    // setup_timer();
}

void YBoard::setup_leds() {
    strip.begin();
    strip.clear();
    set_led_brightness(50);
}

void YBoard::set_led_color(uint16_t index, uint8_t red, uint8_t green, uint8_t blue) {
    strip.setPixelColor(index, red, green, blue);
    strip.show();
}

void YBoard::set_led_brightness(uint8_t brightness) { strip.setBrightness(brightness); }

void YBoard::set_all_leds_color(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < this->led_count; i++) {
        strip.setPixelColor(i, red, green, blue);
    }
    strip.show();
}

uint16_t YBoard::get_led_count() { return this->led_count; }

int YBoard::get_knob() {
    // Map value from 0 to 100
    return map(analogRead(this->knob_pin), 0, 4095, 0, 100);
}
