#include "com.h"

Com::Com()
{

}
void Com::begin()
{
  for(int i = 0; i < BUF_SIZE; i++){
    this->bfr[i] = 0;
    if(i < DAT_SIZE)
    {
      this->dat[i] = 0.0;
    }
  }
  this->command = CMD_VOID;
  this->pending = false;
  this->bfr_idx = 0;
}
void Com::serialISR()
{
  //if(this->bfr_idx < BUF_SIZE)
  if(!this->pending && (this->bfr_idx < BUF_SIZE))
  {
    while (Serial.available()) 
    {
      //Serial.println(this->bfr_idx);
      uint8_t b = Serial.read();
      this->bfr[this->bfr_idx] = b;
      bfr_idx++;
      if(b == ASCII_LINE_FEED)
      {
        this->parseCommand();
      }
    }
  }
}

void Com::parseCommand(){

}