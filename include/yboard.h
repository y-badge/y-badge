#ifndef YBOARD_H
#define YBOARD_H

#include <Adafruit_NeoPixel.h>
#include <stdint.h>

#include "Arduino.h"

class YBoard {
  public:
    YBoard(int led_pin, int led_count, int knob_pin);
    virtual ~YBoard();

    // Define an enum for type identification
    enum BoardType { v2, v3 };

    virtual void setup();

    virtual BoardType get_type() = 0;

    ////////////////////////////// LEDs ///////////////////////////////////////////
    /*
     *  This function sets the color of a single LED.
     *  The index is an integer between 1 and 20, representing the number of the
     * target LED (for example, 1 corresponds to LED 1 on the board). The red,
     * green, and blue values are integers between 0 (off) and 255 (full
     * brightness). The void return type means that this function does not return a
     * value.
     */
    void set_led_color(uint16_t index, uint8_t red, uint8_t green, uint8_t blue);

    /*
     *  This function sets the brightness of all of the LEDs.
     *  The brightness is specified as an integer between 0 (off) and 255 (full
     * brightness). The void return type means that this function does not return a
     * value.
     */
    void set_led_brightness(uint8_t brightness);

    /*
     *  This function sets the color of all the LEDs on the board.
     *  The red, green, and blue values are integers between 0 (off) and 255 (full
     * brightness). The void return type means that this function does not return a
     * value.
     */
    void set_all_leds_color(uint8_t red, uint8_t green, uint8_t blue);

    uint16_t get_led_count();

    ////////////////////////////// Switches/Buttons ///////////////////////////////
    /*
     *  This function returns the state of a switch.
     *  The switch_idx is an integer between 1 and 2, representing the number of the
     * target switch (for example, 1 corresponds to switch 1 on the board). The bool
     * return type means that this function returns a boolean value (true or false).
     *  True corresponds to the switch being on, and false corresponds to the switch
     * being off.
     */
    virtual bool get_switch(uint8_t switch_idx) = 0;

    /*
     *  This function returns the state of a button.
     *  The button_idx is an integer between 1 and 3, representing the number of the
     * target button (for example, 1 corresponds to button 1 on the board). The bool
     * return type means that this function returns a boolean value (true or false).
     *  True corresponds to the button being pressed, and false corresponds to the
     * button being released.
     */
    virtual bool get_button(uint8_t button_idx) = 0;

    /*
     *  This function returns the position of the knob.
     *  The int return type means that this function returns an integer value.
     *  The value returned is between 0 and 100, representing the position of the
     * knob (0 is fully counter-clockwise, 100 is fully clockwise).
     */
    int get_knob();

  protected:
    const int led_count;
    const int led_pin;
    const int knob_pin;

  private:
    Adafruit_NeoPixel strip;

    void setup_leds();
};

#endif /* YBOARD_H */
