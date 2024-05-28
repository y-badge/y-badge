#include "yboard.h"

#if defined(YBOARDV2)
YBoardV2 yboard;
#elif defined(YBOARDV3)
YBoardV3 yboard;
#else
#error "No board defined"
#endif
