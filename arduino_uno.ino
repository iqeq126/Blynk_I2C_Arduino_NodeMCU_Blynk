// Arduino 
// LCD header
#include <LiquidCrystal.h>

// SoftwareSerial header
#include <SoftwareSerial.h>
#include <Wire.h>

//DHT header
#include <DHT.h>

// SoftwareSerial intialization
// pin 번호 선언////////////////////////////////
#define DHTPIN 8           // DHT : 8번 핀 사용
#define DHTTYPE DHT22      // DHT 11  (AM2302), AM2321
//DHT 설정
DHT dht(DHTPIN, DHTTYPE);  // DHT설정 - dht (디지털2, dht11)

int pinWATER_MOTOR1 = 3;  //저류지모터 : 3번핀
int pinWATER_MOTOR2 = 4;  //정류장모터(의자) : 4번핀

int pinWATER_MOTOR3 = 5;  //정류장모터(벽) : 5번핀
int pinTDS_in = 6;        //tds센서 : 6번핀

//lcd
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int temp = 1;
int humi = 1;

void setup() {
  Serial.begin(9600);
  //soft.begin(9600);  
   //Wire.begin(8);                /* join i2c bus with address 8 */
   //Wire.onReceive(receiveEvent); /* register receive event */
   //Wire.onRequest(requestEvent); /* register request event */

  delay(100);
  lcd.begin(20, 4);
  lcd.setCursor(3, 1);
  // put your setup code here, to run once:
  pinMode(pinWATER_MOTOR1, OUTPUT);  //저류지 모터
  pinMode(pinWATER_MOTOR2, OUTPUT);  //정류장 모터

  pinMode(DHTPIN, INPUT);     // 온습도 센서 핀모드
  pinMode(pinTDS_in, INPUT);  // TDS 센서 핀모드


  //Serial.println("\nI2C Scanner");
  //Serial.println("DHTxx test!");
  dht.begin();
}

void loop() {

  //TDS 센서
  int tdsValue = digitalRead(pinTDS_in);
  //Serial.println(tdsValue);
  //delay(500);
  //DHT
  temp = dht.readTemperature();  //온습도 온도 값 저장 변수
  humi = dht.readHumidity();
  //soft.println(String(temp));
  //soft.println(String(humi));
  Serial.println(temp);
  Serial.println(humi);
  delay(1000);
  //delay(500);
  //온도와 tds 센서로 저류지 모터 on/off
  if (temp >= 20) {
    if (tdsValue == HIGH) {  //Read sensor signal
      analogWrite(3, 255);   // 펌프모터 켜기
      //Serial.println("first pump water on");
    } else {
      analogWrite(3, 0);  // 펌프모터 끄기
      //Serial.println("first pump water off");
    }
  }

  //정류장(벽, 의자)
  if (tdsValue == HIGH) {  //Read sensor signal
    analogWrite(4, 255);   // 펌프모터 켜기
    analogWrite(5, 255);   // 펌프모터 켜기
    //Serial.println("second pump water on");
  } else {
    analogWrite(4, 0);  // 펌프모터 끄기
    analogWrite(5, 0);  // 펌프모터 켜기
    //Serial.println("second pump water off");
  }
}
/*
void receiveEvent(int howMany) {
 while (0 <Wire.available()) {
    char c = Wire.read();      // receive byte as a character 
    Serial.print(c);           // print the character 
  }
 Serial.println();             // to newline 
}
*/
// function that executes whenever data is requested from master
/*void requestEvent() {
 if ( Wire.available() >= 0){
    Serial.println(temp);
    Serial.println(humi);
    Wire.beginTransmission(8);  // Transmit to NodeMCU with address 8
    Wire.write(temp);  // Send data
    Wire.write(humi);  // Send data
    delay(500);
    Wire.endTransmission();   // Stop transmitting
  }
}*/