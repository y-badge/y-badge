#ifndef YBOARDV3_H
#define YBOARDV3_H

#include "yboard_base.h"

#include <Adafruit_AHTX0.h>
#include <Audio.h>
#include <FS.h>
#include <SD.h>
#include <SparkFun_LIS2DH12.h>
#include <stdint.h>

class YBoardV3 : public YBoardBase {
  public:
    YBoardV3();
    virtual ~YBoardV3();

    void setup() override;

    BoardType get_type() override;

    ////////////////////////////// Switches/Buttons ///////////////////////////////
    /*
     *  This function returns the state of a switch.
     *  The switch_idx is an integer between 1 and 2, representing the number of the
     * target switch (for example, 1 corresponds to switch 1 on the board). The bool
     * return type means that this function returns a boolean value (true or false).
     *  True corresponds to the switch being on, and false corresponds to the switch
     * being off.
     */
    bool get_switch(uint8_t switch_idx) override;

    /*
     *  This function returns the state of a button.
     *  The button_idx is an integer between 1 and 3, representing the number of the
     * target button (for example, 1 corresponds to button 1 on the board). The bool
     * return type means that this function returns a boolean value (true or false).
     *  True corresponds to the button being pressed, and false corresponds to the
     * button being released.
     */
    bool get_button(uint8_t button_idx) override;

    int get_knob() override;

    ////////////////////////////// Speaker/Tones //////////////////////////////////
    void loop_speaker();

    void play_song_from_sd(const char *filename);

    void set_speaker_volume(uint8_t volume);

    ////////////////////////////// Accelerometer /////////////////////////////////////
    void get_accelerometer(float *accelX, float *accelY, float *accelZ);

    // ////////////////////////////// Temperature /////////////////////////////////////
    void get_temperature(float *temperature, float *humidity);

  protected:
    const int switch1_pin = 16;
    const int switch2_pin = 18;
    const int button1_pin = 17;
    const int button2_pin = 7;

    // I2C Connections
    const int sda_pin = 2;
    const int scl_pin = 1;

    // I2C Devices
    const int accel_addr = 0x19;

    // microSD Card Reader connections
    const int sd_cs_pin = 10;
    const int spi_mosi_pin = 11;
    const int spi_miso_pin = 13;
    const int spi_sck_pin = 12;

    // I2S Connections
    const int i2s_dout_pin = 14;
    const int i2s_bclk_pin = 21;
    const int i2s_lrc_pin = 47;

  private:
    Audio audio;
    SPARKFUN_LIS2DH12 accel;
    Adafruit_AHTX0 aht;
    bool wire_begin = false;

    void setup_switches();
    void setup_buttons();
    void setup_speaker();
    void setup_accelerometer();
    void setup_temperature();
};

#endif /* YBOARDV3_H */
