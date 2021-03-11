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

  // Analog input for moister sensor (0 for wet and 1023 for dry)
  pinMode(ANA, INPUT);

  // Digital input moister sensor
  // LOW for wet and HIGH for dry
  pinMode(DIGI, INPUT);

  // Output to drive the motor (onn/off)
  pinMode(POMPOUT, OUTPUT);

}
void loop() {

  // Read moister sensor values (analog and digital inputs)
  analogValue = analogRead(ANA);
  digitalValue = digitalRead(DIGI);

  // Serial data
  Serial.print("Analog raw: ");
  Serial.println(analogValue);
  Serial.print("Digital raw: ");
  Serial.println(digitalValue);
  Serial.println(" ");

  // 0 for wet and 1023 for dry
  if (analogValue > 800) {
    if (counter == 0)
      waterPlantLittleBit();
    else
        counter--;
    Serial.print("counter: ");
    Serial.println(counter);
  } 

  delay(1000);
}


void waterPlantLittleBit() {
    Serial.println("Pump a little bit");
    digitalWrite(POMPOUT, true);
    delay(750);
    counter = 25;
    Serial.println("Pump off");
    digitalWrite(POMPOUT, false);
}
