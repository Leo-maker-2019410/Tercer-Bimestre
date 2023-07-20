/*
   Fundacion Kinal
   Centro educativo tecnico laboral Kinal
   Electronica
   Grado: Quinto
   Sección: A
   Curso: Taller de electronica digital y reparación de computadoras I
   Nombre: Edgar Leonel Ramírez Estrada
   Carnet: 2019410
   Proyecto: Acelerometro ADXL345
*/
#include <LedControl.h>
#include<Wire.h>
#include <SparkFun_ADXL345.h>

//Constructor para matriz)//
LedControl matriz_Edgar = LedControl(5, 6, 4, 1);

//Figuras para matriz//
byte centro [8] = {
  B00000000,
  B11111111,
  B00000000,
  B00011000,
  B00011000,
  B00000000,
  B11111111,
  B00000000
};

byte derecha_1 [8] = {
  B00000000,
  B11111111,
  B00000000,
  B00001100,
  B00001100,
  B00000000,
  B11111111,
  B00000000
};

byte derecha_2 [8] = {
  B00000000,
  B11111111,
  B00000000,
  B00000011,
  B00000011,
  B00000000,
  B11111111,
  B00000000
};

byte izquierda_1 [8] = {
  B00000000,
  B11111111,
  B00000000,
  B01100000,
  B01100000,
  B00000000,
  B11111111,
  B00000000
};

byte izquierda_2 [8] = {
  B00000000,
  B11111111,
  B00000000,
  B11000000,
  B11000000,
  B00000000,
  B11111111,
  B00000000
};

ADXL345 acelerometro_Edgar = ADXL345();    //constructor para poder utilizar el acelerometro.

//Variable donde guardo las aceleraciones.
int x;

void setup() {
  Serial.begin(9600);     //Inicio la comunicacion serial a 9600 baudios.
  Serial.println("Nivelador Digital");
  acelerometro_Edgar.powerOn();             //Enciendo el acelerometro.
  acelerometro_Edgar.setRangeSetting(8);    //Configuro para medir la aceleracion con 8g.
  matriz_Edgar.shutdown(0,false);
  matriz_Edgar.setIntensity(0,8
  );
  matriz_Edgar.clearDisplay(0);
} 

void loop() {
  aceleraciones();
  if(x > -2 && x <= 1){
    burbuja_centrada();
    Serial.println("burbuja centrada");
  } 
  if(x > 1 && x <= 20){
    burbuja_derecha1();
    Serial.println("burbuja medio inclinado - derecha");
  }
  if(x >20){
    burbuja_derecha2();
    Serial.println("burbuja inclinada - derecha");
  }
  if(x >= -15 && x <= -2){
    burbuja_izquierda1();
    Serial.println("burbuja medio inclinada - izquierda");
  }
  if(x < -15){
    burbuja_izquierda2();
    Serial.println("burbuja inclinada - izquierda");
  }
}

void aceleraciones() {
  //Aqui obtendremos las aceleraciones dadas en el eje X//
  acelerometro_Edgar.readAccel(&x);
  Serial.print("La aceleracion en x es de: ");
  Serial.println(x);
  delay(500);
}

void burbuja_centrada(){
  for(int i = 0; i<8;i++){
    matriz_Edgar.setRow(0,i,centro[i]);
  }
}

void burbuja_derecha1(){
  for(int e = 0; e<8;e++){
    matriz_Edgar.setRow(0,e,derecha_1[e]);
  }
}

void burbuja_derecha2(){
  for(int d = 0; d<8;d++){
    matriz_Edgar.setRow(0,d,derecha_2[d]);
  }
}
void burbuja_izquierda1(){
  for(int g = 0; g<8;g++){
    matriz_Edgar.setRow(0,g,izquierda_1[g]);
  }
}

void burbuja_izquierda2(){
  for(int a = 0; a<8;a++){
    matriz_Edgar.setRow(0,a,izquierda_2[a]);
  }
}
