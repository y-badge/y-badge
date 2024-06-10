#ifndef YBOARDV3_H
#define YBOARDV3_H

#include <Adafruit_AHTX0.h>
#include <Adafruit_NeoPixel.h>
#include <FS.h>
#include <SD.h>
#include <SparkFun_LIS2DH12.h>
#include <stdint.h>

#include "yaudio.h"

struct accelerometer_data {
    float x;
    float y;
    float z;
};

struct temperature_data {
    float temperature;
    float humidity;
};

class YBoardV3 {
  public:
    YBoardV3();
    virtual ~YBoardV3();

    void setup();

    ////////////////////////////// LEDs
    //////////////////////////////////////////////
    void set_led_color(uint16_t index, uint8_t red, uint8_t green, uint8_t blue);

    void set_led_brightness(uint8_t brightness);

    void set_all_leds_color(uint8_t red, uint8_t green, uint8_t blue);

    ////////////////////////////// Switches/Buttons
    //////////////////////////////////
    /*
     *  This function returns the state of a switch.
     *  The switch_idx is an integer between 1 and 2, representing the number of
     * the target switch (for example, 1 corresponds to switch 1 on the board).
     * The bool return type means that this function returns a boolean value (true
     * or false). True corresponds to the switch being on, and false corresponds
     * to the switch being off.
     */
    bool get_switch(uint8_t switch_idx);

    /*
     *  This function returns the state of a button.
     *  The button_idx is an integer between 1 and 3, representing the number of
     * the target button (for example, 1 corresponds to button 1 on the board).
     * The bool return type means that this function returns a boolean value (true
     * or false). True corresponds to the button being pressed, and false
     * corresponds to the button being released.
     */
    bool get_button(uint8_t button_idx);

    int get_knob();

    ////////////////////////////// Speaker/Tones
    /////////////////////////////////////
    void loop_speaker();

    void play_song_from_sd(const char *filename);

    void set_speaker_volume(uint8_t volume);

    void play_notes(std::string notes);

    ////////////////////////////// Accelerometer
    ////////////////////////////////////////
    bool accelerometer_available();

    accelerometer_data get_accelerometer();

    // ////////////////////////////// Temperature
    // /////////////////////////////////////
    temperature_data get_temperature();

    // LEDs
    static constexpr int led_pin = 5;
    static constexpr int led_count = 20;

    // Controls
    static constexpr int knob_pin = 9;
    static constexpr int switch1_pin = 16;
    static constexpr int switch2_pin = 18;
    static constexpr int button1_pin = 17;
    static constexpr int button2_pin = 7;

    // I2C Connections
    static constexpr int sda_pin = 2;
    static constexpr int scl_pin = 1;

    // I2C Devices
    static constexpr int accel_addr = 0x19;

    // microSD Card Reader connections
    static constexpr int sd_cs_pin = 10;
    static constexpr int spi_mosi_pin = 11;
    static constexpr int spi_miso_pin = 13;
    static constexpr int spi_sck_pin = 12;

    // I2S Connections
    static constexpr int i2s_dout_pin = 14;
    static constexpr int i2s_bclk_pin = 21;
    static constexpr int i2s_lrc_pin = 47;

  private:
    Adafruit_NeoPixel strip;
    // YAudio yaudio;
    SPARKFUN_LIS2DH12 accel;
    Adafruit_AHTX0 aht;
    bool wire_begin = false;

    void setup_leds();
    void setup_switches();
    void setup_buttons();
    void setup_speaker();
    void setup_accelerometer();
    void setup_temperature();
    void setup_audio();
};

extern YBoardV3 Yboard;

#endif /* YBOARDV3_H */
