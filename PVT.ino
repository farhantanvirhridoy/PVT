#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Servo.h>

#define ONE_WIRE_BUS 2
const int input = A0;
const int solenoid = 7;

LiquidCrystal_I2C lcd(0x27, 16, 2);

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensor(&oneWire);

DeviceAddress Thermometer;

Servo myservo;

float get_temp1() {
  sensor.requestTemperatures();
  return sensor.getTempCByIndex(0);
}

float get_temp2() {
  sensor.requestTemperatures();
  return sensor.getTempCByIndex(1);
}

float get_temp3() {
  sensor.requestTemperatures();
  return sensor.getTempCByIndex(2);
}

void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    Serial.print("0x");
    if (deviceAddress[i] < 0x10) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
    if (i < 7) Serial.print(", ");
  }
  Serial.println("");
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
  LS = WATER;
  return LS;
}

void valve(int state)
{
  digitalWrite(solenoid, state);
}

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  pinMode(input, INPUT);
  myservo.attach(9);
  pinMode(solenoid, OUTPUT);
  sensor.begin();

  Serial.println("Locating devices...");
  Serial.print("Found ");
  int deviceCount = sensor.getDeviceCount();
  Serial.print(deviceCount, DEC);
  Serial.println(" devices.");
  Serial.println("");

  Serial.println("Printing addresses...");
  for (int i = 0;  i < deviceCount;  i++)
  {
    Serial.print("Sensor ");
    Serial.print(i + 1);
    Serial.print(" : ");
    sensor.getAddress(Thermometer, i);
    printAddress(Thermometer);
  }
}


void loop() {
  float T1 = get_temp1();
  float T2 = get_temp2();
  float T3 = get_temp3();
  float Q = get_flowrate();

  if (T2 >= 45)
  {
    valve(1);
    servo(45);
  }

  if (T2 <= 30)
  {
    valve(0);
    servo(0);
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
