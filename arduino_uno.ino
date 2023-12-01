// Arduino 
// LCD header
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
Servo myservo;
LiquidCrystal_I2C lcd(0x27, 16, 2);  //이상하면 0x3F,16,2로 바꾸기

// SoftwareSerial header
//#include <SoftwareSerial.h>
//#include <Wire.h>

//DHT header
#include <DHT.h>

// SoftwareSerial intialization
// pin 번호 선언////////////////////////////////
#define DHTPIN 8           // DHT : 8번 핀 사용
#define DHTTYPE DHT22      // DHT 11  (AM2302), AM2321
//DHT 설정
DHT dht(DHTPIN, DHTTYPE);  // DHT설정 - dht (디지털2, dht11)

const int pinWATER_MOTOR1 = 3;  //저류지모터 : 3번핀
const int pinWATER_MOTOR2 = 4;  //정류장모터(의자) : 4번핀
const int pinWATER_MOTOR3 = 5;  //정류장모터(벽) : 5번핀
const int pinTDS_in = A0;        //tds센서 : 6번핀
const int ENABLE=11;            // 모터1사용 가능 제어핀과 동시에 속도제어핀 역할
const int DIR1=10;               // 방향제어를 위한 핀1
const int DIR2=9;               // 방향제어를 위한 핀2
const int BUTTON = 3;           // 버튼입력으로 사용할 핀
const int POT = A5;             // 가변저항기와 연결한 핀
enum MOTOR_DIRECTION{FOWARD=0, BACKWARD=1};         // 모터의 전방, 후방 여부 확인을 위한 자료형 
  
enum MOTOR_DIRECTION Direction;                     // 모터의 전방, 후방 여부 확인을 위한 자료형 생성

//lcd
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

float temp = 0.0;
float humi = 0.0;
int tdsValue = 0;
float voltage = 0.0;
void setup() {
  Serial.begin(9600);
  delay(100);
  lcd.init();       // Initialize the LCD
  lcd.backlight();  // Turn on the backlight
  lcd.setCursor(3, 1);
  // put your setup code here, to run once:
  pinMode(pinWATER_MOTOR1, OUTPUT);  //저류지 모터
  pinMode(pinWATER_MOTOR2, OUTPUT);  //정류장 모터
  myservo.attach(pinWATER_MOTOR3);

  pinMode(DHTPIN, INPUT);     // 온습도 센서 핀모드
  pinMode(pinTDS_in, INPUT);  // TDS 센서 핀모드

  pinMode(ENABLE, OUTPUT);             // 모터1사용 가능 제어핀 출력으로 설정
  pinMode(DIR1, OUTPUT);               // 방향제어를 위한 핀1 출력으로 설정
  pinMode(DIR2, OUTPUT);              // 방향제어를 위한 핀2 출력으로 설정
  pinMode(BUTTON, INPUT);             // 버튼핀 입력으로 설정
  digitalWrite(ENABLE, LOW);         // 일단 모터가 작동하지 않도록 초기화

  dht.begin();
}

void loop() {

  //TDS 센서
  tdsValue = analogRead(pinTDS_in);
  voltage = tdsValue * 5.0 / 1024.0;
  Serial.println(voltage);

  //DHT
  
  temp = dht.readTemperature();  //온습도 온도 값 저장 변수
  humi = dht.readHumidity();
  delay(1000);
    lcd.clear();  // Clear the display
  lcd.setCursor(0, 0);
  lcd.print("temp: ");
  lcd.setCursor(8, 0);
  lcd.print(float(temp));
  lcd.setCursor(15, 0);
  lcd.print("C");

  Serial.println(tdsValue);
  Serial.println(temp);
  Serial.println(humi);
  //온도와 tds 센서로 저류지 모터 on/off
  if (temp >= 25) {
    if (voltage >= 3.30) {  //Read sensor signal
      analogWrite(pinWATER_MOTOR1, 255);   // 펌프모터 켜기
      analogWrite(pinWATER_MOTOR2, 255);  // 펌프모터 켜기
      myservo.write(180);   //Counterclockwise maximum speed rotation
      Serial.println(1);
      Serial.println(1);
      //Serial.println("first pump water on");
    } else {
      analogWrite(pinWATER_MOTOR1, 0);  // 펌프모터 끄기
      analogWrite(pinWATER_MOTOR2, 0);  // 펌프모터 끄기
      myservo.write(90);  //Counterclockwise maximum speed rotation
      Serial.println(0);
      Serial.println(0);
      //Serial.println("first pump water off");
    }
  }
}