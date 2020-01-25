//
// Created by samuel on 21/01/20.
//

#include "record_thread.h"

void create_record_thread(unsigned int sample_rate, unsigned int buffer_frame, unsigned int nb_channel) {
	RtAudio adc;
	if ( adc.getDeviceCount() < 1 ) {
		std::cout << "\nNo audio devices found!\n";
		exit( 0 );
	}
	RtAudio::StreamParameters parameters;
	parameters.deviceId = adc.getDefaultInputDevice();
	parameters.nChannels = nb_channel;
	parameters.firstChannel = 0;
	unsigned int sampleRate = sample_rate;
	unsigned int bufferFrames = buffer_frame;
	try {
		adc.openStream( NULL, &parameters, RTAUDIO_SINT16,
		                sampleRate, &bufferFrames, &step );
		adc.startStream();
	}
	catch ( RtAudioError& e ) {
		e.printMessage();
		exit( 0 );
	}

	char input;
	std::cout << "\nRecording ... press <enter> to quit.\n";
	std::cin.get( input );
	try {
		// Stop the stream
		adc.stopStream();
	}
	catch (RtAudioError& e) {
		e.printMessage();
	}
	if ( adc.isStreamOpen() ) adc.closeStream();
}

int
step(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status,
     void *userData) {

	if ( status )
		std::cout << "Stream overflow detected!" << std::endl;

	int *input_buffer = (int *) inputBuffer;
	for (int i = 0; i < nBufferFrames; i++)
		std::cout << input_buffer[i] << " ";
	std::cout << std::endl;

	return 0;
}
