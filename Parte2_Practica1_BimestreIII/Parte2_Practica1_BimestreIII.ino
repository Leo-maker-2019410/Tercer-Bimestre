/*
*Fundacion Kinal
*Centro Educativo Tecnico Laboral Kinal
*Electronica
*Grado: Quinto
*Seccion: A
*Cuerso: Taller de Electronica Digital y Reparacion de Computadoras I
*Nombre: Edgar Leonel Ramírez Estrada
*Carnet: 209410
*Proyecto: Practica No.1 parte 2 
*/

#include <Ticker.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//Sensor de Temperatura//
OneWire ourWire(5);
DallasTemperature sensors(&ourWire);
float cel;

#define push_buttom 2

//Funciones del ISR
void isr_temperatura();
void isr_buttom();

//Variable
volatile static bool estado_1;
volatile static bool estado_2;

//Constructor
Ticker isr_accion_termometro(isr_temperatura, 3000);
Ticker isr_accion_push(isr_buttom, 6000);

void setup() {
  Serial.begin(9600);
  Serial.println("Uso de Ticker");
  sensors.begin();
  isr_accion_termometro.start();
  pinMode(push_buttom, INPUT);
  isr_accion_push.start();
  estado_1 = LOW;
}

void loop() {
  cel = temperaturaC();
  isr_accion_termometro.update();
  isr_accion_push.update();

}

int temperaturaC() {
  sensors.requestTemperatures();   //Se envía el comando para leer la temperatura
  int temp = sensors.getTempCByIndex(0); //Se obtiene la temperatura en ºF
  return temp;
}
void isr_temperatura() {
  Serial.println(cel);
}

void isr_buttom() {
  estado_1 = digitalRead(push_buttom);
  if (estado_1 == HIGH) {
    Serial.println("ABIERTO");
  }
  if(estado_1 == LOW){
    Serial.println("CERRADO");
  }
}
