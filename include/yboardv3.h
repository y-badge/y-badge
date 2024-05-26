#ifndef YBOARDV3_H
#define YBOARDV3_H

#include <Audio.h>
#include <FS.h>
#include <SD.h>
#include <stdint.h>

#include "yboard.h"

class YBoardV3 : public YBoard {
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

  protected:
    const int switch1_pin = 16;
    const int switch2_pin = 18;
    const int button1_pin = 17;
    const int button2_pin = 7;

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

    void setup_switches();
    void setup_buttons();
    void setup_speaker();
};

#endif /* YBOARDV3_H */
