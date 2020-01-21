#!/usr/bin/env bash

wget http://www.music.mcgill.ca/~gary/rtaudio/release/rtaudio-5.1.0.tar.gz
tar -zxvf ./rtaudio-5.1.0.tar.gz

cd ./rtaudio-5.1.0
./configure --with-alsa
make

cd ..


