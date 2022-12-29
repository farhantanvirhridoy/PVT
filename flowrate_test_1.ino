//const int input = A0;

float get_flowrate() {
  int X;
  int Y;
  float TIME = 0;
  float FREQUENCY = 0;
  float WATER = 0;
  float LS = 0;
  X = pulseIn(input, HIGH);
  Y = pulseIn(input, LOW);
  TIME = X + Y;
  FREQUENCY = 1000000 / TIME;
  WATER = FREQUENCY / 7.5;
  LS = WATER / 60;
  return LS;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(get_flowrate());
  Serial.println(" L/h");
}
