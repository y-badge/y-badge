#include "yboard.h"

#if defined(YBOARDV2)
YBoardV2 Yboard;
#elif defined(YBOARDV3)
YBoardV3 Yboard;
#else
static_assert(false,
              "No YBoard defined. Please define YBOARDV2 or YBOARDV3 in your platformio.ini file.");
#endif
