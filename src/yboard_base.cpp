#include "yboard_base.h"

YBoardBase::YBoardBase(int led_pin, int led_count, int knob_pin)
    : led_pin(led_pin), led_count(led_count), knob_pin(knob_pin),
      strip(led_count, led_pin, NEO_GRB + NEO_KHZ800) {}

YBoardBase::~YBoardBase() {}

void YBoardBase::setup() { setup_leds(); }

void YBoardBase::setup_leds() {
    strip.begin();
    strip.clear();
    set_led_brightness(50);
}

void YBoardBase::set_led_color(uint16_t index, uint8_t red, uint8_t green, uint8_t blue) {
    strip.setPixelColor(index, red, green, blue);
    strip.show();
}

void YBoardBase::set_led_brightness(uint8_t brightness) { strip.setBrightness(brightness); }

void YBoardBase::set_all_leds_color(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < this->led_count; i++) {
        strip.setPixelColor(i, red, green, blue);
    }
    strip.show();
}

uint16_t YBoardBase::get_led_count() { return this->led_count; }
