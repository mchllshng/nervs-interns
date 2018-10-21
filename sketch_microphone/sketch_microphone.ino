#include <Time.h>

const int sensorPinA = A0;
const int sensorPinB = A1;
const int digitalPin = 7;

const int THRESHOLD = 3;
unsigned long avgA = 0;
unsigned long avgB = 0;

time_t timeA = 0;
time_t timeB = 0;

void setupMic(const int pin, unsigned long &avg) {
  pinMode(pin, INPUT);
  pinMode(digitalPin, INPUT);

  // Determine average value of silence by reading for first second
  // (so stfu when you run this)
  for(int i = 0; i < 1000; i++) {
    // read in a value
    avg += analogRead(pin);
    delay(1);
  }
  avg /= 1000;
  Serial.println(String(pin) + " room average: " + String(avg));
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  setupMic(sensorPinA, avgA);
  setupMic(sensorPinB, avgB);
}

bool sensorLoop(const int pin, unsigned long &avg, time_t &timeVal) {
  time_t newTime;
  int diff = abs(avg - analogRead(pin));
  if (diff > THRESHOLD) {
    newTime = micros();
    if (newTime - timeVal > 1000000) {
      timeVal = newTime;
      /*Serial.println(String(pin) + " level: " + String(diff));
      Serial.println(String(pin) + " time: " + String(newTime) + " ms");
      Serial.println(String(pin) + " timediff: " + String(newTime - timeVal) + " ms");*/
      return true;
    }
  }
  return false;
}

void loop() {
  // sensorB loop
  bool heardA = sensorLoop(sensorPinA, avgA, timeA);
  bool heardB = sensorLoop(sensorPinB, avgB, timeB);
  if (heardA || heardB) {
    long timeDiff = (long) timeA - (long) timeB;
    if (abs(timeDiff) < 10000) {
      Serial.println("diff: " + String(timeDiff) + " us");
      if (!heardB) {
        Serial.println("only heard A.");
      } else if (!heardA) {
        Serial.println("only heard B.");
      } else {
      }
    }
  }
  
}
