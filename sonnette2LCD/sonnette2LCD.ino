#include <LiquidCrystal.h>

#define RS 12
#define EN 11
#define D4 5
#define D5 3
#define D6 2
#define D7 10

int led = 4;
int buzzer = 9;
int btsonnette = 8;
int btok = 7;
int active = 0;
unsigned long delai = 300000;
unsigned long previousMillis = 0;

LiquidCrystal lcd(RS,EN,D4,D5,D6,D7);

void setup() {  
  pinMode(led, OUTPUT);     
  pinMode(btsonnette, INPUT);     
  pinMode(btok, INPUT);
  lcd.begin(16,2);
  lcd.print("En attente...");
  lcd.setCursor(0,1);
  lcd.print("Aucune visite");
}

void sonne() { 
  tone(buzzer,411);
  delay(150);
  tone(buzzer,611);
  delay(150);
  noTone(buzzer);
}

void loop() {
  if(digitalRead(btsonnette)) {
    unsigned long currentMillis = millis();
    if(((unsigned long)(currentMillis - previousMillis) >= delai) | !active) {
      active++;
      lcd.noDisplay();
      lcd.clear();
      lcd.print("En attente...");
      lcd.setCursor(0,1);
      lcd.print(active,DEC);
      lcd.print(" visite");
      if(active>1)
        lcd.print("s");
      lcd.display();
    }
    previousMillis = currentMillis;
    sonne();
  }
  if(digitalRead(btok)) {
    digitalWrite(led,LOW);
    lcd.noDisplay();
    lcd.clear();
    lcd.print("En attente...");
    lcd.setCursor(0,1);
    lcd.print("Aucune visite");
    lcd.display();
    active=0;
  }
  if(active)
    digitalWrite(led,HIGH);
}
