#include<SoftwareSerial.h>

int dir1pinA = 7;
int dir2pinA = 8;
int speedA = 9;
int dir1pinB = 12;
int dir2pinB = 13;
int speedB = 5;

void setup(){
  Serial.begin(9600);
  pinMode(dir1pinA, OUTPUT);
  pinMode(dir2pinA, OUTPUT);
  pinMode(speedA, OUTPUT);
  pinMode(dir1pinB, OUTPUT);
  pinMode(dir2pinB, OUTPUT);
  pinMode(speedB, OUTPUT);
}

void loop(){
  // 직진 상황
  digitalWrite(dir1pinA, LOW);
  digitalWrite(dir2pinA, HIGH);
  analogWrite(speedA, 100);
  digitalWrite(dir1pinB, LOW);
  digitalWrite(dir2pinB, HIGH);
  analogWrite(speedB, 200);

  // Scenario
  if(Serial.available()){
    char Data = (char)Serial.read();
    // Scenario 1
    if(Data == '1'){
      digitalWrite(dir1pinA, LOW);
      digitalWrite(dir2pinA, HIGH);
      analogWrite(speedA,250);
      digitalWrite(dir1pinB, HIGH);
      digitalWrite(dir2pinB, LOW);
      analogWrite(speedA,200);
      delay(3000);

      digitalWrite(dir1pinA, LOW);
      digitalWrite(dir2pinA, HIGH);
      analogWrite(speedA, 100);
      digitalWrite(dir1pinB, LOW);
      digitalWrite(dir2pinB, HIGH);
      analogWrite(speedB, 200);
      delay(5000);

      digitalWrite(dir1pinA, HIGH);
      digitalWrite(dir2pinA, LOW);
      analogWrite(speedA, 100);
      digitalWrite(dir1pinB, LOW);
      digitalWrite(dir2pinB, HIGH);
      analogWrite(speedB,250);
      delay(3000);

      digitalWrite(dir1pinA, LOW);
      digitalWrite(dir2pinA, LOW);
      analogWrite(speedA, 0 );
      digitalWrite(dir1pinB, LOW);
      digitalWrite(dir2pinB, LOW);
      analogWrite(speedB, 0);
    }
    // Scenario 2
    else if(Data == '2'){
      
      digitalWrite(dir1pinA, LOW);
      digitalWrite(dir2pinA, HIGH);
      analogWrite(speedA, 50);
      digitalWrite(dir1pinB, LOW);
      digitalWrite(dir2pinB, HIGH);
      analogWrite(speedB, 150);

      delay(1000);
      digitalWrite(dir1pinA, HIGH);
      digitalWrite(dir2pinA, HIGH);
      analogWrite(speedA, 150);
      digitalWrite(dir1pinB, HIGH);
      digitalWrite(dir2pinB, HIGH);
      analogWrite(speedB, 150);

      delay(8000);

    }
    // Scenario 3
    else{
      digitalWrite(dir1pinA, LOW);
      digitalWrite(dir2pinA, HIGH);
      analogWrite(speedA, 100);
      digitalWrite(dir1pinB, LOW);
      digitalWrite(dir2pinB, HIGH);
      analogWrite(speedB, 200);
    }
  }
}
