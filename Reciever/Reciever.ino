#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define enA 3  
#define in1 2
#define in2 4
#define enB 6   
#define in3 5
#define in4 7
 
RF24 radio(8,9); // CE, CSN
const byte address[6] = "00001";
char receivedData[32] = "";
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int joystick[2]; 
int z0 = 3000;
int zstop = 13000;
int y0 = 10000;
 
void setup() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
  
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}
void loop() {
  
  if (radio.available()) {   // If the NRF240L01 module received data
     
    radio.read( joystick, sizeof(joystick) );
 
    radio.read( receivedData, sizeof(receivedData));
    
    AcX = joystick[0];
    AcY = joystick[1];
 
 
// DELETE 
//-----------------------------
 
/*    Serial.print("AcX :");
    Serial.print(AcX);
    Serial.print("    ");
    Serial.print("AcY :");
    Serial.print(AcY);
 
    delay(1000);
//-----------------------------
 */
  
  if(AcX<-10000){      //Forward
    
    Serial.print("    Forward    ");
    digitalWrite(enA, HIGH);
    digitalWrite(enB, HIGH);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
  else if(AcX>10000){  //BACK
    
    Serial.print("    BACK    ");
    digitalWrite(enA, HIGH);
    digitalWrite(enB, HIGH);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, HIGH);
  }
  else if(AcY<-10000 ){        ///LEFT
    
    Serial.print("    LEFT    ");
    digitalWrite(enA, HIGH);
    digitalWrite(enB, HIGH);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  else if(AcY>10000){        //RIGHT
    
    Serial.print("    RIGHT    ");
    digitalWrite(enA, HIGH);
    digitalWrite(enB, HIGH);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  else if(AcX<10000 && AcX>-10000 && AcX<10000 && AcX>-10000 ) {  //Stop
    Serial.print("    Stop   ");
    digitalWrite(enA, LOW);
    digitalWrite(enB, LOW);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
  
  } 
}
