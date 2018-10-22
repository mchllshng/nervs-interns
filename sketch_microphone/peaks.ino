
const int sensorPinA = A0;
const int sensorPinB = A1;
const int digitalPin = 7;

const int THRESHOLD = 10;
unsigned long avgA = 0;
unsigned long avgB = 0;

unsigned long timeA = 0;
unsigned long timeB = 0;

unsigned long firstTime=0;
unsigned long firstPin=0;


void setupMic(const int pin, unsigned long &avg) {
  pinMode(pin, INPUT);
  pinMode(digitalPin, INPUT);

  // Determine average value of silence by reading for first second
  // (so stfu when you run this)
  for(int i = 0; i < 10; i++) {
    // read in a value
    avg += analogRead(pin);
    delay(1);
  }
  avg /= 10;
  //Serial.println(String(pin) + " room average: " + String(avg));
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  setupMic(sensorPinA, avgA);
  setupMic(sensorPinB, avgB);
}


unsigned const long alpha=1000;
bool readPeak(int sensorPin, unsigned long &avg){
  long value= analogRead(sensorPin);
  if(value > avg + THRESHOLD)
   {
    long zero= avg + THRESHOLD;
    long newvalue= abs(value-zero);

   // Serial.println(0);
   // Serial.println(0);
   // Serial.println(newvalue);
   // Serial.println(0);
   // Serial.println(0);
    avg=10000000;
    return true;
   }
   else{
    avg= (alpha*avg+ value)/(alpha+1);
    return false;
   }

}



void loop() {

  if(readPeak(sensorPinA,avgA)){
    if(firstTime==0)
      {
        firstTime=micros();
        firstPin=sensorPinA;
        }
        else
        {
          long diff= micros()-firstTime;
          if(firstPin==sensorPinA)
            diff*=-1;
          
          Serial.println(0);
          Serial.println(0);  
          //Serial.println("diff: " + String(diff));
          Serial.println(String(diff));
          Serial.println(0);
          Serial.println(0);
          
          firstTime=0;
          }
  }

  
  if(readPeak(sensorPinB,avgB)){
    if(firstTime==0)
      {
        firstTime=micros();
        firstPin=sensorPinB;
        }
        else
        {
          

          long diff= micros()-firstTime;
          if(firstPin==sensorPinA)
            diff*=-1;


           
          Serial.println(0);
          Serial.println(0);  
          //Serial.println("diff: " + String(diff));
          Serial.println(String(diff));
          Serial.println(0);
          Serial.println(0);
          


          firstTime=0;
          
          }
  }


if(firstTime!=0 && micros() > firstTime + 500000){
  firstTime=0;
}
  
  
}