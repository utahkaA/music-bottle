#include "mbed.h"
#include "SDFileSystem.h"
#include "wave_player.h"

#define C 261.626
#define D 293.665
#define E 329.628
#define F 349.228
#define G 391.995
#define A 440.000
#define B 493.883

int main(void) {    
    AnalogIn press(p20);
    AnalogOut speaker(p18);
    // PwmOut speaker(p21);
    SDFileSystem sd(p5, p6, p7, p8, "sd");
    wave_player waver(&speaker);
    
    // float mm[]={C, D, E, F, G, A, B, C*2};
        
    // mkdir("/sd/mydir", 0777);

    FILE *wav_file = fopen("/sd/hogehoge.wav", "r");
    if (wav_file == NULL) {
       error("Could not open file for write\n");
    }
    waver.play(wav_file);
    fclose(wav_file);
       
    while(1) {
        printf("press: %d\n\r", press.read_u16());
        // for (int i = 0; i < sizeof(mm); i++) {
        //     speaker.period(1.0/mm[i]);
        //     speaker.write(0.5f);
        //     wait(0.5f);
        //     speaker.write(0.0f);
        // }
        wait(1);
   }
}
