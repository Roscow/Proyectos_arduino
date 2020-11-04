#include <LiquidCrystal_I2C.h> 

//led verde funciona con direccion (0x27,16,2)
//led azul funciona con direccion 

LiquidCrystal_I2C lcd(0x27,16,2) ; // si no te sale con esta direccion  puedes usar (0x3f,16,2) || (0x27,16,2)  ||(0x20,16,2) 
void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
 lcd.setCursor(0,0);
  lcd.print(" BUEN DIA "); 
  lcd.setCursor (0,1);
  lcd.print(" PRECIOSA ");
}
void loop() { 
  delay(2000);
  lcd.setCursor(0,0);
  lcd.print(" Te quiero "); 
  lcd.setCursor (0,1);
  lcd.print("mucho ");
  lcd.display();
  delay(500);
  lcd.noDisplay();
  delay(500);
}
