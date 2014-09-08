int led = 4;
int buzzer = 9;
int btsonnette = 8;
int btok = 7;

int active = 0;
unsigned long delai = 300000;
unsigned long previousMillis = 0;

void sonne() { 
  tone(buzzer,411);
  delay(150);
  tone(buzzer,611);
  delay(150);
  noTone(buzzer);
}

void setup() {                
  pinMode(led, OUTPUT);     
  pinMode(btsonnette, INPUT);     
  pinMode(btok, INPUT);
}

void loop() {
  if(digitalRead(btsonnette)) {
    unsigned long currentMillis = millis();
    if(((unsigned long)(currentMillis - previousMillis) >= delai) | !active) {
      active++;
    }
    previousMillis = currentMillis;
    sonne();
  }
  if(digitalRead(btok)) {
    digitalWrite(led,LOW);
    delay(1000);    
    for(int i=0; i < active; i++) {
      digitalWrite(led,HIGH);
      delay(350);
      digitalWrite(led,LOW);
      delay(350);
    }
    active=0;
  }
  if(active)
    digitalWrite(led,HIGH);
}
