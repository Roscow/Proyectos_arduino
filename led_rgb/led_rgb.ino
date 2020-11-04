


int ledRojo=9;
int ledVerde=10;
int ledAzul=11;
int i;




void setup() {
  //pin del led
  pinMode(ledRojo,OUTPUT );
  pinMode(ledVerde,OUTPUT );
  pinMode(ledAzul,OUTPUT );
}

void loop() {
  //led verde 
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
     
    //led rojo
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
    

   //led azul
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
