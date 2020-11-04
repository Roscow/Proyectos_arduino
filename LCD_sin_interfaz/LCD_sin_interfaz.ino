#include <LiquidCrystal.h>

int RS=4;
int E=5; 
int D4=6;
int D5=7;
int D6=8;
int D7=9;
int V0=3;

LiquidCrystal lcd (RS, E, D4, D5, D6, D7);


void setup() {
  analogWrite(V0,130);
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.write("p");
}

void loop() {
  
  int i;
  for(i=0;i<=255;i++){
    analogWrite(V0,i);
    //lcd.begin(16,2);
    lcd.setCursor(0,0);
    lcd.print("cony rica <3 ");


    //mostrar parametros en pantalla
    Serial.println("--------------------------");
    Serial.print("prueba de pwn: ");
    Serial.println(i);
    delay(200);
   
  }
 
}
