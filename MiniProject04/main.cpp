#include "../Resources/adafruit/HT1632/HT1632.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "icons.c"

/* 
This demo outputs the data fed into stdin to the HT1632 for the 16x24 LED matrix
*/

#define BANK 1
#define DATA 28 //1_28
#define WR 17 //1_17
#define CS 16 //1_16

unsigned char data[48];

main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Wrong number of arguments %d\n", argc);
    return 1;
  } else {
    printf("Starting...\n");
    HT1632LEDMatrix matrix = HT1632LEDMatrix(BANK, DATA, WR, CS);
    matrix.begin(HT1632_COMMON_16NMOS);
    
    printf("Clear\n");
    matrix.clearScreen();
    int i = 0;
    char *token = strtok(argv[1], " ");
    while (token && i < 48) {
      sscanf(token, "%hhu", &data[i++]);
      token = strtok(NULL, " ");
    }
    printf("Drawing\n");
    matrix.drawBitmap(0, 0, data, matrix.width(), matrix.height(), 1);  
    matrix.writeScreen();
    printf("Done!\n");
    return 0;
  }
}
