#include <OneWire.h>
#include <DallasTemperature.h>
OneWire ourWire(5);
DallasTemperature sensors(&ourWire);
int cel;
int led_red = 3;
int estado = 0;

void setup() {
  Serial.begin(9600);
  sensors.begin();
  pinMode(led_red, OUTPUT);
}

void loop() {
   if (Serial.available() > 0) {
    estado = Serial.read();
  }
  if (estado == '1') {
    digitalWrite(led_red, HIGH);
  }
  if (estado == '2') {
    digitalWrite(led_red, LOW);
  }
  cel = temperaturaC();
  Serial.println(cel);
}

int temperaturaC() {
  sensors.requestTemperatures();
  int temp = sensors.getTempCByIndex(0);
  delay(1000);
  return temp;
}
