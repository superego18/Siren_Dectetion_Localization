const int soundSensorPinA0 = A0; // A0 핀에 연결된 사운드 감지 센서의 핀을 정의합니다.
const int soundSensorPinA1 = A1; // A1 핀에 연결된 사운드 감지 센서의 핀을 정의합니다.
const int soundSensorPinA2 = A2; // A2 핀에 연결된 사운드 감지 센서의 핀을 정의합니다.
const int soundSensorPinA3 = A3; // A3 핀에 연결된 사운드 감지 센서의 핀을 정의합니다.
const int sampleWindow = 20;     // 샘플링 시간 (예: 3ms, 50ms 등)
unsigned int sampleA0;
unsigned int sampleA1;
unsigned int sampleA2;
unsigned int sampleA3;
unsigned long startTime;
unsigned long sampleCount = 0;
unsigned long sampleRate = 0;

int echo = 8;
int trig = 12;

float getDistance() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH);
  float distance = duration * 0.034 / 2;
  return distance;
}

void setup() {
  Serial.begin(9600); // 시리얼 통신을 초기화합니다.
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {                                                                        
  unsigned long startMillis = millis(); // 샘플링 시작
  unsigned int peakToPeakA0 = 0;       // A0 핀의 음성 신호 진폭
  unsigned int peakToPeakA1 = 0;       // A1 핀의 음성 신호 진폭
  unsigned int peakToPeakA2 = 0;       // A2 핀의 음성 신호 진폭
  unsigned int peakToPeakA3 = 0;       // A3 핀의 음성 신호 진폭

  unsigned int signalMaxA0 = 0;        // A0 핀의 최대 크기 초기화
  unsigned int signalMinA0 = 1024;     // A0 핀의 최소 크기 초기화
  unsigned int signalMaxA1 = 0;        // A1 핀의 최대 크기 초기화
  unsigned int signalMinA1 = 1024;     // A1 핀의 최소 크기 초기화
  unsigned int signalMaxA2 = 0;        // A2 핀의 최대 크기 초기화
  unsigned int signalMinA2 = 1024;     // A2 핀의 최소 크기 초기화
  unsigned int signalMaxA3 = 0;        // A3 핀의 최대 크기 초기화
  unsigned int signalMinA3 = 1024;     // A3 핀의 최소 크기 초기화

  while (millis() - startMillis < sampleWindow) { // 데이터를 sampleWindow(예: 3ms)마다 모으는 while 루프
    sampleA0 = analogRead(soundSensorPinA0);    // A0 핀에서 데이터 읽기
    sampleA1 = analogRead(soundSensorPinA1);    // A1 핀에서 데이터 읽기
    sampleA2 = analogRead(soundSensorPinA2);    // A2 핀에서 데이터 읽기
    sampleA3 = analogRead(soundSensorPinA3);    // A3 핀에서 데이터 읽기

    // A0 핀의 음성 신호 진폭 측정
    if (sampleA0 < 1024) {
      if (sampleA0 > signalMaxA0) {
        signalMaxA0 = sampleA0;
      } else if (sampleA0 < signalMinA0) {
        signalMinA0 = sampleA0;
      }
    }

    // A1 핀의 음성 신호 진폭 측정
    if (sampleA1 < 1024) {
      if (sampleA1 > signalMaxA1) {
        signalMaxA1 = sampleA1;
      } else if (sampleA1 < signalMinA1) {
        signalMinA1 = sampleA1;
      }
    }

    // A2 핀의 음성 신호 진폭 측정
    if (sampleA2 < 1024) {
      if (sampleA2 > signalMaxA2) {
        signalMaxA2 = sampleA2;
      } else if (sampleA2 < signalMinA2) {
        signalMinA2 = sampleA2;
      }
    }

    // A3 핀의 음성 신호 진폭 측정
    if (sampleA3 < 1024) {
      if (sampleA3 > signalMaxA3) {
        signalMaxA3 = sampleA3;
      } else if (sampleA3 < signalMinA3) {
        signalMinA3 = sampleA3;
      }
    }
  } 

  peakToPeakA0 = signalMaxA0 - signalMinA0; // A0 핀의 진폭
  peakToPeakA1 = signalMaxA1 - signalMinA1; // A1 핀의 진폭
  peakToPeakA2 = signalMaxA2 - signalMinA2; // A2 핀의 진폭
  peakToPeakA3 = signalMaxA3 - signalMinA3; // A3 핀의 진폭

  float distance = getDistance();

  // A0, A1, A2, A3 핀의 진폭을 시리얼 모니터에 출력
  Serial.print(peakToPeakA0);
  Serial.print(',');
  Serial.print(peakToPeakA1);
  Serial.print(',');
  Serial.print(peakToPeakA2);
  Serial.print(',');
  Serial.print(peakToPeakA3);
  Serial.print(',');
  Serial.println(distance);
}
