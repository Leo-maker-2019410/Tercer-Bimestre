/*
*Fundacion Kinal
*Centro Educativo Tecnico Laboral Kinal
*Electronica
*Grado: Quinto
*Seccion: A
*Cuerso: Taller de Electronica Digital y Reparacion de Computadoras I
*Nombre: Edgar Leonel Ramírez Estrada
*Carnet: 209410
*Proyecto: Practica No.2 Control_de_secuencia_de_cololesRGB_con_potenciometro_Ejercicio2
*/
//variables//
#define RED  3
#define GREEN 5
#define BLUE 6
int tiempo = 0;
int poten = A0;

//CAMBIO DE NOMBRES DE DIRECTIVA//
#define salida(pin) pinMode(pin,OUTPUT);
#define entrada(pin) pinMode(pin,INPUT);

void setup()
{
  salida(RED);
  salida(GREEN);
  salida(BLUE);
  entrada(poten);
}

void loop() {
  tiempo = map(analogRead(poten), 0, 1023, 100, 1000);
  analogWrite(RED, 174);
  analogWrite(GREEN, 92);
  analogWrite(BLUE, 230);
  delay(tiempo);
  analogWrite(RED, 255);
  analogWrite(GREEN, 255);
  analogWrite(BLUE, 255);
  delay(tiempo);
  analogWrite(RED, 0);
  analogWrite(GREEN, 255);
  analogWrite(BLUE, 255);
  delay(tiempo);
  analogWrite(RED, 189);
  analogWrite(GREEN, 174);
  analogWrite(BLUE, 20);
  delay(tiempo);
  analogWrite(RED, 225);
  analogWrite(GREEN, 87);
  analogWrite(BLUE, 35);
  delay(tiempo);
}
