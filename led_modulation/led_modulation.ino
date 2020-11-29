#define LED_PIN 9
#define POT_PIN A0

const int loop_delay = 10;
const int min_delta_step = 1;
const int max_delta_step = 64;
int brightness = 0;
bool raisePower = true;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(POT_PIN, INPUT);
}

void loop() {
  int rotation, powerDelta;

  rotation = analogRead(POT_PIN);

  powerDelta = min_delta_step + round(float(rotation) / 1023.0f * (max_delta_step - min_delta_step));

  if (raisePower) {
    brightness += powerDelta;
    if (brightness > 255) {
      brightness = 255;
      raisePower = false;
    }
  } else {
    brightness -= powerDelta;
    if (brightness < 0) {
      brightness = 0;
      raisePower = true;
    }
  }

  analogWrite(LED_PIN, brightness);

  delay(loop_delay);
}
