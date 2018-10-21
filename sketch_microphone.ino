const int sensorPin = A0;
const int digitalPin = 7;

const int THRESHOLD = 3;
unsigned long avgVal = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  pinMode(digitalPin, INPUT);

  // Determine average value of silence by reading for first second
  // (so stfu when you run this)
  for(int i = 0; i < 1000; i++) {
    // read in a value
    avgVal += analogRead(sensorPin);
    delay(1);
  }
  avgVal /= 1000;
  Serial.println("Room average found: " + String(avgVal));
}

void loop() {
  int diff = abs(avgVal - analogRead(sensorPin));
  if (diff > THRESHOLD) {
    Serial.println("im talkin here: " + String(diff));
  }
  
}
