#ifndef RIGHT_BLIND_SPOT_THREAD_H
#define RIGHT_BLIND_SPOT_THREAD_H

#include "BlindSpotDetection.h"
#include <thread>


void startRightBlindSpot(Communication &comm);
void rightBlindSpotThread(Communication &comm);

#endif //RIGHT_BLIND_SPOT_THREAD_H