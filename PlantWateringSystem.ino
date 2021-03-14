#include <time.h>

#define ANA A0        // Analog input for moisture sensor (0 for wet and 1023 for dry)
#define DIGI D5       // Digital input moisture sensor (LOW for wet and HIGH for dry)
#define POMPOUT D6    // Output to drive the motor (true=on / false=off)

// Moisture sensor threshold ; above this value plant get water drips..
// Initial value for Basil .. but set lower to get more wet soil ; or higher for get more dry soil 
#define DRIP_THRESHOLD 510  
#define SECONDS_BETWEEN_DRIPS 30

double analogValue = 0.0;
double previousAnalogValue = analogValue;
int digitalValue = 0;

// Counts down when soil is to dry; at zero drip the plant  
int counter = SECONDS_BETWEEN_DRIPS;
int previousCounter = counter;

// Variable to format time to HH:MM:SS (since start)
time_t     now;
struct tm  ts;
char       buf[40];

void setup() {
  Serial.begin(115200);
  Serial.println("Plant_watering_system Setup");

  // Setup which I/O we use.
  pinMode(ANA, INPUT);
  pinMode(DIGI, INPUT);
  pinMode(POMPOUT, OUTPUT);

}
void loop() {
  // Read moisture sensor values (analog and digital inputs)
  analogValue = analogRead(ANA);
  digitalValue = digitalRead(DIGI);

  outputToSerialMonitor();

  // Moisture sensor values : 0 for wet and 1023 for dry
  // Soil to dry ? 
  if (analogValue > DRIP_THRESHOLD) {
    if (counter == 0)
      dripThePlant();
    else
      counter--;
  } 
  delay(1000);
}

// Enable motor for short time, so little bit of water will reach the plant
// Then counter will start decreasing to zero => to wait a moment for next moisture sensor reading (let water go into soil)
// Might need to change the delay and/or counter to finetune to your system
void dripThePlant() {
    Serial.println("Pump a little bit");
    digitalWrite(POMPOUT, true);
    delay(750);
    counter = SECONDS_BETWEEN_DRIPS;
    Serial.println("Pump off");
    digitalWrite(POMPOUT, false);
}


// Show values to serial monitor (Tools->Serial Monitor)
// with those values you can view and finetune your system
void outputToSerialMonitor() {

  double delta = abs(analogValue - previousAnalogValue);
  
  if ( (delta >= 5) || (previousCounter != counter))
  {
    previousAnalogValue = analogValue;
    
    // Get current time
    time(&now);

    // Format time, "hh:mm:ss" (time since startup)
    ts = *localtime(&now);
    strftime(buf, sizeof(buf), "%H:%M:%S ", &ts);
    Serial.print(buf);

    if (analogValue <= DRIP_THRESHOLD)
      Serial.print("Soil is OK");
    else 
      Serial.print("Soil is to DRY");    

    Serial.print("\tMoisture Analoge value: ");
    Serial.print(analogValue);
    Serial.print("\tDigital value: ");
    Serial.print(digitalValue);

    if (previousCounter != counter)
    {
      previousCounter = counter;
      Serial.print("\t Next drip in: ");
      Serial.print(counter);
      Serial.print(" seconds.");
    }

    Serial.println();
  }



}
