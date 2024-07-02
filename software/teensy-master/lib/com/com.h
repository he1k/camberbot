#ifndef PID_H
#define PID_H

#include <Arduino.h>

// Miscellaneous
#define BUF_SIZE 256
#define DAT_SIZE 8

// Commands
#define CMD_VOID 0x00
// Ascii 
#define ASCII_LINE_FEED 0x0A

class Com
{
  private:
    uint8_t bfr[BUF_SIZE];
    uint16_t bfr_idx;
    uint8_t command;
    float dat[DAT_SIZE];
    bool pending;
    void parseCommand(); // Function is called internally
  public:
    Com();
    void begin();
    void serialISR();

};

#endif