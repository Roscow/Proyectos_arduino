#include <Servo.h>
 

#define Pecho 6
#define Ptrig 7
long duracion, distancia; 
float distancia_deteccion =25;         //ctms
float  duracion_bomba_activada = 10;   //segundos
float duracion_servo_activado =0.5;      //segundos
float tiempo_entre_lecturas = 10;       //en minutos --20''
Servo servo1;

int angulo_apertura=0, angulo_cierre=50;


//definimos intensidades de la bomba de agua (255 es lo mayor, envia 6 volts, 127 es la mitad=3.46 volts, 195 es alto pero seguro)
int intensidad_maxima=255, intensidad_media =127, intensidad_alta_segura=192;

int transistor=3;
 
void setup() {                
  Serial.begin (9600);       // inicializa el puerto seria a 9600 baudios
  pinMode(Pecho, INPUT);     // define el pin 6 como entrada (echo)
  pinMode(Ptrig, OUTPUT);    // define el pin 7 como salida  (triger)
  pinMode(3, 1); 
  servo1.attach(10);
  servo1.write(angulo_cierre);    //ubicacion de los grados 
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
    digitalWrite(4, 1); 
  } 

    //DETECCION DE UN OBJETO
   if (distancia <= distancia_deteccion && distancia >= 1){    
    Serial.println("Alarma.......");         // envia la palabra Alarma por el puerto serial

    //activa servomotor1 (dos veces)
    servo1.write(angulo_apertura);   //apertura
    delay(duracion_servo_activado * 1000);
    servo1.write(angulo_cierre);    //cierre
    delay(1000);

    servo1.write(angulo_apertura);   //apertura
    delay(duracion_servo_activado * 1000);
    servo1.write(angulo_cierre);    //cierre
   

    //activa motor2 (transistor)
    analogWrite(transistor, intensidad_alta_segura);
    delay(duracion_bomba_activada * 1000 );
    analogWrite(transistor, 0);

    //tiempo entre cada alimentacion
    delay(tiempo_entre_lecturas * 60000);
  }
  delay(400);                                // espera 400ms para que se logre ver la distancia en la consola
}
