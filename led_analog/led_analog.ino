const int pina_1 = 13;

void setup() {
  pinMode(pina_1,OUTPUT);
}

const int stepPowerChange = 10;
const int stepTime = 25;

void loop() {
  for( int power = 0; power <= 255; power += stepPowerChange ){
    analogWrite(pina_1, power);
    delay(stepTime);
  }
  for( int power = 255; power >= 0; power -= stepPowerChange){
    analogWrite(pina_1, power);
    delay(stepTime);
  }
}
