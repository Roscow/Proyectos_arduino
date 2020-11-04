
int ledRojo=9;
int ledVerde=10;
int ledAzul=11;
 int i;
//LIBRERIA PARA USAR EL SENSOR DE TEMPERATURA
#include "DHT.h"

//definir que se usara el pin 2 para esto
#define DHTPIN 2

//definir el tipo de sensor
#define DHTTYPE DHT11

//inicializar sensor 
DHT dht(DHTPIN, DHTTYPE);

void setup(){
  Serial.begin(9600);
  dht.begin();

  //pin del led
  pinMode(ledRojo,OUTPUT );
  pinMode(ledVerde,OUTPUT );
  pinMode(ledAzul,OUTPUT );
  
}

void loop(){
  //delay(5000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);


  //mostrar datos por serial 
  Serial.println("---------------------------------------------");
  Serial.print("temperatura: ");
  Serial.println(t);
  Serial.print("humedad: ");
  Serial.println(h);


  if ( isnan(h) || isnan(t) ){
    Serial.println("error de lectura");
    return;
  }
  else{

    //temperatura normal agradable de 15 a 26 grados
    if(t>=15 && t<=26 ){
     
      for(i=0;i<=200;i++){
        analogWrite(ledAzul ,0 );
        analogWrite(ledRojo ,0);
        analogWrite(ledVerde ,i);
        delay(12);
       }     
      for(i=200;i>0;i--){
        analogWrite(ledAzul ,0 );
        analogWrite(ledRojo ,0);
        analogWrite(ledVerde ,i);
        delay(12);
       } 
       
    }

    //temperatura calor (rojo)
    if(t>26){
       for(i=0;i<=200;i++){
        analogWrite(ledAzul ,0 );
        analogWrite(ledRojo ,i);
        analogWrite(ledVerde ,0);
        delay(12);
       }     
      for(i=200;i>0;i--){
        analogWrite(ledAzul ,0 );
        analogWrite(ledRojo ,i);
        analogWrite(ledVerde ,0);
        delay(12);
       } 
    }

    //temperatura fria (azul)
    if(t<15){
         for(i=0;i<=200;i++){
        analogWrite(ledAzul ,i );
        analogWrite(ledRojo ,0);
        analogWrite(ledVerde ,0);
        delay(12);
       }     
      for(i=200;i>0;i--){
        analogWrite(ledAzul ,i);
        analogWrite(ledRojo ,0);
        analogWrite(ledVerde ,0);
        delay(12);
       } 
    }
    
    
  }

  
  //calcular sensacion termica
  float st = dht.computeHeatIndex(t,h,false);
  Serial.print("Sensacion termica : ");
  Serial.println(st);
  Serial.println("---------------------------------------------");

 
  
}
