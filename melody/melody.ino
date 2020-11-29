#define BUZZER_PIN 3
#define LDR_PIN A0

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
}

const int mute = 5000;
/* 1/16 = 4
   1/8 = 8
*/
const int parts_in_beat = 64;
const int beat_time = 1792;/* 64 * 7 * 4*/
const int note_shift = 7;
const int base_frequency = 440;
const int note_freq[] = {
  220, 233, 247, 262, 277, 294, 311, 330, 349, 370, 392, 415,
  440, 466, 494, 523, 554, 587, 622, 659, 698, 740, 784, 831,
  880, 932, 988, 1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661,
  1760, 1865, 1976, 2093, 2217, 2349
};
const int note_count = sizeof(note_freq) / sizeof(note_freq[0]);
const int pattern_size = 250;//Outro: 223;//Section B: 116;//Section A: 107;// Intro: 27
const int time_pattern[pattern_size] = {
  //Intro
  4, 4, 5, 3, 8, 4, 4, 4, 4, 4, 4, 4, 4, 8,
  8, 4, 4, 8, 8, 4, 4, 4, 4, 4, 4, 4, 4,

  //Section A
  8, 8, 4, 8, 4, 4, 4, 7, 1, 8, 8,
  7, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  8, 8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  8, 4, 4, 4, 4, 4, 4, 4, 4, 8, 8, 8,

  8, 8, 4, 8, 4, 4, 4, 7, 1, 8, 8,
  7, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  8, 8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  8, 4, 4, 4, 4, 4, 4, 4, 4, 8, 7, 1, 8,

  //Section B
  8, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  7, 1, 8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  8, 4, 4, 8, 4, 4, 3, 1, 4, 4, 4, 4, 4, 4, 4,
  7, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 8, 8,

  8, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  7, 1, 8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  8, 4, 4, 8, 4, 4, 3, 1, 4, 4, 4, 4, 4, 4, 4,
  7, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 8, 8,

  // Outro
  //  8, 8, 4, 8, 4, 4, 4, 7, 1, 8, 8,
  //  7, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  //  8, 8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  //  8, 4, 4, 4, 4, 4, 4, 4, 4, 8, 8, 8,
  //
  //  8, 8, 4, 8, 4, 4, 4, 7, 1, 8, 8,
  //  7, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  //  8, 8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  //  8, 4, 4, 4, 4, 4, 4, 4, 4, 8, 7, 1, 8,
  //
  //  8, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  //  7, 1, 8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  //  8, 4, 4, 8, 4, 4, 3, 1, 4, 4, 4, 4, 4, 4, 4,
  //  7, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 8, 8,
  //
  //  8, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  //  7, 1, 8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  //  8, 4, 4, 8, 4, 4, 3, 1, 4, 4, 4, 4, 4, 4, 4,
  //  7, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 8, 8,
};
const int note_pattern[pattern_size] = {
  //Intro
  11, 12, 14, mute, 19, 11, 12, 14, 19, 21, 23, 21, 18, 19,
  14, 11, 12, 14, 19, 21, 18, 19, 21, 24, 23, 24, 21,

  //Section A
  14, 16, 9, 11, 7, 10, 9, 7, mute, 7, 9, //11 notes
  10, mute, 10, 9, 7, 9, 10, 14, 16, 11, 14, 9, 11, 7, 9, 7, //16 notes
  11, 14, 16, 11, 14, 9, 11, 7, 9, 11, 10, 9, 7, 9, //14 notes
  10, 7, 9, 11, 14, 9, 11, 9, 7, 9, 7, 9, //12 notes

  14, 16, 9, 11, 7, 10, 9, 7, mute, 7, 9, //11 notes
  10, mute, 10, 9, 7, 9, 10, 14, 16, 11, 14, 9, 11, 7, 9, 7, //16 notes
  11, 14, 16, 11, 14, 9, 11, 7, 9, 11, 10, 9, 7, 9, //14 notes
  10, 7, 9, 11, 14, 9, 11, 9, 7, 9, 7, mute, 7, //13 notes

  //Section B
  7, 2, 4, 7, 2, 4, 7, 9, 11, 7, 12, 11, 12, 14, //14 notes
  7, mute, 7, 2, 4, 7, 2, 12, 11, 9, 7, 2, -1, 0, 2, //15 notes
  7, 2, 4, 7, 2, 4, 7, mute, 7, 9, 11, 7, 2, 4, 2, //15 notes
  7, mute, 7, 6, 7, 2, 4, 7, 12, 11, 12, 14, 7, 6, //14 notes

  7, 2, 4, 7, 2, 4, 7, 9, 11, 7, 12, 11, 12, 14, //14 notes
  7, mute, 7, 2, 4, 7, 2, 12, 11, 9, 7, 2, -1, 0, 2, //15 notes
  7, 2, 4, 7, 2, 4, 7, mute, 7, 9, 11, 7, 2, 4, 2, //15 notes
  7, mute, 7, 6, 7, 2, 4, 7, 12, 11, 12, 14, 7, 9, //14 notes

  // Outro
  //  14, 16, 9, 11, 7, 10, 9, 7, mute, 7, 9, //11 notes
  //  10, mute, 10, 9, 7, 9, 10, 14, 16, 11, 14, 9, 11, 7, 9, 7, //16 notes
  //  11, 14, 16, 11, 14, 9, 11, 7, 9, 11, 10, 9, 7, 9, //14 notes
  //  10, 7, 9, 11, 14, 9, 11, 9, 7, 9, 7, 9, //12 notes
  //
  //  14, 16, 9, 11, 7, 10, 9, 7, mute, 7, 9, //11 notes
  //  10, mute, 10, 9, 7, 9, 10, 14, 16, 11, 14, 9, 11, 7, 9, 7, //16 notes
  //  11, 14, 16, 11, 14, 9, 11, 7, 9, 11, 10, 9, 7, 9, //14 notes
  //  10, 7, 9, 11, 14, 9, 11, 9, 7, 9, 7, mute, 7, //13 notes
  //
  //  7, 2, 4, 7, 2, 4, 7, 9, 11, 7, 12, 11, 12, 14, //14 notes
  //  7, mute, 7, 2, 4, 7, 2, 12, 11, 9, 7, 2, -1, 0, 2, //15 notes
  //  7, 2, 4, 7, 2, 4, 7, mute, 7, 9, 11, 7, 2, 4, 2, //15 notes
  //  7, mute, 7, 6, 7, 2, 4, 7, 12, 11, 12, 14, 7, 6, //14 notes
  //
  //  7, 2, 4, 7, 2, 4, 7, 9, 11, 7, 12, 11, 12, 14, //14 notes
  //  7, mute, 7, 2, 4, 7, 2, 12, 11, 9, 7, 2, -1, 0, 2, //15 notes
  //  7, 2, 4, 7, 2, 4, 7, mute, 7, 9, 11, 7, 2, 4, 2, //15 notes
  //  7, mute, 7, 6, 7, 2, 4, 7, 12, 11, 12, 14, 7, 9, //14 notes
};
const int soundStartAfter = 500;
const int soundStartBefore = 250;

bool play = false;
int note_id = 0;

const int maxDecay = 5;
int decay = 0;

int note_to_freq(int note) {
  int elem_count = sizeof(note_freq) / sizeof(note_freq[0]);
  if (note < 0 || note >= note_count) {
    return note_freq[0];
  }
  return note_freq[note + note_shift];
}

void loop() {
  int val, frequency;
  val = analogRead(LDR_PIN);

  if (val < soundStartBefore) {
    //  if (val > soundStartAfter && !play) {
    decay++;    
  } else {
    decay--;    
  }
  
  if(decay>=maxDecay){
    decay = maxDecay;
    if (!play) {
      play = true;
      note_id = 0;
    }
  }
  
  if(decay<=0){
    decay = 0;
    play = false;
    noTone(BUZZER_PIN);
  }
  if (play) {
    if (note_id >= pattern_size) {
      play = false;
      noTone(BUZZER_PIN);
    } else {
      if (note_pattern[note_id] == mute) {
        noTone(BUZZER_PIN);
      } else {
        frequency = note_to_freq(note_pattern[note_id]);
        tone(BUZZER_PIN, frequency);
      }
      delay(time_pattern[note_id] * (beat_time / parts_in_beat));
      note_id++;
    }
  }else{
    delay(10);
  }
}
