#ifndef YBOARDV3_H
#define YBOARDV3_H

#include <Adafruit_AHTX0.h>
#include <Adafruit_NeoPixel.h>
#include <Audio.h>
#include <FS.h>
#include <SD.h>
#include <SparkFun_LIS2DH12.h>
#include <stdint.h>

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

    /*
     *  This function initializes the YBoard. This function must be called before using any of the
     * YBoard features.
     */
    void setup();

    ////////////////////////////// LEDs ///////////////////////////////////////////

    /*
     *  This function sets the color of an individual LED.
     *  The index is an integer between 1 and 20, representing the number of the
     * target LED (for example, 1 corresponds to the first LED on the board).
     *  The red, green, and blue values are integers between 0 and 255, representing
     * the intensity of the corresponding color. For example, if you want to set the
     * LED to red, you would set red to 255 and green and blue to 0.
     */
    void set_led_color(uint16_t index, uint8_t red, uint8_t green, uint8_t blue);

    /*
     *  This function sets the brightness of all the LEDs on the board.
     *  The brightness is an integer between 0 and 255, representing the intensity
     * of the LEDs. A brightness of 0 is off, and a brightness of 255 is full
     * brightness.
     */
    void set_led_brightness(uint8_t brightness);

    /*
     *  This function sets the color of all the LEDs on the board.
     *  The red, green, and blue values are integers between 0 and 255, representing
     * the intensity of the corresponding color. For example, if you want to set all
     * the LEDs to red, you would set red to 255 and green and blue to 0.
     */
    void set_all_leds_color(uint8_t red, uint8_t green, uint8_t blue);

    ////////////////////////////// Switches/Buttons ///////////////////////////////
    /*
     *  This function returns the state of a switch.
     *  The switch_idx is an integer between 1 and 2, representing the number of the
     * target switch (for example, 1 corresponds to switch 1 on the board). The bool
     * return type means that this function returns a boolean value (true or false).
     *  True corresponds to the switch being on, and false corresponds to the switch
     * being off.
     */
    bool get_switch(uint8_t switch_idx);

    /*
     *  This function returns the state of a button.
     *  The button_idx is an integer between 1 and 2, representing the number of the
     * target button (for example, 1 corresponds to button 1 on the board). The bool
     * return type means that this function returns a boolean value (true or false).
     *  True corresponds to the button being pressed, and false corresponds to the
     * button being released.
     */
    bool get_button(uint8_t button_idx);

    /*
     *  This function returns the value of the knob.
     *  The return type is an integer between 0 and 100, representing the position
     * of the knob. A value of 0 corresponds to the knob being turned all the way to
     * the left, and a value of 100 corresponds to the knob being turned all the way
     * to the right.
     */
    int get_knob();

    ////////////////////////////// Speaker/Tones //////////////////////////////////
    /*
     *  This function continues to play a sound on the speaker after the
     * play_song_from_sd function is called. This function must be called often to
     * playback the sound on the speaker.
     */
    void loop_speaker();

    /*
     *  This function plays a sound on the speaker. The filename is a string
     * representing the name of the sound file to play. The return type is a boolean
     * value (true or false). True corresponds to the sound being played
     * successfully, and false corresponds to an error playing the sound. The sound
     * file must be stored on the microSD card. After this function is called, the
     * loop_speaker function must be called often to playback the sound on the speaker.
     */
    bool play_song_from_sd(const char *filename);

    /*
     *  This function sets the speaker volume. The volume is an integer between 0
     * and 100. A volume of 0 is off, and a volume of 100 is full volume.
     */
    void set_speaker_volume(uint8_t volume);

    ///////////////////////////// Accelerometer ////////////////////////////////////
    /*
     *  This function returns whether accelerometer data is available.
     *  The bool return type means that this function returns a boolean value (true
     * or false). True corresponds to accelerometer data being available, and false
     * corresponds to accelerometer data not being available.
     */
    bool accelerometer_available();

    /*
     *  This function returns the accelerometer data.
     *  The return type is a struct containing the x, y, and z values of the
     * accelerometer data. These values are floats, representing the acceleration
     * in the x, y, and z directions, respectively.
     */
    accelerometer_data get_accelerometer();

    /////////////////////////////// Temperature /////////////////////////////////////

    /*
     *  This function returns the temperature and humidity data.
     *  The return type is a struct with temperature and humidity fields.
     * These values are floats.
     */
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
    Audio audio;
    SPARKFUN_LIS2DH12 accel;
    Adafruit_AHTX0 aht;
    bool wire_begin = false;

    void setup_leds();
    void setup_switches();
    void setup_buttons();
    bool setup_speaker();
    bool setup_accelerometer();
    bool setup_temperature();
};

extern YBoardV3 Yboard;

#endif /* YBOARDV3_H */
