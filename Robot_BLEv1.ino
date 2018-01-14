//********************************************
//* Robotic Arm with BLE control v1
//*
//* By Benny Lo
//* Jan 14 2018
//********************************************
#include <CurieBLE.h>
#include <Servo.h>  
Servo myservoA;  
Servo myservoB;
Servo myservoC;
Servo myservoD;
Servo myservoE;
Servo myservoF;
Servo myservoG;//the craw
int i,pos,myspeed;
int sea,seb,sec,sed,see,sef,seg;

BLEPeripheral blePeripheral;//create peripheral instance
BLEService BrobotService("47452000-0f63-5b27-9122-728099603712");//BLE service
//characteristics for the servo motors
BLECharCharacteristic BLE_ServoA("47452001-0f63-5b27-9122-728099603712", BLERead | BLEWrite);
BLECharCharacteristic BLE_ServoB("47452002-0f63-5b27-9122-728099603712", BLERead | BLEWrite);
BLECharCharacteristic BLE_ServoC("47452003-0f63-5b27-9122-728099603712", BLERead | BLEWrite);
BLECharCharacteristic BLE_ServoD("47452004-0f63-5b27-9122-728099603712", BLERead | BLEWrite);
BLECharCharacteristic BLE_ServoE("47452005-0f63-5b27-9122-728099603712", BLERead | BLEWrite);
BLECharCharacteristic BLE_ServoF("47452006-0f63-5b27-9122-728099603712", BLERead | BLEWrite);
BLECharCharacteristic BLE_ServoG("47452008-0f63-5b27-9122-728099603712", BLERead | BLEWrite);
BLECharCharacteristic BLE_Reset("47452007-0f63-5b27-9122-728099603712",  BLEWrite);

void myservosetup()  //set up the servo motors
{
   sea=myservoA.read();
   seb=myservoB.read();
   sec=myservoC.read();
   sed=myservoD.read();
   see=myservoE.read();
   sef=myservoF.read();
   seg=myservoG.read();
   
   myspeed=500;
   for(pos=0;pos<=myspeed;pos+=1)
   {
    myservoA.write(int(map(pos,1,myspeed,sea,50)));
    myservoB.write(int(map(pos,1,myspeed,seb,90)));
    myservoC.write(int(map(pos,1,myspeed,sec,80)));
    myservoD.write(int(map(pos,1,myspeed,sed,90)));
    myservoE.write(int(map(pos,1,myspeed,see,66)));
    myservoF.write(int(map(pos,1,myspeed,sef,90)));
    myservoG.write(int(map(pos,1,myspeed,sef,90)));    
    delay(1);
   }
}

void setup() 
{ 
  Serial.begin(9600);
  //pinMode(13, OUTPUT);   LED control
  
  myservoA.attach(2);  
  myservoB.attach(3); 
  myservoC.attach(4); 
  myservoD.attach(5); 
  myservoE.attach(6); 
  myservoF.attach(7);
  myservoG.attach(8); 
  
  myservoA.write(66);
  myservoB.write(10);
  myservoC.write(50);
  myservoD.write(30);
  myservoE.write(120);
  myservoF.write(90); 
  myservoG.write(90);    
  // set the local name peripheral advertises
  blePeripheral.setLocalName("BRobot");
  // set the UUID for the service this peripheral advertises
  blePeripheral.setAdvertisedServiceUuid(BrobotService.uuid());

  // add service and characteristic
  blePeripheral.addAttribute(BrobotService);
  blePeripheral.addAttribute(BLE_ServoA);
  blePeripheral.addAttribute(BLE_ServoB);
  blePeripheral.addAttribute(BLE_ServoC);
  blePeripheral.addAttribute(BLE_ServoD);
  blePeripheral.addAttribute(BLE_ServoE);
  blePeripheral.addAttribute(BLE_ServoF);
  blePeripheral.addAttribute(BLE_ServoG);
  blePeripheral.addAttribute(BLE_Reset);

  // assign event handlers for connected, disconnected to peripheral
  blePeripheral.setEventHandler(BLEConnected, blePeripheralConnectHandler);
  blePeripheral.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);

  // assign event handlers for characteristic
  BLE_ServoA.setEventHandler(BLEWritten, ServoACharacteristicWritten);
  BLE_ServoB.setEventHandler(BLEWritten, ServoBCharacteristicWritten);
  BLE_ServoC.setEventHandler(BLEWritten, ServoCCharacteristicWritten);
  BLE_ServoD.setEventHandler(BLEWritten, ServoDCharacteristicWritten);
  BLE_ServoE.setEventHandler(BLEWritten, ServoECharacteristicWritten);
  BLE_ServoF.setEventHandler(BLEWritten, ServoFCharacteristicWritten);
  BLE_ServoG.setEventHandler(BLEWritten, ServoFCharacteristicWritten);
  BLE_Reset.setEventHandler(BLEWritten, ResetCharacteristicWritten);
  
// set an initial value for the characteristic
  BLE_ServoA.setValue(50);
  BLE_ServoB.setValue(10);
  BLE_ServoC.setValue(80);
  BLE_ServoD.setValue(30);
  BLE_ServoE.setValue(66);
  BLE_ServoF.setValue(90);
  BLE_ServoG.setValue(90);

  // advertise the service
  blePeripheral.begin();
  Serial.println(("Bluetooth device active, waiting for connections..."));

}

void loop() 
{ 
 //Serial.println("Loop");
  blePeripheral.poll();
   
  i=10;
  myservosetup();
 /*while (i>0)
  {
    myservoA.write(20);
    delay(1000);
    myservoA.write(50);
    delay(1000);
    myservoA.write(70);
    delay(1000);
    myservoB.write(10);
    delay(1000);
    myservoB.write(90);
    delay(1000);
    myservoC.write(90);
    delay(1000);
    myservoC.write(50);
    delay(1000);
    myservoD.write(50);
    delay(1000);
    myservoD.write(90);
    delay(1000);
    myservoE.write(50);
    delay(1000);
    myservoE.write(90);
    delay(1000);
    myservoF.write(50);
    delay(1000);
    myservoF.write(90);
    delay(1000);
    i--;
  }
  while (1);*/
  while (1)
  {
    delay(100);
  }
}

void blePeripheralConnectHandler(BLECentral& central) {
  // central connected event handler
  Serial.print("Connected event, central: ");
  Serial.println(central.address());
}

void blePeripheralDisconnectHandler(BLECentral& central) {
  // central disconnected event handler
  Serial.print("Disconnected event, central: ");
  Serial.println(central.address());
  myservosetup();//return to original position
}

void ServoACharacteristicWritten(BLECentral& central, BLECharacteristic& characteristic) {
  // central wrote new value to characteristic, update LED
  Serial.print("ServoA Control: ");
  myservoA.write((byte)BLE_ServoA.value());
  Serial.println((byte)BLE_ServoA.value(),DEC);
}

void ServoBCharacteristicWritten(BLECentral& central, BLECharacteristic& characteristic) {
  // central wrote new value to characteristic, update LED
  Serial.print("ServoB Control: ");
  myservoB.write((byte)BLE_ServoB.value());
  Serial.println((byte)BLE_ServoB.value(),DEC);
}
void ServoCCharacteristicWritten(BLECentral& central, BLECharacteristic& characteristic) {
  // central wrote new value to characteristic, update LED
  Serial.print("ServoC Control: ");
  myservoC.write((byte)BLE_ServoC.value());
  Serial.println((byte)BLE_ServoC.value(),DEC);
}
void ServoDCharacteristicWritten(BLECentral& central, BLECharacteristic& characteristic) {
  // central wrote new value to characteristic, update LED
  Serial.print("ServoD Control: ");
  myservoD.write((byte)BLE_ServoD.value());
  Serial.println((byte)BLE_ServoD.value(),DEC);
}

void ServoECharacteristicWritten(BLECentral& central, BLECharacteristic& characteristic) {
  // central wrote new value to characteristic, update LED
  Serial.print("ServoE Control: ");
  myservoE.write((byte)BLE_ServoE.value());
  Serial.println((byte)BLE_ServoE.value(),DEC);
}

void ServoFCharacteristicWritten(BLECentral& central, BLECharacteristic& characteristic) {
  // central wrote new value to characteristic, update LED
  Serial.print("ServoF Control: ");
  myservoF.write((byte)BLE_ServoF.value());
  Serial.println((byte)BLE_ServoF.value(),DEC);
}

void ServoGCharacteristicWritten(BLECentral& central, BLECharacteristic& characteristic) {
  // central wrote new value to characteristic, update LED
  Serial.print("ServoG Control: ");
  myservoG.write((byte)BLE_ServoG.value());
  Serial.println((byte)BLE_ServoG.value(),DEC);
}

void ResetCharacteristicWritten(BLECentral& central, BLECharacteristic& characteristic) {
  // Reset - back to original position
  Serial.println("Reset");
  myservosetup();//return to original position
}
