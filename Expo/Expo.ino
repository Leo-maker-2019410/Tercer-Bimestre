#include <Servo.h> // Se incluye la libreria para el control del Servo
#define Rele 12 //Pin para rele
#define servo 9 //Pin para servo
int agua; //variable para controlar sensor de agua
char info;  //Variable para poder obtener informacion con el bluetooth

Servo myservo; //Le damos un nombre a nuestro servo

void setup() {
  Serial.begin(9600); //Se inicia el monitor Serial 
  pinMode(Rele, OUTPUT); //Se declara como pin de salida al rele
  digitalWrite(Rele, HIGH); //Iniciamos nuestro rele como apagado
  myservo.attach(servo, 1000, 2000); //Iniciamos nuestro servo
  myservo.write(180); //Iniciamos nuestro servo con un angulo de 180
}

void loop() {
  if (Serial.available() > 0) { //Se hace la comunicacion con nuestro bluetooth
    info = Serial.read();
    Serial.println(info);
  }
  funcionamiento_de_agua();//funcion donde le damos nombre al pin analogico que controla el sensor de agua
  if (info == 'A') { //Si nuestra variable recibe la letra A
    digitalWrite(Rele, LOW); //El rele se encendera
  }
  apagado(); //Funcion para apagar el rele
  if(info == 'B'){ //Si la variable info recibe la letra B
  abierto(); // Se realiza lo que hay en la funcion abrir
  }
  if(info == 'C'){ //Si la variable info recibe la letra C
    cerrado(); //Se realiza lo que hay en la funcion cerrar
  }
}

void funcionamiento_de_agua() {
  agua = analogRead(A6); //Se declara el pin A6 a nuestra variable agua
  Serial.println(agua); //Se imprime agua
  delay(500);
}

void apagado(){ //Funcion para apagar la bomba
  if(agua >= 350){ //Si el sensor detecta valores mayores o iguales a 350
    digitalWrite(Rele,HIGH); //Se apagara la bomba
  }
}

void abierto(){ //Funcion para abrir el servo
  myservo.write(0); //Realizara un angulo de cero grados
}

void cerrado(){ //Funcion para cerrar el servo
  myservo.write(180); //Se realiza un angulo de 180
}
