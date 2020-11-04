


int ledRojo=9;
int ledVerde=10;
int ledAzul=11;

void setup(){ 
  pinMode(ledRojo,OUTPUT);
  pinMode(ledVerde,OUTPUT);
  pinMode(ledAzul,OUTPUT);
  
}
int i;

void loop(){

  //ver distintas tonalidades de rojo
  for(i=0;i<=255;i++){
    analogWrite(ledRojo,i);
    analogWrite(ledVerde,0);
    analogWrite(ledAzul,0);
    delay(100);
  }


//ver distintas tonalidades de azul
  for(i=0;i<=255;i++){
    analogWrite(ledRojo,0);
    analogWrite(ledVerde,0);
    analogWrite(ledAzul,i);
    delay(100);
  }

  //ver distintas tonalidades de verde
  for(i=0;i<=255;i++){
    analogWrite(ledRojo,0);
    analogWrite(ledVerde,i);
    analogWrite(ledAzul,0);
    delay(100);
  }

//verde sube azul baja
int j=255;
  for(i=0;i<=255;i++){
    analogWrite(ledRojo,0);
    analogWrite(ledVerde,i);
    analogWrite(ledAzul,j);
    j--;
    delay(100);
  }





  //prender rojo
  analogWrite(ledRojo,255);
  analogWrite(ledVerde,0);
  analogWrite(ledAzul,0);
  delay(2000);

  //prender verde
  analogWrite(ledRojo,0);
  analogWrite(ledVerde,255);
  analogWrite(ledAzul,0);
  delay(2000);

  
  //prender azul
  analogWrite(ledRojo,0);
  analogWrite(ledVerde,0);
  analogWrite(ledAzul,255);
  delay(2000);


  //prender azul y rojo (violeta)
  analogWrite(ledRojo,255);
  analogWrite(ledVerde,0);
  analogWrite(ledAzul,255);
  delay(2000);



  

  //prender azul y verde (??)
  analogWrite(ledRojo,0);
  analogWrite(ledVerde,255);
  analogWrite(ledAzul,255);
  delay(2000);

  //prender rojo y verde (cafe)
  analogWrite(ledRojo,255);
  analogWrite(ledVerde,255);
  analogWrite(ledAzul,0);
  delay(2000);


  
}
