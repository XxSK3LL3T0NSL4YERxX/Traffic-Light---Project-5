#define westButton 3
#define eastButton 13
#define pedestrianButton 8
#define westRed 2
#define westYellow 1
#define westGreen 0
#define eastRed 12
#define eastYellow 11
#define eastGreen 10
#define pedestrianLight 9  // White pedestrian light
#define yellowBlinkTime 500

boolean trafficWest = true;  // west = true, east = false
int flowTime = 10000;
int changeDelay = 2000;
int pedestrianTime = 7000;

void setup() {
  pinMode(westButton, INPUT);
  pinMode(eastButton, INPUT);
  pinMode(westRed, OUTPUT);
  pinMode(westYellow, OUTPUT);
  pinMode(westGreen, OUTPUT);
  pinMode(eastRed, OUTPUT);
  pinMode(eastYellow, OUTPUT);
  pinMode(eastGreen, OUTPUT);
  pinMode(pedestrianButton, INPUT);

  digitalWrite(westRed, LOW);
  digitalWrite(westYellow, LOW);
  digitalWrite(westGreen, HIGH);
  digitalWrite(eastRed, HIGH);
  digitalWrite(eastYellow, LOW);
  digitalWrite(eastGreen, LOW);
  digitalWrite(pedestrianLight, LOW);
}

void loop() {
  while (digitalRead(pedestrianButton) == HIGH) {
    handlePedestrianCrossing();
  }
  switchTrafficWest();
  switchTrafficEast();
}

// Function to blink the yellow light
void blinkYellowLight(int lightPin, int blinkTime) {
  for (int a = 0; a < 5; a++) {
    digitalWrite(lightPin, LOW);
    delay(blinkTime);
    digitalWrite(lightPin, HIGH);
    delay(blinkTime);
  }
}

void switchTrafficWest() {
  if (digitalRead(westButton) == HIGH) {
    if (trafficWest != true) {
      trafficWest = true;
      delay(flowTime);
      digitalWrite(eastGreen, LOW);

      digitalWrite(eastYellow, HIGH);
      delay(changeDelay);
      digitalWrite(eastYellow, LOW);
      digitalWrite(eastRed, HIGH);
      delay(changeDelay);

      // Blink the yellow light for west direction
      blinkYellowLight(westYellow, yellowBlinkTime);

      digitalWrite(westYellow, LOW);
      digitalWrite(westRed, LOW);
      digitalWrite(westGreen, HIGH);
    }
  }
}

void switchTrafficEast() {
  if (digitalRead(eastButton) == HIGH) {
    if (trafficWest == true) {
      trafficWest = false;
      delay(flowTime);
      digitalWrite(westGreen, LOW);
      digitalWrite(westYellow, HIGH);
      delay(changeDelay);
      digitalWrite(westYellow, LOW);
      digitalWrite(westRed, HIGH);
      delay(changeDelay);

      // Blink the yellow light for east direction
      blinkYellowLight(eastYellow, yellowBlinkTime);

      digitalWrite(eastYellow, LOW);
      digitalWrite(eastRed, LOW);
      digitalWrite(eastGreen, HIGH);
    }
  }
}

void handlePedestrianCrossing() {
  // Stop both traffic directions
  digitalWrite(westGreen, LOW);

  digitalWrite(eastGreen, LOW);

  if (trafficWest) {
    blinkYellowLight(westYellow, yellowBlinkTime);
    delay(100);
  } else {
    blinkYellowLight(eastYellow, yellowBlinkTime);
    delay(100);
  }
  digitalWrite(westYellow, LOW);
  digitalWrite(westRed, HIGH);

  digitalWrite(eastYellow, LOW);
  digitalWrite(eastRed, HIGH);

  // Turn on pedestrian light
  digitalWrite(pedestrianLight, HIGH);
  delay(pedestrianTime);
  digitalWrite(pedestrianLight, LOW);

  if (trafficWest) {
    digitalWrite(westRed, LOW);
    digitalWrite(westGreen, HIGH);
  } else {
    digitalWrite(eastRed, LOW);
    digitalWrite(eastGreen, HIGH);
  }
}
