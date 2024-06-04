#include "yaudio.h"

#include <I2S.h>

static int16_t sound_buf[60 * 256];

static bool done;
static int done_cnt;
static bool stop_i2s;

void done_buf() {
    Serial.println("Done_buf");
    done_cnt++;
    if (done_cnt == 4) {
        stop_i2s = true;

        Serial.println("I2S stopped");
    }
}

void generate_triangle_wave(double frequency, double sample_rate, int num_samples, double amplitude,
                            int16_t *buffer) {
    double period = sample_rate / frequency; // Period of one cycle of the triangle wave
    for (int i = 0; i < num_samples; ++i) {
        double phase = fmod(i, period); // Current phase in the period
        if (phase < period / 2) {
            buffer[i] = 2 * amplitude * phase / (period / 2) - amplitude; // Rising edge
        } else {
            buffer[i] =
                -2 * amplitude * (phase - period / 2) / (period / 2) + amplitude; // Falling edge
        }
    }
}

void generate_sine_wave(double frequency, double sample_rate, int num_samples, double amplitude,
                        int16_t *buffer) {
    for (int i = 0; i < num_samples; ++i) {
        buffer[i] = amplitude * sin(2 * PI * frequency * i / sample_rate);
    }
}

void YAudio::setup() {
    I2S.setSimplex(); // set to mono mode
    I2S.setSckPin(21);
    I2S.setFsPin(47);
    I2S.setDataPin(14);
    I2S.setBufferSize(1024);
    I2S.onTransmit(done_buf);

    done = false;
    done_cnt = 0;
    stop_i2s = false;

    const int amplitude = 3000;

    // Middle C
    float freq = 261;

    // start I2S at the sample rate with 16-bits per sample
    i2s_mode_t mode = I2S_LEFT_JUSTIFIED_MODE;
    const int sampleRate = 8000; // sample rate in Hz
    const int bps = 16;

    // for (int i = 0; i < 3072; i++) {
    //     sound_buf[i] = amplitude * sin(2 * 3.14 * freq * i / (float)sampleRate);
    // }
    // generate_triangle_wave(freq, sampleRate, 3072, amplitude, sound_buf);
    generate_sine_wave(freq, sampleRate, 3072, amplitude, sound_buf);

    if (!I2S.begin(mode, sampleRate, bps)) {
        Serial.println("Failed to initialize I2S!");
        while (1)
            ; // do nothing
    }
    Serial.println("I2S started");
    // delay(2000);
}

void YAudio::loop() {
    // TODO

    if (!done) {
        Serial.println("Writing");
        Serial.printf("Available: %d\n", I2S.availableForWrite());
        //   size_t result = I2S.write_blocking(sound_buf, sizeof(sound_buf) / 32);
        //   // size_t result = I2S.write(sample);
        //   // Serial.printf("Wrote %d bytes\n", result);
        for (int i = 0; i < 12; i++) {
            I2S.write_blocking(&sound_buf[i * 256], 512);
        }
        Serial.println("Done");
        done_cnt = 0;
        stop_i2s = false;
        done = true;
    }

    if (stop_i2s) {
        I2S.end();
    }
}

void YAudio::setVolume(uint8_t volume) {
    // TODO
}