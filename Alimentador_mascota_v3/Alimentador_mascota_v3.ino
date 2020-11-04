
//CONEXIONES DE LOS PINS
// sensor de proximidad 6 y 7
// transistor de motor pin 3
//transistor de bomba pin 5


#define Pecho 6
#define Ptrig 7
int motor = 3;
int i;
long duracion, distancia;   
int duracion_bomba_encendida=  10;       //en segundos     , el tiempo que la bomba bombea agua
int distancia_deteccion =  20     ;      //en centimetros  , l adistancia a la que se activa el proceso de alimentar
float tiempo_entre_lecturas = 10;           //en minutos ,  el tiempo que esta inactivo el sensor 
float duracion_motor_activado = 3;       //en segundos
int bomba=5;

void setup() {                
  Serial.begin (9600);       // inicializa el puerto seria a 9600 baudios
  pinMode(Pecho, INPUT);     // define el pin 6 como entrada (echo)
  pinMode(Ptrig, OUTPUT);    // define el pin 7 como salida  (triger)
  pinMode(13, 1);            // Define el pin 13 como salida
  pinMode(4, 1); 
  pinMode(motor, OUTPUT); 
  analogWrite(motor,0);  
  pinMode(bomba, OUTPUT); 
  analogWrite(bomba,0); 

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

   //SE EJECUTA EL PROCESO PRINCIPAL
   if (distancia <= distancia_deteccion && distancia >= 1){
    digitalWrite(4, 0); 

    //BOMBEO AGUA
    Serial.print("Accionando bomba durante:  ");         // envia la palabra Alarma por el puerto serial    
    Serial.println(duracion_bomba_encendida);
    analogWrite(bomba, 150);
    delay(duracion_bomba_encendida * 1000);
    analogWrite(bomba, 0);
    Serial.println(" bomba apagada ");
     
 
    //ACTIVACION MOTOR 
    Serial.print(" Activacion de motor por ");
    Serial.println(duracion_motor_activado);
    analogWrite(motor, 220);
    delay(duracion_motor_activado * 1000);
    analogWrite(motor, 0);
    Serial.println("motor desactivado");

    Serial.print("proceso desactivado durante ");
    Serial.print(tiempo_entre_lecturas);
    Serial.println(" minutos ");
    delay(tiempo_entre_lecturas * 60000 );   //tiempo hasta que se puede volver a activar el proceso
    Serial.println("Se reactiva lectura ");
   
  }
  delay(400);                                // espera 400ms para que se logre ver la distancia en la consola

  
}
