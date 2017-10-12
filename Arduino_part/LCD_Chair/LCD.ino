int val = 0; // AD 변환값을 저장할 변수
int percent;
int LED = 5;

void setup() {
  Serial.begin(9600); // 시리얼 통신 속도 지정
  pinMode(5, OUTPUT);
}
void loop() {
  val = analogRead(0); // 아날로그 0번 핀(CDS) 값을 입력
  percent = map(val,0,1023,0,100); // 변환된 디지털 값을 %로 변환
  Serial.print("CDS = ");
  Serial.print(percent); // 변환된 디지털 값을 시리얼 모니터로 전송
  Serial.print("\n");
  //analogWrite(5, 255);

  if(percent < 25){
    percent = 0;
    analogWrite(5, percent);
  }else if(percent <50){
    percent = 85;
    analogWrite(5, percent);
  }else if(percent <75){
    percent = 170;
    analogWrite(5, percent);
  }else {
    percent = 255;
    analogWrite(5, percent);
  }
  
  delay(200);
}
