#define LED1_PIN 11
#define LED2_PIN 12
#define LED3_PIN 13
#define LDR_PIN A0
#define POT_PIN A1

void setup() {
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
}

void loop() {
  int lightness = analogRead(LDR_PIN);
  int threshold = analogRead(POT_PIN);

  int darkness_force = 0;

  if (lightness > threshold) {
    darkness_force = 0;
  }  else {
    darkness_force = (threshold - lightness) * 4 / threshold;
  }

  digitalWrite(LED1_PIN, (darkness_force >= 1) ? HIGH : LOW);
  digitalWrite(LED2_PIN, (darkness_force >= 2) ? HIGH : LOW);
  digitalWrite(LED3_PIN, (darkness_force >= 3) ? HIGH : LOW);
}
