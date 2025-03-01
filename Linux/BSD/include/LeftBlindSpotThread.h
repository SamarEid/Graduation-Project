#ifndef LEFT_BLIND_SPOT_THREAD_H
#define LEFT_BLIND_SPOT_THREAD_H

#include "BlindSpotDetection.h"
#include <thread>

void startLeftBlindSpot(Communication &comm);
void leftBlindSpotThread(Communication &comm);

#endif //LEFT_BLIND_SPOT_THREAD_H