#include <SoftwareSerial.h>
// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library
#include <SPI.h>

#define xPin A3
#define yPin A4
#define zPin A5

const int samples = 10;
int Sms_1 = 0;
int Sms_2 = 0;
int Sms_3 = 0;
int Sms_4 = 0;
int Sms_5 = 0;

// Create Amplitude Shift Keying Object
RH_ASK rf_driver;
SoftwareSerial mySerial(9, 10);

void setup() {
  // Initialize ASK Object
  Serial.begin(115200);
  mySerial.begin(9600);
  rf_driver.init();

  mySerial.println("AT");
  updateSerial();
}

void loop() {
  int xRaw = 0, yRaw = 0, zRaw = 0;
  for (int i = 0; i < samples; i++) {
    xRaw += analogRead(xPin);
    yRaw += analogRead(yPin);
    zRaw += analogRead(zPin);
  }
  xRaw /= samples;
  yRaw /= samples;
  zRaw /= samples;
  if ((xRaw > 330 && xRaw < 344) && (yRaw > 329 && yRaw < 335) && (zRaw > 398 && zRaw < 412)) {
    Sms_2 = 0;
    Sms_3 = 0;
    Sms_4 = 0;
    Sms_5 = 0;
    const char *msg = "Am Ok";
    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
    delay(1000);
    if (Sms_1 == 0) {
      mySerial.println("AT+CMGF=1");  // Configuring TEXT mode
      updateSerial();
      mySerial.println("AT+CMGS=\"+254748613509\"");
      updateSerial();
      mySerial.print("Am Ok");
      updateSerial();
      mySerial.write(26);
      Sms_1 = 1;
    }

  } else if ((xRaw > 335 && xRaw < 355) && (yRaw > 250 && yRaw < 280)) {
    Sms_1 = 0;
    Sms_3 = 0;
    Sms_4 = 0;
    Sms_5 = 0;
    const char *msg = "Hello There!";
    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
    delay(1000);
    if (Sms_2 == 0) {
      mySerial.println("AT+CMGF=1");  // Configuring TEXT mode
      updateSerial();
      mySerial.println("AT+CMGS=\"+254748613509\"");
      updateSerial();
      mySerial.print("Hello There!");
      updateSerial();
      mySerial.write(26);
      Sms_2 = 1;
    }
  } else if ((xRaw > 400 && xRaw < 410) && (yRaw > 325 && yRaw < 335)) {
    Sms_1 = 0;
    Sms_2 = 0;
    Sms_4 = 0;
    Sms_5 = 0;
    const char *msg = "Move to the Right";
    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
    delay(1000);
    if (Sms_3 == 0) {
      mySerial.println("AT+CMGF=1");  // Configuring TEXT mode
      updateSerial();
      mySerial.println("AT+CMGS=\"+254748613509\"");
      updateSerial();
      mySerial.print("Move to the Right");
      updateSerial();
      mySerial.write(26);
      Sms_3 = 1;
    }
  } else if ((xRaw > 270 && xRaw < 280) && (yRaw > 325 && yRaw < 336)) {
    Sms_1 = 0;
    Sms_2 = 0;
    Sms_3 = 0;
    Sms_5 = 0;
    const char *msg = "Move to the Left";
    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
    delay(1000);
    if (Sms_4 == 0) {
      mySerial.println("AT+CMGF=1");  // Configuring TEXT mode
      updateSerial();
      mySerial.println("AT+CMGS=\"+254748613509\"");
      updateSerial();
      mySerial.print("Move to the Left");
      updateSerial();
      mySerial.write(26);
      Sms_4 = 1;
    }
  } else if ((xRaw > 330 && xRaw < 344) && (yRaw > 329 && yRaw < 335) && (zRaw > 265 && zRaw < 278)) {
    Sms_1 = 0;
    Sms_2 = 0;
    Sms_3 = 0;
    Sms_4 = 0;
    const char *msg = "Am Done";
    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
    delay(1000);
    if (Sms_5 == 0) {
      mySerial.println("AT+CMGF=1");  // Configuring TEXT mode
      updateSerial();
      mySerial.println("AT+CMGS=\"+254748613509\"");
      updateSerial();
      mySerial.print("Am Done"); 
      updateSerial();
      mySerial.write(26);
      Sms_5 = 1;
    }
  }

  //delay(200);

  Serial.print(xRaw);
  Serial.print("\t");
  Serial.print(yRaw);
  Serial.print("\t");
  Serial.print(zRaw);
  Serial.println();

  delay(200);
}
void updateSerial() {
  delay(500);
  while (Serial.available()) {
    mySerial.write(Serial.read());  //Forward what Serial received to Software Serial Port
  }
  while (mySerial.available()) {
    Serial.write(mySerial.read());  //Forward what Software Serial received to Serial Port
  }
}