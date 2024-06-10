#ifndef YAUDIO_H
#define YAUDIO_H

#include <stdint.h>
#include <string>

namespace YAudio {

void setup();
void loop();
void setVolume(uint8_t volume);
void add_notes(std::string notes);
}; // namespace YAudio

#endif /* YAUDIO_H */
