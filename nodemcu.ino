// nodemcu
// AT+UART_DEF=9600,8,1,0,0
// #define BLYNK_PRINT Serial
// #define BlynkTimer timer; // Announcing the timer

/* Fill-in your Template ID (only if using Blynk.Cloud) */
#define BLYNK_TEMPLATE_ID "TMPL6KdbIgawS"
#define BLYNK_TEMPLATE_NAME "BusstopCooler2"
#define BLYNK_AUTH_TOKEN "bz-yFhnAm7QWDK443r-AURpzxpDOv1JW"

// Blynk && Serial 
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>
#include <DHT.h>
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "1"; // WIFI ID
char pass[] = "qhdks001!"; // WIFI PASSWOARD

//pin번호 정의
int tempPin = D4;
int humiPin = D5;
// 변수 정의
float temp;
float humi;
int tdsValue;
int motor1;
int motor2;

// push를 위한 타이머 인스턴스
BlynkTimer timer;
// 1초마다 Blynk 서버에 정보 전달
void myTimerEvent()
{
    float Discomfort = 1.8 * temp - 0.55 * (1 - humi * 0.01) * (1.8 * temp - 26) + 32;
    Blynk.virtualWrite(V0, temp);
    Blynk.virtualWrite(V1, humi);
    Blynk.virtualWrite(V2, Discomfort);
    Blynk.virtualWrite(V3, motor1);
    Blynk.virtualWrite(V4, motor2);
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
  tdsValue = Serial.readStringUntil('\n').toInt();
  temp = Serial.readStringUntil('\n').toFloat();
  humi = Serial.readStringUntil('\n').toFloat();
  motor1 = Serial.readStringUntil('\n').toInt();
  motor2 = Serial.readStringUntil('\n').toInt();
  delay(200);
}