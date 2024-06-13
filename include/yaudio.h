#ifndef YAUDIO_H
#define YAUDIO_H

#include <stdint.h>
#include <string>

namespace YAudio {

void setup();
void loop();
void set_wave_volume(uint8_t volume);
void add_notes(std::string notes);
void stop();
bool is_playing();
void play_sound_file(const char *filename);
}; // namespace YAudio

#endif /* YAUDIO_H */
