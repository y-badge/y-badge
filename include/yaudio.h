#ifndef YAUDIO_H
#define YAUDIO_H

#include <stdint.h>

class YAudio {
  public:
    void setup();
    void loop();
    void setVolume(uint8_t volume);
};

#endif /* YAUDIO_H */
