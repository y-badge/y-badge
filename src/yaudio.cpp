#include "yaudio.h"

// #include <I2S.h>

namespace YAudio {

// The number of bits per sample.
static const int BITS_PER_SAMPLE = 16;
static const int BYTES_PER_SAMPLE = BITS_PER_SAMPLE / 8;
static const int SAMPLE_RATE = 8000; // sample rate in Hz

// The number of frames available in the I2S buffer. This will be 0, 1 or 2.  There are 2 frames
// created by the I2S library, and this will be decremented when we write to the I2S buffer, and
// incrmented when the I2S buffer provides a callback indicating that it has finished writing a
// frame.
static int i2s_buf_num_empty_frames;

// The number of frames of valid PCM audio data in the audio buffer. This will be incremented when
// we add a note to the audio buffer, and decremented when we write a frame to the I2S buffer.
static int audio_buf_num_populated_frames;

// The audio buffer. This is where we store the PCM audio data that we want to play.
// This is sized large enough to hold an almost full frame (1023 bytes), plus the next note.
// The largest note is a whole note at tempo = 40bps, sample rate = 8000,
// which is 4*(60/40)*8000 = 48000 samples.
// 48000 samples + 1023 = 49023, which is less than 48 frames (48 * 1024 = 49152)
static const int FRAME_SIZE = 1024;
static const int AUDIO_BUF_NUM_FRAMES = 96;
static int16_t audio_buf[FRAME_SIZE * AUDIO_BUF_NUM_FRAMES];

// This is the index of the next frame to write to the I2S buffer.
static int audio_buf_frame_idx_to_send;

// This is the index into the audio buffer of the next sample to write to
static int audio_buf_empty_idx;

// This is the sequence of notes to play
static std::string notes;

// Temp
static const int beats_per_minute = 60;

// Local private functions
static void generate_sine_wave(double frequency, int num_samples, double amplitude);

// I2S is running?
bool i2s_running;

////////////////////////////// Public Functions ///////////////////////////////
void add_notes(std::string notes) { YAudio::notes += notes; }

////////////////////////////// Private Functions ///////////////////////////////

void done_buf() {
    i2s_buf_num_empty_frames++;
    Serial.printf("Done_buf. Empty: %d\n", i2s_buf_num_empty_frames);

    if (audio_buf_num_populated_frames) {
        // Write a frame to the I2S buffer
        int size = I2S.write_blocking(&audio_buf[audio_buf_frame_idx_to_send * FRAME_SIZE],
                                      FRAME_SIZE * BYTES_PER_SAMPLE);
        Serial.printf("Wrote frame %d to I2S. %d bytes\n", audio_buf_frame_idx_to_send, size);
        audio_buf_num_populated_frames--;
        i2s_buf_num_empty_frames--;
        audio_buf_frame_idx_to_send = (audio_buf_frame_idx_to_send + 1) % AUDIO_BUF_NUM_FRAMES;
    }
}

void generate_triangle_wave(double frequency, int num_samples, double amplitude) {
    double period = SAMPLE_RATE / frequency; // Period of one cycle of the triangle wave

    for (int i = 0; i < num_samples; ++i) {
        double phase = fmod(i, period); // Current phase in the period
        if (phase < period / 2) {
            audio_buf[audio_buf_empty_idx] =
                2 * amplitude * phase / (period / 2) - amplitude; // Rising edge
        } else {
            audio_buf[audio_buf_empty_idx] =
                -2 * amplitude * (phase - period / 2) / (period / 2) + amplitude; // Falling edge
        }
        audio_buf_empty_idx = (audio_buf_empty_idx + 1) % (FRAME_SIZE * AUDIO_BUF_NUM_FRAMES);
        if (audio_buf_empty_idx % FRAME_SIZE == 0) {
            Serial.println("Frame filled");
            audio_buf_num_populated_frames++;
        }
    }
}

static void generate_sine_wave(double frequency, int num_samples, double amplitude) {
    for (int i = 0; i < num_samples; i++) {
        audio_buf[audio_buf_empty_idx] = amplitude * sin(2 * 3.14 * frequency * i / SAMPLE_RATE);
        audio_buf_empty_idx = (audio_buf_empty_idx + 1) % (FRAME_SIZE * AUDIO_BUF_NUM_FRAMES);
        if (audio_buf_empty_idx % FRAME_SIZE == 0) {
            Serial.println("Frame filled");
            audio_buf_num_populated_frames++;
        }

        // audio_buf[audio_buf_empty_idx] = amplitude * sin(2 * 3.14 * frequency * i / SAMPLE_RATE);
        // audio_buf_empty_idx = (audio_buf_empty_idx + 1) % (FRAME_SIZE * AUDIO_BUF_NUM_FRAMES);
        // if (audio_buf_empty_idx % FRAME_SIZE == 0) {
        //     Serial.println("Frame filled");
        //     audio_buf_num_populated_frames++;
        // }
    }
}

static void generate_square_wave(double frequency, int num_samples, double amplitude) {
    double period = SAMPLE_RATE / frequency; // Period of one cycle of the square wave

    for (int i = 0; i < num_samples; ++i) {
        double phase = fmod(i, period); // Current phase in the period
        if (phase < period / 2) {
            audio_buf[audio_buf_empty_idx] = amplitude; // Rising edge
        } else {
            audio_buf[audio_buf_empty_idx] = -amplitude; // Falling edge
        }
        Serial.printf("Wrote %d to index %d\n", audio_buf[audio_buf_empty_idx],
                      audio_buf_empty_idx);
        audio_buf_empty_idx = (audio_buf_empty_idx + 1) % (FRAME_SIZE * AUDIO_BUF_NUM_FRAMES);
        if (audio_buf_empty_idx % FRAME_SIZE == 0) {
            Serial.println("Frame filled");
            audio_buf_num_populated_frames++;
        }
    }
}

void setup() {
    I2S.setSimplex(); // set to mono mode
    I2S.setSckPin(21);
    I2S.setFsPin(47);
    I2S.setDataPin(14);
    I2S.setBufferSize(FRAME_SIZE);
    I2S.onTransmit(done_buf);

    // Initialize global variables
    i2s_buf_num_empty_frames = 2;
    audio_buf_num_populated_frames = 0;
    audio_buf_frame_idx_to_send = 0;
    audio_buf_empty_idx = 0;
    notes = "";
    i2s_running = false;

    if (!I2S.begin(I2S_PHILIPS_MODE, SAMPLE_RATE, BITS_PER_SAMPLE)) {
        Serial.println("Failed to initialize I2S!");
        while (1)
            ; // do nothing
    }
    i2s_running = true;
    Serial.println("I2S started");
}

void loop() {

    // If there is available space in the I2S buffer, and we have frames in the audio
    // buffer, write them out
    // if (audio_buf_num_populated_frames && i2s_buf_num_empty_frames) {
    //     // Write a frame to the I2S buffer
    //     Serial.println("Writing frame to I2S");
    //     I2S.write_blocking(&audio_buf[audio_buf_frame_idx_to_send * FRAME_SIZE],
    //                        FRAME_SIZE * BYTES_PER_SAMPLE);
    //     audio_buf_num_populated_frames--;
    //     i2s_buf_num_empty_frames--;
    //     audio_buf_frame_idx_to_send = (audio_buf_frame_idx_to_send + 1) % AUDIO_BUF_NUM_FRAMES;
    // }

    // Try and fill notes into the audio buffer until we run out of space, or we have no more notes
    while (notes.length()) {
        // Serial.printf("Notes: %s\n", notes.c_str());

        // If first character is white space, remove it and continue
        if (isspace(notes[0])) {
            notes.erase(0, 1);
            continue;
        }

        // Check that note is a C
        if (notes[0] == 'C' || notes[0] == 'D' || notes[0] == 'E' || notes[0] == 'F') {

            // Check if we have enough space in the buffer to add the note
            int avail_space = (AUDIO_BUF_NUM_FRAMES - audio_buf_num_populated_frames) * FRAME_SIZE;
            int note_samples = (60.0 / beats_per_minute) * SAMPLE_RATE;
            Serial.printf("Avail space: %d, Note samples: %d\n", avail_space, note_samples);

            // If we don't have enough space, return
            if (avail_space < note_samples) {
                return;
            }
            Serial.printf("Adding note: %c\n", notes[0]);

            double freq;
            switch (notes[0]) {
            case 'C':
                freq = 261.63;
                break;
            case 'D':
                freq = 293.66;
                break;
            case 'E':
                freq = 329.63;
                break;
            case 'F':
                freq = 349.23;
                break;
            }

            // If we have space, add the note to the buffer and erase it from the notes string
            // generate_triangle_wave(freq, note_samples, 5000);
            generate_square_wave(freq, note_samples, 5000);

            notes.erase(0, 1);
            break;
        }
    }

    if (notes.length() == 0 && i2s_buf_num_empty_frames >= 2 &&
        audio_buf_num_populated_frames == 0 && i2s_running) {
        Serial.println("Stopping I2S");
        I2S.end();
        i2s_running = false;
    }
}

void setVolume(uint8_t volume) {
    // TODO
}

}; // namespace YAudio