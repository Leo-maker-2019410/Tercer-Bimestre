/*
   Fundacion Kinal
   Centro educativo tecnico laboral Kinal
   Electronica
   Grado: Quinto
   Sección: A
   Curso: Taller de electronica digital y reparación de computadoras I
   Nombre: Edgar Leonel Ramírez Estrada - Luis Alexander Racanac Canahui
   Carnet: 2019410 - 2022084
   Proyecto: Banda
*/
#include <Servo.h>
#include <Stepper.h>
int pasosVuelta = 2048;
Stepper motor(pasosVuelta,6,8,7,9);
#define ch_LDR    A0  //pin A0 del arduino, a este conectaremos el punto medio del divisor de tension entre LDR y una resistencia de 33K
#define led_Azul  3   //led azul conectado al pin 3
#define led_Verde 4   //led verde conectado al pin 4
#define led_Rojo  5   //led rojo conectado al pin 5
#define tm 2
#define sensor_objetos 10

//Servo//
Servo barra;
//Variables
//Valores analogicos de la intensidad de cada color
int resultado_azul, resultado_rojo, resultado_verde;
//Valores analogicos leidos por la LDR
int resultado;

//Valor de umbral para los colores
int tol = 8; //este valor lo podremos cambiar segun los valores leidos por nuestra LDR

void setup() {
  //Comunicacion serial
  Serial.begin(9600);
  Serial.println("Construccion del sensor de color");
  motor.setSpeed(6);
  //Configuracion de I/O
  pinMode(ch_LDR, INPUT); //pin A0 como entrada
  pinMode(led_Azul, OUTPUT); //pin 3 como salida
  pinMode(led_Verde, OUTPUT); //pin 4 como salida
  pinMode(led_Rojo, OUTPUT);  //pin 5 como salida
  pinMode(sensor_objetos, INPUT);
  barra.attach(11);

  //Los leds inician en un estado de bajo
  digitalWrite(led_Azul, LOW);
  digitalWrite(led_Verde, LOW);
  digitalWrite(led_Rojo, LOW);
  barra.write(0);

}

void loop() {
  motor.step(-pasosVuelta);
  if (digitalRead(sensor_objetos) == LOW) {
    motor.step(-1935);
    escaner_de_colores();
    operacion();
    delay(500);
  }
}


int escaner_de_colores() {
  //Enviendo el led rojo
  digitalWrite(led_Rojo, HIGH);
  //espero 150 milisegundos
  delay(150);

  //Leo el valor captado por la LDR
  resultado = analogRead(ch_LDR);
  resultado_rojo = map(resultado, 0, 1023, 0, 255); //lo linealizo
  //Lo muestro por medio del monitor serial
  Serial.print("color_rojo:  ");
  Serial.println(resultado_rojo);
  digitalWrite(led_Rojo, LOW);
  delay(150);

  //Enviendo el led verde
  digitalWrite(led_Verde, HIGH);
  //espero 150 milisegundos
  delay(150);

  //Leo el valor captado por la LDR
  resultado = analogRead(ch_LDR);
  resultado_verde = map(resultado, 0, 1023, 0, 255); //lo linealizo
  //Lo muestro por medio del monitor serial
  Serial.print("color_verde:  ");
  Serial.println(resultado_verde);
  digitalWrite(led_Verde, LOW);
  delay(150);

  //Enviendo el led azul
  digitalWrite(led_Azul, HIGH);
  //espero 150 milisegundos
  delay(150);

  //Leo el valor captado por la LDR
  resultado = analogRead(ch_LDR);
  resultado_azul = map(resultado, 0, 1023, 0, 255); //lo linealizo
  //Lo muestro por medio del monitor serial
  Serial.print("color_azul: ");
  Serial.println(resultado_azul);
  digitalWrite(led_Azul, LOW);
  delay(150);
}

void operacion() {
  if (resultado_verde > resultado_rojo && resultado_verde > resultado_azul) {
    motor.step(-1150);
    delay(200);
    barra.write(180);
    delay(800);
    barra.write(0);
  }
}
