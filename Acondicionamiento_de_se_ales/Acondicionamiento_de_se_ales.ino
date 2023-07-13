#include <LedControl.h>
#include <Ticker.h>
void sensor_de_humo(void);
int valor;
Ticker isr_accion_humo(sensor_de_humo, 5000);
LedControl matri_Edgar = LedControl(5, 6, 4, 1);
byte llamas_1 [8] = {
  B11110000,
  B11100000,
  B11111100,
  B11101000,
  B10111111,
  B11011000,
  B10111100,
  B11110000
};

byte llamas_2 [8] = {
  B00001100,
  B00001001,
  B11101011,
  B00111111,
  B11101011,
  B00001001,
  B00001100
};

byte feliz[8] = {
  B00000000,
  B00100000,
  B01001110,
  B10000000,
  B10000000,
  B01001110,
  B00100000,
  B00000000
};

byte copo[8] = {
  B00101000,
  B10010010,
  B01010100,
  B00111000,
  B00111000,
  B01010100,
  B10010010,
  B00101000
};
void setup() {
  Serial.begin(9600);
  matri_Edgar.shutdown(0, false);
  matri_Edgar.setIntensity(0, 4);
  matri_Edgar.clearDisplay(0);
  isr_accion_humo.start();

}

void loop() {
  isr_accion_humo.update();
  if (valor >= 100 && valor <= 399) {
    neutro_1();
    delay(500);
    neutro_2();
    delay(500);
  }
  if (valor >= 400) {
    fuego_1();
    delay(500);
    fuego_2();
    delay(500);
  }
}
void sensor_de_humo(void) {
  valor = analogRead(A0);
  Serial.println(valor);
}
void fuego_1() {
  for (int i = 0; i < 8; i++) {
    matri_Edgar.setRow(0, i, llamas_1[i]);
  }
 delay(2500);
}


void fuego_2() {
  for (int x = 0; x < 8; x++) {
    matri_Edgar.setRow(0, x, llamas_2[x]);
  }
  delay(2500);
}

void neutro_1() {
  for (int y = 0; y < 8; y++) {
    matri_Edgar.setRow(0, y, feliz[y]);
  }
  delay(2500);
}

void neutro_2() {
  for (int a = 0; a < 8; a++) {
    matri_Edgar.setRow(0, a, copo[a]);
  }
  delay(2500);
}
