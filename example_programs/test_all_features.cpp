#include "example_programs.h"

#include "ybadge.h"

int get_brightness();
void light_all_lights(int r, int g, int b);
void turn_off_all_lights();
bool check_switches();

/*
 * This function tests all of the features of the badge.
 * It will display different colors depending on which button is pressed.
 * It will also play different notes depending on which button is pressed IF at
 * least one of the two switches is on It will also change the brightness of the
 * LEDs depending on the position of the knob.
 */
void test_all_features() {
  while (true) {
    if (buttons_get(1)) {
      while (buttons_get(1)) {
        light_all_lights(255, 0, 0);
        leds_set_brightness(get_brightness());
        if (check_switches()) {
          speaker_play_note(NOTE_C4, 10);
        }
      }
    } else if (buttons_get(2)) {
      while (buttons_get(2)) {
        light_all_lights(255, 255, 0);
        leds_set_brightness(get_brightness());
        if (check_switches()) {
          speaker_play_note(NOTE_D4, 10);
        }
      }
    } else if (buttons_get(3)) {
      while (buttons_get(3)) {
        light_all_lights(0, 255, 0);
        leds_set_brightness(get_brightness());
        if (check_switches()) {
          speaker_play_note(NOTE_E4, 10);
        }
      }
    } else {
      light_all_lights(255, 255, 255);
      leds_set_brightness(get_brightness());
    }
  }
}

// This function converts the knob's output (1-100) to a brightness value
// (0-255)
int get_brightness() {
  int brightness = 255 * knob_get() / 100;
  return floor(brightness);
}

// This function lights up all of the LEDs with the given color
void light_all_lights(int r, int g, int b) {
  for (int i = 1; i <= 20; i++) {
    leds_set_color(i, r, g, b);
  }
}

// This function turns off all of the LEDs
void turn_off_all_lights() { light_all_lights(0, 0, 0); }

// This function checks if either of the switches are on
bool check_switches() { return switches_get(1) || switches_get(2); }