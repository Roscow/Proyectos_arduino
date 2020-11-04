#include <LiquidCrystal_I2C.h> 
//lcd verde funciona con direccion (0x27,16,2)
//lcd azul funciona con direccion 

int ledRojo=9;
int ledVerde=10;
int ledAzul=11;
int i;
int ventilador=12;
int calefactor=13;


String estado="base";

 LiquidCrystal_I2C lcd(0x27,16,2) ; // si no te sale con esta direccion  puedes usar (0x3f,16,2) || (0x27,16,2)  ||(0x20,16,2) 
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

  //pin de ventilador y calefcator
  pinMode(ventilador,OUTPUT );
  pinMode(calefactor,OUTPUT );

  
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Tem:00 "); 
  lcd.setCursor (8,0);
  lcd.print("Hum:00 ");
  lcd.setCursor(0,1);
  lcd.print("Estado: ");
  
}

void loop(){
  //delay(5000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

/*
  //solo para prueba activar cada relay por 3 segundos
  digitalWrite(ventilador,1);
  delay(3*1000);
  digitalWrite(ventilador,0);
  digitalWrite(calefactor,1);
  delay(3*1000);
  digitalWrite(calefactor,0);
  */

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
      //se desactiva ventilador y calefactor
        digitalWrite(calefactor,0);
        digitalWrite(ventilador,0);
        
      estado="agradable";
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
        //se activa el ventilador se apaga calefactor
        digitalWrite(calefactor,0);
        digitalWrite(ventilador,1);
      
       estado="calor    ";
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
        //se desactiva ventilador se activa calefactor
        digitalWrite(calefactor,1);
        digitalWrite(ventilador,0);
        estado="frio     ";
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

  
  //mostrar datos por lcd
  lcd.setCursor(4,0);
  lcd.print(int(t)); 
  lcd.setCursor (12,0);
  lcd.print(int(h));
  lcd.display();
  lcd.setCursor(7,1);
  lcd.print(estado);
  

  
  //calcular sensacion termica
  float st = dht.computeHeatIndex(t,h,false);
  Serial.print("Sensacion termica : ");
  Serial.println(st);
  Serial.println("---------------------------------------------");

 
  
}
