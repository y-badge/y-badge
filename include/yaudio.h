#ifndef YAUDIO_H
#define YAUDIO_H

#include <stdint.h>
#include <string>

namespace YAudio {

bool setup_speaker();
bool setup_mic();
void loop();
void set_wave_volume(uint8_t volume);
bool add_notes(const std::string &new_notes);
void stop();
bool is_playing();
bool play_sound_file(const std::string &filename);
bool start_recording(const std::string &filename);
void stop_recording();
}; // namespace YAudio

#endif /* YAUDIO_H */
