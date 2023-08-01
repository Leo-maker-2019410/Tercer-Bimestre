#include <LiquidCrystal_I2C.h> //Inluimos las librerias
#include <Wire.h>
#include <RTClib.h>
#include <SPI.h>
#include <MFRC522.h>

RTC_DS3231 rtc; //Variable de tiempo

#define RST_PIN 9 //Defino el pin del RST
#define SS_PIN 10 //Defino el pin del SS
MFRC522 mfrc522 (SS_PIN, RST_PIN);

byte LecturaUID[4];
byte Usuario1[4] = {0x23, 0xD4, 0x84, 0xAC}; //Tarjeta
byte Usuario2[4] = {0x13, 0x99, 0x6A, 0xB6}; //llavero

#define V_pin A0 //A0 sera el pin a utilizar para voltaje

//Variables del sensor de voltaje
unsigned int raw_sensor = 0;
float voltaje_sensado = 0;

//Variables del sensor de corriente
float Sensibilidad = 0.185;

//Incluimos el I2C con la direccion 0x27
LiquidCrystal_I2C lcd_Edgar(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  lcd_Edgar.init();//Inicializamos nuestra LCD
  lcd_Edgar.backlight();//Encendemos la luz de la LCD
  SPI.begin(); //se inicia el SPI
  mfrc522.PCD_Init();
  lcd_Edgar.setCursor(1, 0);
  lcd_Edgar.print("EEGSA - Kinal");
  lcd_Edgar.setCursor(1, 1);
  lcd_Edgar.print("Medidor Energia");
  pinMode(V_pin, INPUT);
  if (! rtc.begin()) {
    Serial.println("Modulo RTC no encontrado !");
  }
  rtc.adjust(DateTime(__DATE__, __TIME__));
}

void loop() {
  if (! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if (! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  Serial.print("Usuario:");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) {
      Serial.println(" 0");
    }
    else {
      Serial.print(" ");
    }
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    LecturaUID[i] = mfrc522.uid.uidByte[i];
  }
  if (comparaUID(LecturaUID, Usuario1)) {
    lcd_Edgar.clear();
    lcd_Edgar.setCursor(1, 0);
    lcd_Edgar.print("EEGSA - Kinal");
    lcd_Edgar.setCursor(0, 1);
    lcd_Edgar.print(voltaje_sensado);
    lcd_Edgar.setCursor(4, 1);
    lcd_Edgar.print("V");
    funcionamiento_voltaje();
    tiempo_reloj();
    float Idc = calculoCorriente(500);
    lcd_Edgar.setCursor(6, 1);
    lcd_Edgar.print(Idc, 2);
    lcd_Edgar.setCursor(10, 1);
    lcd_Edgar.print("A");
    float poten = voltaje_sensado * Idc;
    lcd_Edgar.setCursor(11,1);
    lcd_Edgar.print(poten);
    lcd_Edgar.setCursor(15,1);
    lcd_Edgar.print("P");
    delay(3000);
  }
  else {
    lcd_Edgar.clear();
    lcd_Edgar.setCursor(1, 0);
    lcd_Edgar.print("EEGSA - Kinal");
    lcd_Edgar.setCursor(2, 1);
    lcd_Edgar.print("Desconocido");
    Serial.println(" Usuario Invalido");
    delay(1000);
    mfrc522.PICC_HaltA();
  }
  //Ubicamos nuestra lcd
  lcd_Edgar.clear();
  lcd_Edgar.setCursor(1, 0);
  lcd_Edgar.print("EEGSA - Kinal");
  lcd_Edgar.setCursor(1, 1);
  lcd_Edgar.print("Medidor Energia");
}
boolean comparaUID(byte lectura[], byte usuario[]) {
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (lectura[i] != usuario[i])
      return (false);
  }
  return (true);
}

void funcionamiento_voltaje() {
  raw_sensor = analogRead(V_pin);
  voltaje_sensado = fmap(raw_sensor, 0, 1023, 0.0, 25.0);
  //delay(1000);
}
int fmap(int x, int in_min, int in_max, int out_min, int out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void tiempo_reloj() {
  DateTime now = rtc.now();
  Serial.print("  Hora de acceso: ");
  Serial.print(now.hour(), DEC);
  Serial.print(":");
  Serial.println(now.minute(), DEC);
  //delay(1000);
}

float calculoCorriente(int numero_Muestras) {
  float leerAcs712 = 0;
  float intensidad = 0;
  for (int i = 0; i < numero_Muestras; i++) {
    leerAcs712 = analogRead(A1) * (5.02 / 1023);
    intensidad = intensidad + (leerAcs712 - 2.5) / Sensibilidad;
  }
  intensidad = intensidad / numero_Muestras;
  return (intensidad);
}
