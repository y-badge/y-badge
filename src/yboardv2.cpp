#include "yboardv2.h"

YBoardV2::YBoardV2() : YBoardBase(5, 20, 14) {}

YBoardV2::~YBoardV2() {}

void YBoardV2::setup() {
    YBoardBase::setup();

    setup_switches();
    setup_buttons();
    setup_timer();
}

YBoardBase::BoardType YBoardV2::get_type() { return BoardType::v2; }

////////////////////////////// Switches ///////////////////////////////
void YBoardV2::setup_switches() {
    pinMode(this->switch1_pin, INPUT);
    pinMode(this->switch2_pin, INPUT);
}

bool YBoardV2::get_switch(uint8_t switch_idx) {
    switch (switch_idx) {
    case 1:
        return !digitalRead(this->switch1_pin);
    case 2:
        return !digitalRead(this->switch2_pin);
    default:
        return false;
    }
}

////////////////////////////// Buttons ///////////////////////////////
void YBoardV2::setup_buttons() {
    pinMode(this->button1_pin, INPUT);
    pinMode(this->button2_pin, INPUT);
    pinMode(this->button3_pin, INPUT);
}

bool YBoardV2::get_button(uint8_t button_idx) {
    switch (button_idx) {
    case 1:
        return !digitalRead(this->button1_pin);
    case 2:
        return !digitalRead(this->button2_pin);
    case 3:
        return !digitalRead(this->button3_pin);
    default:
        return false;
    }
}

////////////////////////////// Knob ///////////////////////////////
int YBoardV2::get_knob() {
    int value = map(analogRead(this->knob_pin), 0, 4095, 0, 100);
    value = max(0, value);
    value = min(100, value);
    return value;
}

////////////////////////////// Interrupt /////////////////////////////////////
void YBoardV2::setup_timer() {
    // Prescaler = 80, So timer clock = 80MHZ/80 = 1MHz = 1us period
    interrupt_timer = timerBegin(0, 80, true);

    timerAttachInterrupt(interrupt_timer, []() {}, true);

    // Alarm runs every 10 cycles.  1us * 10 = 100us period
    timerAlarmWrite(interrupt_timer, 100, true);
}

////////////////////////////// Speaker/Tones /////////////////////////////////////
void YBoardV2::play_note(unsigned int freq, unsigned long duration) {
    tone(this->tone_pin, freq, duration);
}
