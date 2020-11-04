
#define Pecho 6
#define Ptrig 7
long duracion, distancia; 
float distancia_deteccion =25; //ctms
float  duracion_relay_activado = 4; //segundos

int transistor=3;
 
void setup() {                
  Serial.begin (9600);       // inicializa el puerto seria a 9600 baudios
  pinMode(Pecho, INPUT);     // define el pin 6 como entrada (echo)
  pinMode(Ptrig, OUTPUT);    // define el pin 7 como salida  (triger)
  pinMode(13, 1);            // Define el pin 13 como salida
  pinMode(3, 1); 

  }
  
void loop() {
  
  digitalWrite(Ptrig, LOW);
  delayMicroseconds(2);
  digitalWrite(Ptrig, HIGH);   // genera el pulso de triger por 10ms
  delayMicroseconds(10);
  digitalWrite(Ptrig, LOW);
  
  duracion = pulseIn(Pecho, HIGH);
  distancia = (duracion/2) / 29;            // calcula la distancia en centimetros
  
  if (distancia >= 500 || distancia <= 0){  // si la distancia es mayor a 500cm o menor a 0cm 
    Serial.println("---");                  // no mide nada
  }
  else {
    Serial.print(distancia);           // envia el valor de la distancia por el puerto serial
    Serial.println("cm");              // le coloca a la distancia los centimetros "cm"
    digitalWrite(13, 0);               // en bajo el pin 13
    digitalWrite(4, 1); 
  } 

    //DETECCION DE UN OBJETO
   if (distancia <= distancia_deteccion && distancia >= 1){    
    Serial.println("Alarma.......");         // envia la palabra Alarma por el puerto serial

    //activa motor1 (relay)
    digitalWrite(13, 1);                     // en alto el pin 13 si la distancia es menor a 10cm
    delay(duracion_relay_activado * 1000 );
    digitalWrite(13,0);                       //apago motor
    
    //activa motor2 (transistor)
    analogWrite(transistor, 127);
    delay(duracion_relay_activado * 1000 );
    analogWrite(transistor, 0);
  }
  delay(400);                                // espera 400ms para que se logre ver la distancia en la consola
}
