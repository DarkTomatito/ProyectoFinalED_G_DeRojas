#include <SPI.h>
#include <MFRC522.h>
String nuid;
#define RST_PIN         9          
#define SS_PIN          10         

MFRC522 rfid(SS_PIN, RST_PIN);
byte nuidPICC[4];
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  while (!Serial);    
  SPI.begin();      
  rfid.PCD_Init(); // Init MFRC522
}

void loop() {
  // put your main code here, to run repeatedly:
  int p1 = digitalRead(3);
  int p2 = digitalRead(6);
  int p3 = digitalRead(5);
  int p4 = digitalRead(4);
  int valor = analogRead(A0);
  valor = map(valor,0,1023,0,360);
  Serial.print(p1);
  Serial.print(",");
  Serial.print(p2);
  Serial.print(",");
  Serial.print(p3);
  Serial.print(",");
  Serial.print(p4);
  Serial.print(",");
  Serial.print(valor);
  Serial.print(",");
  Serial.println(nuid);
  if(valor <= 272 && valor >= 268)
  {
    digitalWrite(8,HIGH);
  }
  if ( ! rfid.PICC_IsNewCardPresent())
    {
      nuid = "";
    }

  if ( ! rfid.PICC_ReadCardSerial())
    return;

  if (rfid.uid.uidByte[0] != nuidPICC[0] || 
    rfid.uid.uidByte[1] != nuidPICC[1] || 
    rfid.uid.uidByte[2] != nuidPICC[2] || 
    rfid.uid.uidByte[3] != nuidPICC[3] ) {

    // Store NUID into nuidPICC array
    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = rfid.uid.uidByte[i];
      nuid = nuid + String(nuidPICC[i]);
      digitalWrite(7,HIGH);
      }
    }
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
