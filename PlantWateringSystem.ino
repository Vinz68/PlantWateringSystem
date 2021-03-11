#define ANA A0
#define DIGI D5
#define POMPOUT D6

double analogValue = 0.0;
int digitalValue = 0;
double analogVolts = 0.0;
unsigned long timeHolder = 0;

unsigned int counter = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Plant_watering_system Setup");

  // Analog input for moisture sensor (0 for wet and 1023 for dry)
  pinMode(ANA, INPUT);

  // Digital input moisture sensor (LOW for wet and HIGH for dry)
  pinMode(DIGI, INPUT);

  // Output to drive the motor (on/off)
  pinMode(POMPOUT, OUTPUT);

}
void loop() {
  // Read moisture sensor values (analog and digital inputs)
  analogValue = analogRead(ANA);
  digitalValue = digitalRead(DIGI);

  outputToSerialMonitor();

  // 0 for wet and 1023 for dry
  if (analogValue > 800) {
    if (counter == 0)
      dripThePlant();
    else
      counter--;
  } 
  delay(1000);
}

// Enable motor for short time, so little bit of water will reach the plant
// Might need to change the delay and/or counter to finetune to your system
void dripThePlant() {
    Serial.println("Pump a little bit");
    digitalWrite(POMPOUT, true);
    delay(750);
    counter = 25;
    Serial.println("Pump off");
    digitalWrite(POMPOUT, false);
}

void outputToSerialMonitor() {
  // Data for Tools->Serial Monitor
  Serial.print("Analog raw: ");
  Serial.println(analogValue);
  Serial.print("Digital raw: ");
  Serial.println(digitalValue);
  Serial.println(" ");
  Serial.print("counter: ");
  Serial.println(counter);
}
