/*  
  Fundacion Kinal
  Centro educativo tecnico laboral Kinal
  Electronica
  Grado: Quinto
  Sección: A
  Curso: Taller de electronica digital y reparación de computadoras I
  ombre: Álvaro Anzueto Rodas y Edgar Ramírez
  Carnet: 2019373 y 2019...
  Proyecto: Comunicacion serial - Aplicación para encender o apagar un led y dar la temperatura
*/

//Librerías
#include <Wire.h> //Para ocmunicación I2C
#include <PCF8574.h> //Para crackear el módulo I2C :v

//Directivas de preprocesador
#define expansor_HIGH LOW
#define expansor_LOW HIGH
#define LED0  0 //Zacapa//
#define LED1 1 //Peten//
#define LED2 2 //Izabal//
#define LED7 7 //Chiquimula//
#define LED4 4 //Jutiapa//
#define LED5 5 //El Progreso//
#define LED6 6 //Jalapa//
#define Buzzer_pin 10
#define timeON 2500
#define encender(pin) digitalWrite(pin, HIGH)
#define apagar(pin) digitalWrite(pin, LOW)
#define cH 523
#define cSH 554

//Constructor
PCF8574 expansor_mapa(0x27); //Dirección del expansor de pines

//Variables
byte pregunta_num; //Numero de pregunta y el tiempo de encendido del led
String respuesta; //Se guadará la respuesta escrita

//Funciones
void cuestionario(), respuesta_conteo();

void setup() {
  Serial.begin(9600); //Comunicación Serial
  expansor_mapa.begin(); //Inicia el expansor
  for (int i = 2; i < 17; i++) //Contador de los pines 2 al 16(A3)
  {
    pinMode(i, OUTPUT); //Se declaran como salidas
    digitalWrite(i, LOW); 
  }
  Serial.println("Juego de preguntas, estás listo?");
//  apagado();
}

void loop() {
  pregunta_num = random(1, 22);//El numero de pregunta es un número random del 1 al 22
  cuestionario();
}

void apagado(){
  for (int i = 2; i < 17; i++) //Contador de los pines 2 al 16(A3)
  {
    digitalWrite(i, LOW); //Se declaran como salidas
  }
  expansor_mapa.write(LED0,expansor_LOW);
  expansor_mapa.write(LED1,expansor_LOW);
  expansor_mapa.write(LED2,expansor_LOW);
  expansor_mapa.write(LED7,expansor_LOW);
  expansor_mapa.write(LED4,expansor_LOW);
  expansor_mapa.write(LED5,expansor_LOW);
  expansor_mapa.write(LED6,expansor_LOW);
}

void respuesta_conteo() {
  bool tiempo = false; //Estado en que se define si sigue la cuenta o no
  int segundos = 20; //Segundos para el conteo si no responde

  while ((!Serial.available() > 0) && tiempo == false) //Mientras no haya comunicación y cuando hay cuenta
  { Serial.print(segundos); //Va mostrando la cuenta
    Serial.print("... "); // con un caracter separado
    delay(1000); //Por cada segundo
    segundos--;//Se restando la cuenta
    if (segundos < 0) { //Cuando haya terminado la cuenta
      tiempo  = true;
      Serial.println();
      Serial.println(F("¡TIEMPO FUERA!")); //Tira el mensaje
      respuesta_incorrecta();
      
    }
  }
  Serial.println(); //Se espera la respuesta
  respuesta = Serial.readStringUntil('\n'); //Se escribe la respuesta y se guarda en el String

}

void cuestionario() {
  switch (pregunta_num) { //Dependiendo del número de pregunta
    case 1:                                                                     //Petén//
      Serial.println(F("¿Cuál es la cabecera de Peten?")); //Tira la pregunta
      respuesta_conteo(); //Responde
      if (respuesta == String("Flores")) { //Si la respuesta coincide
        expansor_mapa.write(LED0, expansor_HIGH); //Enciende el led y espera casi 3 segundos
        delay(timeON);
        expansor_mapa.write(LED0, expansor_LOW); //Apaga el led
      }
      else { //Si no coincide
        Serial.println("¡Incorrecta! - La respuesta es Flores"); //Se corrige la respuesta
        respuesta_incorrecta();//Inicia el buzzer
      }
      break;

    case 2:                                                                     //Izabal//
      Serial.println(F("¿Cuál es la cabecera de Izabal?")); //Tira la pregunta
      respuesta_conteo(); //Responde
      if (respuesta == String("Puerto barrios")) { //Si la respuesta coincide
        expansor_mapa.write(LED7, expansor_HIGH); //Enciende el led y espera casi 3 segundos
        delay(timeON);
        expansor_mapa.write(LED7, expansor_LOW); //Apaga el led
      }
      else { //Si no coincide
        Serial.println("¡Incorrecta! - La respuesta es Puerto barrios"); //Se corrige la respuesta
        respuesta_incorrecta();//Inicia el buzzer
      }
      break;

    case 3:                                                                     //Alta Verapaz//
      Serial.println(F("¿Cuál es la cabecera de Alta Verapaz?")); //Tira la pregunta
      respuesta_conteo(); //Responde
      if (respuesta == String("Coban")) { //Si la respuesta coincide
        encender(13); //Enciende el led y espera casi 3 segundos
        delay(timeON);
        apagar(13); //Apaga el led
      }
      else { //Si no coincide
        Serial.println("¡Incorrecta! - La respuesta es Coban"); //Se corrige la respuesta
        respuesta_incorrecta();//Inicia el buzzer
      }
      break;

    case 4:                                                                     //Quiché//
      Serial.println(F("¿Cuál es la cabecera de Quiche?")); //Tira la pregunta
      respuesta_conteo(); //Responde
      if (respuesta == String("Santa cruz del quiche")) { //Si la respuesta coincide
        encender(A1); //Enciende el led y espera casi 3 segundos
        delay(timeON);
        apagar(A1); //Apaga el led
      }
      else { //Si no coincide
        Serial.println("¡Incorrecta! - La respuesta es Santa cruz del quiche"); //Se corrige la respuesta
        respuesta_incorrecta();//Inicia el buzzer
      }
      break;

    case 5:                                                                     //Huehuetenango//
      Serial.println(F("¿Cuál es la cabecera de Huehuetenango?")); //Tira la pregunta
      respuesta_conteo(); //Responde
      if (respuesta == String("Huehuetenango")) { //Si la respuesta coincide
          encender(3); //Enciende el led y espera casi 3 segundos
        delay(timeON);
        apagar(3); //Apaga el led
      }
      else { //Si no coincide
        Serial.println("¡Incorrecta! - La respuesta es Huehuetenango"); //Se corrige la respuesta
        respuesta_incorrecta();//Inicia el buzzer
      }
      break;

    case 6:                                                                     //Escuintla//
      Serial.println(F("¿Cuál es la cabecera de Escuintla?")); //Tira la pregunta
      respuesta_conteo(); //Responde
      if (respuesta == String("Escuintla")) { //Si la respuesta coincide
        encender(5); //Enciende el led y espera casi 3 segundos
        delay(timeON);
        apagar(5); //Apaga el led
      }
      else { //Si no coincide
        Serial.println("¡Incorrecta! - La respuesta es Escuintla"); //Se corrige la respuesta
        respuesta_incorrecta();//Inicia el buzzer
      }
      break;

    case 7:                                                                     //San Marcos//
      Serial.println(F("¿Cuál es la cabecera de San Marcos?")); //Tira la pregunta
      respuesta_conteo(); //Responde
      if (respuesta == String("San marcos")) { //Si la respuesta coincide
        encender(A0); //Enciende el led y espera casi 3 segundos
        delay(timeON);
        apagar(A0); //Apaga el led
      }
      else { //Si no coincide
        Serial.println("¡Incorrecta! - La respuesta es San marcos"); //Se corrige la respuesta
        respuesta_incorrecta();//Inicia el buzzer
      }
      break;

    case 8:                                                                     //Jutiapa//
      Serial.println(F("¿Cuál es la cabecera de Jutiapa?")); //Tira la pregunta
      respuesta_conteo(); //Responde
      if (respuesta == String("Jutiapa")) { //Si la respuesta coincide
        expansor_mapa.write(LED4, expansor_HIGH); //Enciende el led y espera casi 3 segundos
        delay(timeON);
        expansor_mapa.write(LED4, expansor_LOW); //Apaga el led
      }
      else { //Si no coincide
        Serial.println("¡Incorrecta! - La respuesta es Jutiapa"); //Se corrige la respuesta
        respuesta_incorrecta();//Inicia el buzzer
      }
      break;

    case 9:                                                                     //Baja Verapaz//
      Serial.println(F("¿Cuál es la cabecera de Baja Verapaz?")); //Tira la pregunta
      respuesta_conteo(); //Responde
      if (respuesta == String("Salama")) { //Si la respuesta coincide
        encender(9); //Enciende el led y espera casi 3 segundos
        delay(timeON);
        apagar(9); //Apaga el led
      }
      else { //Si no coincide
        Serial.println("¡Incorrecta! - La respuesta es Salama"); //Se corrige la respuesta
        respuesta_incorrecta();//Inicia el buzzer
      }
      break;

    case 10:                                                                     //Santa Rosa//
      Serial.println(F("¿Cuál es la cabecera de Santa Rosa?")); //Tira la pregunta
      respuesta_conteo(); //Responde
      if (respuesta == String("Cuilapa")) { //Si la respuesta coincide
        encender(12); //Enciende el led y espera casi 3 segundos
        delay(timeON);
        apagar(12); //Apaga el led
      }
      else { //Si no coincide
        Serial.println("¡Incorrecta! - La respuesta es Cuilapa"); //Se corrige la respuesta
        respuesta_incorrecta();//Inicia el buzzer
      }
      break;

    case 11:                                                                     //Zacapa//
      Serial.println(F("¿Cuál es la cabecera de Zacapa?")); //Tira la pregunta
      respuesta_conteo(); //Responde
      if (respuesta == String("Zacapa")) { //Si la respuesta coincide
        expansor_mapa.write(LED6, expansor_HIGH); //Enciende el led y espera casi 3 segundos
        delay(timeON);
        expansor_mapa.write(LED6, expansor_LOW); //Apaga el led
      }
      else { //Si no coincide
        Serial.println("¡Incorrecta! - La respuesta es Zacapa"); //Se corrige la respuesta
        respuesta_incorrecta();//Inicia el buzzer
      }
      break;

    case 12:                                                                     //Suchitepequez//
      Serial.println(F("¿Cuál es la cabecera de Suchitepequez?")); //Tira la pregunta
      respuesta_conteo(); //Responde
      if (respuesta == String("Mazatenango")) { //Si la respuesta coincide
        encender(2); //Enciende el led y espera casi 3 segundos
        delay(timeON);
        apagar(2); //Apaga el led
      }
      else { //Si no coincide
        Serial.println("¡Incorrecta! - La respuesta es Mazatengango"); //Se corrige la respuesta
        respuesta_incorrecta();//Inicia el buzzer
      }
      break;

    case 13:                                                                     //Chiquimula//
      Serial.println(F("¿Cuál es la cabecera de Chiquimula?")); //Tira la pregunta
      respuesta_conteo(); //Responde
      if (respuesta == String("Chiquimula")) { //Si la respuesta coincide
        expansor_mapa.write(LED5, expansor_HIGH); //Enciende el led y espera casi 3 segundos
        delay(timeON);
        expansor_mapa.write(LED5, expansor_LOW); //Apaga el led
      }
      else { //Si no coincide
        Serial.println("¡Incorrecta! - La respuesta es Chiquimula"); //Se corrige la respuesta
        respuesta_incorrecta();//Inicia el buzzer
      }
      break;

    case 14:                                                                     //Guatemala//
      Serial.println(F("¿Cuál es la cabecera de Guatemala?")); //Tira la pregunta
      respuesta_conteo(); //Responde
      if (respuesta == String("Ciudad de guatemala")) { //Si la respuesta coincide
        encender(11); //Enciende el led y espera casi 3 segundos
        delay(timeON);
        apagar(11); //Apaga el led
      }
      else { //Si no coincide
        Serial.println("¡Incorrecta! - La respuesta es Ciudad de guatemala"); //Se corrige la respuesta
        respuesta_incorrecta();//Inicia el buzzer
      }
      break;

    case 15:                                                                     //Jalapa//
      Serial.println(F("¿Cuál es la cabecera de Jalapa?")); //Tira la pregunta
      respuesta_conteo(); //Responde
      if (respuesta == String("Jalapa")) { //Si la respuesta coincide
        expansor_mapa.write(LED2, expansor_HIGH); //Enciende el led y espera casi 3 segundos
        delay(timeON);
        expansor_mapa.write(LED2, expansor_LOW); //Apaga el led
      }
      else { //Si no coincide
        Serial.println("¡Incorrecta! - La respuesta es Jalapa"); //Se corrige la respuesta
        respuesta_incorrecta();//Inicia el buzzer
      }
      break;
    case 16:                                                                     //Chimaltenango//
      Serial.println(F("¿Cuál es la cabecera de Chimaltenango?")); //Tira la pregunta
      respuesta_conteo(); //Responde
      if (respuesta == String("Chimaltenango")) { //Si la respuesta coincide
        encender(7); //Enciende el led y espera casi 3 segundos
        delay(timeON);
        apagar(7); //Apaga el led
      }
      else { //Si no coincide
        Serial.println("¡Incorrecta! - La respuesta es Chimaltenango"); //Se corrige la respuesta
        respuesta_incorrecta();//Inicia el buzzer
      }
      break;

    case 17:                                                                     //Quetzaltenango//
      Serial.println(F("¿Cuál es la cabecera de Quetzaltenango?")); //Tira la pregunta
      respuesta_conteo(); //Responde
      if (respuesta == String("Quetzaltenango")) { //Si la respuesta coincide
        encender(A2); //Enciende el led y espera casi 3 segundos
        delay(timeON);
        apagar(A2); //Apaga el led
      }
      else { //Si no coincide
        Serial.println("¡Incorrecta! - La respuesta es Quetzaltenango"); //Se corrige la respuesta
        respuesta_incorrecta();//Inicia el buzzer
      }
      break;

    case 18:                                                                     //El Progreso//
      Serial.println(F("¿Cuál es la cabecera de El Progreso?")); //Tira la pregunta
      respuesta_conteo(); //Responde
      if (respuesta == String("Guastatoya")) { //Si la respuesta coincide
        expansor_mapa.write(LED1, expansor_HIGH); //Enciende el led y espera casi 3 segundos
        delay(timeON);
        expansor_mapa.write(LED1, expansor_LOW); //Apaga el led
      }
      else { //Si no coincide
        Serial.println("¡Incorrecta! - La respuesta es Guastatoya"); //Se corrige la respuesta
        respuesta_incorrecta();//Inicia el buzzer
      }
      break;

    case 19:                                                                     //Retalhuleu//
      Serial.println(F("¿Cuál es la cabecera de Retalhuleu?")); //Tira la pregunta
      respuesta_conteo(); //Responde
      if (respuesta == String("Retalhuleu")) { //Si la respuesta coincide
        encender(A3); //Enciende el led y espera casi 3 segundos
        delay(timeON);
        apagar(A3); //Apaga el led
      }
      else { //Si no coincide
        Serial.println("¡Incorrecta! - La respuesta es Retalhuleu"); //Se corrige la respuesta
        respuesta_incorrecta();//Inicia el buzzer
      }
      break;

    case 20:                                                                     //Sololá//
      Serial.println(F("¿Cuál es la cabecera de Solola?")); //Tira la pregunta
      respuesta_conteo(); //Responde
      if (respuesta == String("Solola")) { //Si la respuesta coincide
        encender(4); //Enciende el led y espera casi 3 segundos
        delay(timeON);
        apagar(4); //Apaga el led
      }
      else { //Si no coincide
        Serial.println("¡Incorrecta! - La respuesta es Solola"); //Se corrige la respuesta
        respuesta_incorrecta();//Inicia el buzzer
      }
      break;

    case 21:                                                                     //Totonicapán//
      Serial.println(F("¿Cuál es la cabecera de Totonicapan?")); //Tira la pregunta
      respuesta_conteo(); //Responde
      if (respuesta == String("Totonicapan")) { //Si la respuesta coincide
        encender(6); //Enciende el led y espera casi 3 segundos
        delay(timeON);
        apagar(6); //Apaga el led
      }
      else { //Si no coincide
        Serial.println("¡Incorrecta! - La respuesta es Totonicapan"); //Se corrige la respuesta
        respuesta_incorrecta();//Inicia el buzzer
      }
      break;

    case 22:                                                                     //Sacatepéquez//
      Serial.println(F("¿Cuál es la cabecera de Sacatepequez?")); //Tira la pregunta
      respuesta_conteo(); //Responde
      if (respuesta == String("La Antigua")) { //Si la respuesta coincide
        encender(8); //Enciende el led y espera casi 3 segundos
        delay(timeON);
        apagar(8); //Apaga el led
      }
      else { //Si no coincide
        Serial.println("¡Incorrecta! - La respuesta es La Antigua"); //Se corrige la respuesta
        respuesta_incorrecta();//Inicia el buzzer
      }
      break;
  }
}

void respuesta_incorrecta() {
  tone(Buzzer_pin, cH, 400);
  delay(1000);
  tone(Buzzer_pin, cH, 400);
  delay(1000);
  tone(Buzzer_pin, cSH, 700);
  noTone;
}
