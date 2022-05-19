#include <SoftwareSerial.h>
#include <String.h>
#define RXD2 17
#define TXD2 16

const int Pin = 34;
int value = 0;

void setup() {
    // put your setup code here, to run once:
    Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
    Serial.begin(115200);
    Serial.println("Serial Txd is on pin: "+String(TXD2));
    Serial.println("Serial Rxd is on pin: "+String(RXD2));
  
    Serial2.println("AT+CGDCONT=1,\"IP\",\"v-connect\"");     
    delay(2000);
    Serial2.println("AT+HTTPINIT");  //Khoi tao http
    delay(1000);
}

void loop() {
    // put your main code here, to run repeatedly:
    //doc ADC
    value = analogRead(Pin);
    delay(1000);
    Serial.print("value = ");
    Serial.println(value);
  
    //http
    Serial2.println("AT+HTTPINIT");  //Khoi tao http
    delay(1000); 

    String str="AT+HTTPPARA=\"URL\",\"https://api.thingspeak.com/update?api_key=0IQVK88LQ1BNLHRK&field1=" + String(value)+"\"";
    Serial.println(str);
    Serial2.println(str);
    while(Serial2.available()<0);
    String res = Serial2.readStringUntil('\n');
    Serial.println(res);
    delay(1000);

    Serial2.println("AT+HTTPACTION=0");
    delay(5000); 


}
