#if defined(YBOARDV2)
#include "yboardv2.h"
extern YBoardV2 Yboard;
#elif defined(YBOARDV3)
#include "yboardv3.h"
extern YBoardV3 Yboard;
#else
static_assert(false,
              "No YBoard defined. Please define YBOARDV2 or YBOARDV3 in your platformio.ini file.");
#endif
