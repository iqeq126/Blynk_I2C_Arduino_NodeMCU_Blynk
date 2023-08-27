// nodemcu
// AT+UART_DEF=9600,8,1,0,0
// #define BLYNK_PRINT Serial
// #define BlynkTimer timer; // Announcing the timer

/* Fill-in your Template ID (only if using Blynk.Cloud) */
#define BLYNK_TEMPLATE_ID "YourID"
#define BLYNK_TEMPLATE_NAME "YourTemplate"
#define BLYNK_AUTH_TOKEN "YourToken"

// Blynk && Serial 
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>
#include <DHT.h>
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "YourID"; // WIFI ID
char pass[] = "YourPW"; // WIFI PASSWOARD

//pin번호 정의
int tempPin = D4;
int humiPin = D5;
// 변수 정의
int temp;
int humi;

// push를 위한 타이머 인스턴스
BlynkTimer timer;
// 1초마다 Blynk 서버에 정보 전달
void myTimerEvent()
{
    Blynk.virtualWrite(V0, temp);
    Blynk.virtualWrite(V1, humi);
}

void setup()
{
  Serial.begin(9600); /* begin serial for debug */
  pinMode(D0, OUTPUT);
  pinMode(tempPin, OUTPUT);
  pinMode(humiPin, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();
  temp = Serial.readStringUntil('\n').toInt();
  humi = Serial.readStringUntil('\n').toInt();
  delay(100);
}