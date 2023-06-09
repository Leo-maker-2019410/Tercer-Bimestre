
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd_Edgar(0x27, 16, 2);
float Vout, dato, arriba, R1;
void setup() {
  lcd_Edgar.init();
  lcd_Edgar.backlight();
  lcd_Edgar.setCursor(3, 0);
  lcd_Edgar.print("Ohmimetro");
  lcd_Edgar.setCursor(0,1);
  lcd_Edgar.print("Omhios:");
}

void loop() {
  Vout = analogRead(A0);
  Vout = ((5 * Vout) / 1023);
  if (Vout) {
    dato = 5 - Vout;
    arriba = Vout;
    R1 = (dato / arriba) * 10000;
    lcd_Edgar.setCursor(7,1);
    lcd_Edgar.print("          ");
    lcd_Edgar.setCursor(7,1);
    lcd_Edgar.print(R1);
    delay(300);
  }
}
