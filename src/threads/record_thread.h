//
// Created by samuel on 21/01/20.
//

#ifndef SPECTRIXPC_RECORD_THREAD_H
#define SPECTRIXPC_RECORD_THREAD_H

#include <thread>
#include "RtAudio.h"

void create_record_thread(unsigned int sample_rate, unsigned int buffer_frame, unsigned int nb_channel);

int step(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
         double streamTime, RtAudioStreamStatus status, void *userData );

#endif //SPECTRIXPC_RECORD_THREAD_H
