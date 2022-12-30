#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Servo.h>

#define ONE_WIRE_BUS_1 2
#define ONE_WIRE_BUS_2 3
#define ONE_WIRE_BUS_3 4
const int inputQ = A0;
const int solenoid = 7;

LiquidCrystal_I2C lcd(0x27, 16, 2);

OneWire oneWire1(ONE_WIRE_BUS_1);
OneWire oneWire2(ONE_WIRE_BUS_2);
OneWire oneWire3(ONE_WIRE_BUS_3);

DallasTemperature sensor1(&oneWire1);
DallasTemperature sensor2(&oneWire2);
DallasTemperature sensor3(&oneWire3);

Servo myservo;

float get_temp1() {
  sensor1.requestTemperatures();
  return sensor1.getTempCByIndex(0);
}

float get_temp2() {
  sensor2.requestTemperatures();
  return sensor2.getTempCByIndex(0);
}

float get_temp3() {
  sensor3.requestTemperatures();
  return sensor3.getTempCByIndex(0);
}

float get_flowrate() {
  int X;
  int Y;
  float TIME = 0;
  float FREQUENCY = 0;
  float WATER = 0;
  float LS = 0;
  X = pulseIn(inputQ, HIGH);
  Y = pulseIn(inputQ, LOW);
  TIME = X + Y;
  FREQUENCY = 1000000 / TIME;
  WATER = FREQUENCY / 7.5;
  LS = WATER;
  return LS;
}

void servo(int mili) {

  myservo.writeMicroseconds(mili);
}

void valve(bool state)
{
  digitalWrite(solenoid, !state);
}

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  pinMode(inputQ, INPUT);
  myservo.attach(9);
  pinMode(solenoid, OUTPUT);
}

void loop() {
  float T1 = get_temp1();
  float T2 = get_temp2();
  float T3 = get_temp3();
  float Q = get_flowrate();

  if (T2 >= 45)
  {
    valve(1);
    servo(2000);
  }
  else
  {
    
  }

  if (T2 < 30)
  {
    valve(0);
  }

  Serial.print("T1 = ");
  Serial.print(T1);
  Serial.print(", T2 = ");
  Serial.print(T2);
  Serial.print(", T3 = ");
  Serial.print(T3);
  Serial.print(", Q = ");
  Serial.print(Q);
  Serial.println(" L/min");

  delay(1000);
}
