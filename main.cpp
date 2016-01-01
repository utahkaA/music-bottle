// -------------------------------------------------------------------------------
// Name:           music_bottle/main.cpp
// Author:         @utahkaA (Twitter, GitHub, and so on...)
// Created:        Nov 18th, 2015
// Last Date:      Dec 30th, 2015
// Note:           xxxxx
// -------------------------------------------------------------------------------
#include "mbed.h"
#include "SDFileSystem.h"
#include "wave_player.h"
#include <string>

const int MAX = 65535;
const int THRESHOLD_1 = 40000;  // Threshold
const int THRESHOLD_2 = 20000;

AnalogOut speaker(p18);
AnalogIn press(p20);
SDFileSystem sd(p5, p6, p7, p8, "sd");
wave_player waver(&speaker);
Ticker flipper;

std::string file_name = "/sd/hogehoge.wav";
bool playing;
FILE *wav_file;

void wav_open(string wav_name) {
    wav_file = fopen(wav_name.c_str(), "r");
    if (wav_file == NULL) {
        error("Could not open wav file for read\n");
    }
}

void change_music() {
    printf("press: %d\n\r", press.read_u16());
    int val = press.read_u16();
    if (val == MAX && playing) {
        playing = false;
        fclose(wav_file);
    }

    if (THRESHOLD_1 <= val && val < MAX && !playing) {
        wav_open("/sd/hogehoge.wav");
        playing = true;
    }

    if (THRESHOLD_2 <= val && val < THRESHOLD_1 && !playing) {
        wav_open("/sd/secret-iii-exposure.wav");
        playing = true;
    }

    if (val < THRESHOLD_2 && !playing) {
        wav_open("/sd/re-paradox.wav");
        playing = true;
    }
}

int main(void) {
    flipper.attach(&change_music, 0.5);
    while (1) {
        while (playing) {
            waver.play(wav_file);
        }
   }
}
