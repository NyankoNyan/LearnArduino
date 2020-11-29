#define KEY1_PIN 8
#define KEY2_PIN 9
#define KEY3_PIN 10
#define KEY4_PIN 11
#define KEY5_PIN 12
#define BUZZER_PIN 13

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
}

const int notes[] = {440, 494, 523, 587, 659};
const int keys[] = {KEY1_PIN, KEY2_PIN, KEY3_PIN, KEY4_PIN, KEY5_PIN};
const int key_count = sizeof(keys) / sizeof(keys[0]);
int tick_counter = 0;
int max_ticks = 80;

void loop() {
  int key_code = -1;
  for (int i = 0; i < key_count; i++) {
    if ( !digitalRead(keys[i])) {
      key_code = i;
    }
  }
  if (key_code >= 0) {
    //float slide_mult = .8f + .2f * float(tick_counter) / float(max_ticks);
    float slide_mult = .8f + .2f * (1.0f - abs(2.0f * float(tick_counter) - float(max_ticks)) / float(max_ticks));
    tone(BUZZER_PIN, int(notes[key_code] * slide_mult));
    if (tick_counter < max_ticks) {
      tick_counter++;
    } else {
      tick_counter = 0;
    }
  } else {
    noTone(BUZZER_PIN);
    tick_counter = 0;
  }
  delay(1);
}
