#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int buzzer=11;
const int waterlevel = 13; 
const int ldrPin = A2;
#include <DS1302.h>
int Relay = 5;
DS1302 rtc(8, 9, 10);

#include <DHT.h> 
DHT dht(7, DHT11); 

#define fan 2
int levelState = 1;
void setup() {
  pinMode(waterlevel,INPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(buzzer, OUTPUT);
  rtc.halt(false);
  rtc.writeProtect(false);
  
  pinMode(ldrPin, INPUT);
  pinMode(Relay,OUTPUT);
  digitalWrite(Relay, LOW);
   
  pinMode(fan,OUTPUT);
  digitalWrite(fan,HIGH);
  lcd.init();
  lcd.backlight();
  dht.begin();

  lcd.setCursor (0,0);
  lcd.print("Welcome......");
  delay(2000);
  lcd.clear();
  lcd.setCursor (0,0);
  lcd.print("Project By :- ");
  lcd.setCursor (0,1);
  lcd.print("  Krishanthan");
  delay(4000);
  lcd.clear();
}

void loop() { 
 int ldrStatus = analogRead(ldrPin);
 byte hum = dht.readHumidity();
 byte temp = dht.readTemperature();
 levelState = digitalRead(waterlevel);
 Serial.print("temperature: ");
 Serial.println(temp);
 Serial.print("humidity: ");
 Serial.print(hum);
 lcd.setCursor (0,0);
 lcd.print("temp:");
 lcd.print(temp);
 lcd.print("|hum:");
 lcd.print(hum); 
 
 lcd.setCursor(0, 1);
 lcd.print("|W Level:");
delay(100);
 if (temp >= 30){
    digitalWrite(fan,LOW);//for fan on
}
 else {
  digitalWrite(fan,HIGH);// for fan off

 }
                        
  

 if (levelState == HIGH) {
  digitalWrite(buzzer, HIGH);   
  delay(100);
  lcd.print("Low  ");
  }
  
  else  {
    lcd.print("HIGH");
    digitalWrite(buzzer,LOW);
  }
  
 if (ldrStatus <= 200) {

    digitalWrite(Relay, LOW);

  } 
 else {

    digitalWrite(Relay, HIGH);

}
  
}
