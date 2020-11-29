int pin_1 = 13;
int pin_2 = 12;
const int stepCount = 8;
const int pattern_1[stepCount] = {0,1,0,1,0,1,1,1};
const int pattern_2[stepCount] = {1,1,1,0,1,0,0,0};
int stepId = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin_1,OUTPUT);
  pinMode(pin_2,OUTPUT);
}

int ledPower(bool active){
  return active?HIGH:LOW;
}

void loop() {
  for(stepId=0; stepId<stepCount; stepId++){
    digitalWrite(pin_1, ledPower(pattern_1[stepId]));
    digitalWrite(pin_2, ledPower(pattern_2[stepId]));
    delay(100);
  }
}
