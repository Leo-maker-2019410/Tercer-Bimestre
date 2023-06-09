/*
*Fundacion Kinal
*Centro Educativo Tecnico Laboral Kinal
*Electronica
*Grado: Quinto
*Seccion: A
*Cuerso: Taller de Electronica Digital y Reparacion de Computadoras I
*Nombre: Edgar Leonel Ramírez Estrada
*Carnet: 209410
*Proyecto: Practica No.2 Control_de_led_con_potenciometro
*/
#define RED 3
int Control_brillo = 0;
int poten = A0;


void setup() {
  pinMode(RED, OUTPUT);
  pinMode(poten, INPUT);

}

void loop() {
  Control_brillo = map(analogRead (poten), 0, 1023, 0, 255);
  analogWrite(RED, Control_brillo);
}
