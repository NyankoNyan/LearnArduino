#define FIRST_LED_PIN 2
#define LAST_LED_PIN 11
#define BUZZER_PIN 13

void setup() {
  for (int pin = FIRST_LED_PIN; pin <= LAST_LED_PIN; pin++) {
    pinMode(pin, OUTPUT);
  }
  pinMode(BUZZER_PIN, OUTPUT);
}

bool signStarted = false;

void loop() {

  unsigned long int ms = millis();

  int side = (ms / 500) % 2;
  int lamp = (ms / 50) % 10;
  if (side == 1) {
    lamp = 9 - lamp;
  }

  if (side == 0 && lamp == 0) {
    if (!signStarted) {
      signStarted = true;
      tone(BUZZER_PIN, 220, 50);
    }
  } else if (side == 1 && lamp == 9) {
    if (!signStarted) {
      signStarted = true;
      tone(BUZZER_PIN, 440, 50);
    }
  } else {
    signStarted = false;
  }

  int pin = FIRST_LED_PIN + lamp;
  digitalWrite(pin, HIGH);
  delay(10);
  digitalWrite(pin, LOW);
}
