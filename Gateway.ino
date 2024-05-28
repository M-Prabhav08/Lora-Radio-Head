//#include <Console.h>
#include <Process.h>
#include <SPI.h>
#include <RH_RF95.h>

RH_RF95 rf95;

char DeviceID[25] = "GATEX001";

//unsigned long receivedPackets = 0;
//unsigned long sentPackets = 0;

//void receivepacket();

void setup()
{
  Serial.begin(9600);
  while (!Serial);

  if (!rf95.init())
  {
    Serial.println("Starting LoRa failed!");
    Serial.print(",");
    while (1);
  }
  Serial.println("Ready to Recv!,");
  //Serial.print(",");
  rf95.setFrequency(865);
  rf95.setSpreadingFactor(12);
  rf95.setSignalBandwidth(125E3);
  rf95.setCodingRate4(8);
  rf95.setTxPower(20, false);
}

void loop()
{
 // receivepacket();
  if (rf95.available())
  {
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    if (rf95.recv(buf, &len))
    {
      Serial.print("Received: ");
      Serial.print((char *)buf);
      Serial.println(",");

      // Calculate and print SNR
      float currentSNR = rf95.lastSNR();
      //float averageSNR = currentSNR;

      Serial.print("SNR: ");
      Serial.print(currentSNR);
      Serial.println(",");
      Serial.print("RSSI: ");
      Serial.print(rf95.lastRssi(), DEC);
      Serial.println(",");
    }
      uint8_t data[] = "Hi from gateway. This is the payload from gateway";
      rf95.send(data, sizeof(data));
      rf95.waitPacketSent();
  }
  //sentPackets++;

  // Add a delay if needed to control the loop frequency
 //delay(5000); // Adjust the delay duration as needed
}
/*
void receivepacket()
{
  if (rf95.available())
  {
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    if (rf95.recv(buf, &len))
    {
      Serial.print("Received: ");
      Serial.println((char *)buf);

      // Calculate and print SNR
      float currentSNR = rf95.lastSNR();
      float averageSNR = currentSNR;

      Serial.print("SNR: ");
      Serial.print(currentSNR);

      Serial.println(rf95.lastRssi(), DEC);
      /*
      receivedPackets++;
      float packetLoss = 100.0 * (1.0 - (float)receivedPackets / sentPackets);

      Serial.print("Sent Packets: ");
      Serial.print(sentPackets);
      Serial.print(", Received Packets: ");
      Serial.print(receivedPackets);
      Serial.print(", Packet Loss: ");
      Serial.print(packetLoss);
      Serial.println("%");
    }
  }
}*/
