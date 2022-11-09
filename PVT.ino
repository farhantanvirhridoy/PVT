#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Servo.h>

#define ONE_WIRE_BUS 2
const int input = A0;

LiquidCrystal_I2C lcd(0x27, 16, 2);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
Servo myservo;

float get_temp() {
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0);
}

void servo(int angle) {
  int val;
  val = map(angle, 0, 1023, 0, 180);
  myservo.write(val);
}

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
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  pinMode(input, INPUT);
  myservo.attach(9);
}

void loop() {
lcd.setCursor(0,0);
lcd.print("T = ");
lcd.print(get_temp());
lcd.setCursor(0,1);
lcd.print("Q = ");
lcd.print(get_flowrate());

delay(1000);
}