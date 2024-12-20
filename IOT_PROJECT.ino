#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <WiFiClient.h> 
#include <NTPClient.h>
#include <TimeLib.h>
#include <WiFiUdp.h>
char auth[] = "nzMFzoFHkjmasHuRDg2dmvBvzfUkL4S-";
char ssid[] = "Projectstartup"; 
char pass[] = "GOGOStartup24";  

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "time.nist.gov", 7 * 3600, 60000);
char dayWeek [7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
unsigned long unix_epoch;
char dateMsg[64];
char timeMsg[64];

BlynkTimer timer;
#define relay1 D0
#define relay2 D1

WidgetLED LED1 (V3);
WidgetLED LED2 (V4);

BLYNK_WRITE(V1)
{
  int pinValue = param.asInt();
  if (pinValue == 1) {
    digitalWrite(relay1, LOW); 
    Serial.println("Relay is ON");
    LED1.on();
  } else {
    digitalWrite(relay1, HIGH);   
    Serial.println("Relay is OFF");
     LED1.off();
  }
}

BLYNK_WRITE(V2)
{
  int pinValue = param.asInt();
  if (pinValue == 1) {
    digitalWrite(relay2, LOW); 
    Serial.println("Relay is ON");
    LED2.on();
  } else {
    digitalWrite(relay2, HIGH);   
    Serial.println("Relay is OFF");
     LED2.off();
  }
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass, "blynk.iot-cm.com", 8080);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  timeClient.begin();
}
void loop() {
    timeClient.update();
    unix_epoch = timeClient.getEpochTime();   // get UNIX Epoch time
    Blynk.run(); 
    timer.run();
    
      //##### ON - OFF LIGHT LED SET At TIME #####
      //LED
      if (hour(unix_epoch) == 18 && minute(unix_epoch) == 30 && second(unix_epoch) == 00)
      { 
        digitalWrite(relay1, LOW);
        Blynk.virtualWrite(V1, 1);
      }
      if (hour(unix_epoch) == 4 && minute(unix_epoch) == 30 && second(unix_epoch) == 00 )
      { 
        digitalWrite(relay1, HIGH);
        Blynk.virtualWrite(V1, 0);
      }
      
      //PUMP ตอนเช้า
      if (hour(unix_epoch) == 6 && minute(unix_epoch) == 30 && second(unix_epoch) == 00)
      { 
        digitalWrite(relay2, LOW);
        Blynk.virtualWrite(V2, 1);
      }
      if (hour(unix_epoch) == 6 && minute(unix_epoch) == 45 && second(unix_epoch) == 00 )
      { 
        digitalWrite(relay2, HIGH);
        Blynk.virtualWrite(V2, 0);
      }
      
      //PUMP ตอนเย็น
      if (hour(unix_epoch) == 17 && minute(unix_epoch) == 30 && second(unix_epoch) == 00)
      { 
        digitalWrite(relay2, LOW);
        Blynk.virtualWrite(V2, 1);
      }
      if (hour(unix_epoch) == 17 && minute(unix_epoch) == 45 && second(unix_epoch) == 00 )
      { 
        digitalWrite(relay2, HIGH);
        Blynk.virtualWrite(V2, 0);
      }
}
