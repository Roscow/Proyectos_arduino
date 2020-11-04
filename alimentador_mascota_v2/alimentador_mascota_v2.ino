 /*
Sensor de proximidad y al ser inferior a 10cm 
envia un pulso de alarma por  el pin 13

 HC-SR04 conexiones:
  VCC al arduino 5v 
  GND al arduino GND
  Echo al Arduino pin 6 
  Trig al Arduino pin 7
  
Descargar planos de conexiones en http://elprofegarcia.com/
 */
 
#define Pecho 6
#define Ptrig 7
long duracion, distancia;   
int duracion_bomba_encendida=  10;       //en segundos
int distancia_deteccion =  20     ;      //en centimetros
float tiempo_entre_lecturas = 0.5;           //en minutos
 
void setup() {                
  Serial.begin (9600);       // inicializa el puerto seria a 9600 baudios
  pinMode(Pecho, INPUT);     // define el pin 6 como entrada (echo)
  pinMode(Ptrig, OUTPUT);    // define el pin 7 como salida  (triger)
  pinMode(13, 1);            // Define el pin 13 como salida
  pinMode(4, 1); 

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
    digitalWrite(13, 1);                     // en alto el pin 13 si la distancia es menor a 10cm    
    digitalWrite(4, 0); 
    Serial.print("Accionando bomba durante:  ");         // envia la palabra Alarma por el puerto serial
    Serial.println(duracion_bomba_encendida);
    delay(duracion_bomba_encendida * 1000);    //duracion bomba encendida
    digitalWrite(13, 0);                        //se apaga la bomba nuevamente
    Serial.println(" bomba apagada ");
    Serial.print("proceso desactivado durante ");
    Serial.print(tiempo_entre_lecturas);
    Serial.println(" minutos ");
    delay(tiempo_entre_lecturas * 60000 );   //tiempo hasta que se puede volver a activar el proceso
    Serial.println("Se reactiva lectura ");
    
   
  }
  delay(400);                                // espera 400ms para que se logre ver la distancia en la consola

  
}
