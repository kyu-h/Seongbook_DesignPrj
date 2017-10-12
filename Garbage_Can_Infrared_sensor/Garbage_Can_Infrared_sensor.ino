#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN 6
int pinNum = A0;
int ledNum = 0;
int Sensor_val;   //센서 ADC값 저장 변수
int cm;         // cm값을 저장할 변수 선언
Adafruit_NeoPixel strip = Adafruit_NeoPixel(256, PIN, NEO_GRB + NEO_KHZ800); //LED 갯수

void setup() {
     Serial.begin(9600);
     pinMode (pinNum, INPUT); 
     #if defined (__AVR_ATtiny85__)
     if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
     #endif

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
//적외선 거리 센서로 부터 측정값을 읽어온다
  Sensor_val = map(analogRead(pinNum), 0, 1023, 0, 5000);  //전압값으로 변경
  cm = (24.61/(Sensor_val-0.1696))*1000;//CM 거리값으로 변경
  Serial.print(cm);// 시리얼 모니터로 거리값 출력
  Serial.print("|");// 시리얼 모니터로 거리값 출력
  distance(cm);  
  Serial.println(  ledNum);// 시리얼 모니터로 거리값 출력
  rainbow(30); // 숫자가 작을수록 빠르게 바뀐다
 
}

void distance (int a) { 
  if(a<13){
    ledNum=16;
  }else if(a<12){
    ledNum=24;
  }else if(a<14){
    ledNum=32;
  }else if(a<16){
    ledNum=40;
  }else if(a<18){
    ledNum=48;
  }else if(a<20){
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
