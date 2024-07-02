#include <Arduino.h>
#include <SPI.h>

volatile bool dataReceived = false;
volatile char receivedData = 0;

const int SS_PIN = 5; // Slave Select pin

// Create an SPIClass instance for the VSPI bus
SPIClass SPI_VSPI(VSPI);

void IRAM_ATTR onReceive() {
  receivedData = SPI_VSPI.transfer(0x00); // Receive data by sending a dummy byte
  dataReceived = true;
}

void setup() {
  Serial.begin(115200);
  pinMode(SS_PIN, INPUT);

  // Initialize the SPI library in slave mode
  SPI_VSPI.begin(18, 19, 23, SS_PIN); // SCLK, MISO, MOSI, SS
  SPI_VSPI.setDataMode(SPI_MODE0); // Set SPI mode
  SPI_VSPI.setClockDivider(SPI_CLOCK_DIV4); // Set clock divider (optional)

  attachInterrupt(digitalPinToInterrupt(SS_PIN), onReceive, FALLING);
}

void loop() {
  if (dataReceived) {
    Serial.print("Received: ");
    Serial.println(receivedData);
    dataReceived = false;
  }
}