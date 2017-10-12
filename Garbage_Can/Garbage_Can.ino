#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN 6
int pinNum = A0;
int ledNum = 0;
int Sensor_val;   //센서 ADC값 저장 변수
int cm;         // cm값을 저장할 변수 선언
int echoPin = 7;
int trigPin = 8;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(256, PIN, NEO_GRB + NEO_KHZ800); //LED 갯수
 
void setup() {
     Serial.begin(9600);
        pinMode(trigPin, OUTPUT);
        pinMode(echoPin, INPUT);
     #if defined (__AVR_ATtiny85__)
     if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
     #endif
 
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}
 
void loop() {
//적외선 거리 센서로 부터 측정값을 읽어온다
  float duration, distance;
  
  // 초음파를 보낸다. 다 보내면 echo가 HIGH 상태로 대기하게 된다.
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  
  // echoPin 이 HIGH를 유지한 시간을 저장 한다.
  duration = pulseIn(echoPin, HIGH); 
  // HIGH 였을 때 시간(초음파가 보냈다가 다시 들어온 시간)을 가지고 거리를 계산 한다.
  distance = ((float)(340 * duration) / 10000) / 2;  
  
  Serial.print(distance);
  Serial.println("cm");
  dis(distance);
  // 수정한 값을 출력
  delay(500);
  rainbow(30); // 숫자가 작을수록 빠르게 바뀐다
 
}
 
void dis (float a) { 
  if(a<12){
    ledNum=16;
  }else if(a<16){
    ledNum=24;
  }else if(a<20){
    ledNum=32;
  }else if(a<24){
    ledNum=40;
  }else if(a<28){
    ledNum=48;
  }else if(a<32){
    ledNum=56;
  }else{
    ledNum=64;
  }
  
}
 
void rainbow(uint8_t wait) {
  uint16_t i, j, k;
 
  for(j=0; j<256; j++) {
   for(k=ledNum; k<64 ; k++){
    strip.setPixelColor(k, 0,0,0);
   }
    for(i=0; i<ledNum; i++) { // 32는 32칸
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(20);
  }
}
 
 
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
