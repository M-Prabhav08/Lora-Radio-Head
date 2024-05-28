#include <Console.h>
#include <Process.h>
#include <SPI.h>
#include <RH_RF95.h>

RH_RF95 rf95;

char DeviceID[25] = "Transrecv";

//void receivepacket();
//int count = 1;
void setup()
{
  Serial.begin(9600);
  while (!Serial);

  if (!rf95.init())
  {
    Serial.println("Starting LoRa failed!"); 
    while (1);  
  }
  Serial.println("Ready to send");
  rf95.setFrequency(865);
  rf95.setSpreadingFactor(12);
  rf95.setSignalBandwidth(125E3);
  rf95.setCodingRate4(8);
  rf95.setTxPower(20, false);
}

void loop()
{
  Serial.println("Starting to send!");
  uint8_t data[] = "Hi from transRecv";
  rf95.send(data, sizeof(data));
 // Serial.print("Transrecv sent data size : ", sizeof(data));
  rf95.waitPacketSent();
  //sentPackets++;
   //count++;
  //receivepacket();

  if (rf95.available())
  {
   Serial.println("yu are inside recv ");
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    if (rf95.recv(buf, &len))
    {
      Serial.print("Received: ");
      Serial.println((char *)buf);
     //  Serial.print(" recv data size : ", len);
   //   float currentSNR = rf95.lastSNR();
     // float averageSNR = currentSNR;
     
    //  Serial.print("SNR: ");
     // Serial.print(currentSNR);
   
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
      Serial.println("%");*/
    }
  }
   
 // delay(40); 
}

/*
void receivepacket()
{
  
  if (rf95.available())
  {
    Serial.println("yu are inside recv ");
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    if (rf95.recv(buf, &len))
    {
      Serial.print("Received: ");
      Serial.println((char *)buf);
     //  Serial.print(" recv data size : ", len);
      float currentSNR = rf95.lastSNR();
     // float averageSNR = currentSNR;
     
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