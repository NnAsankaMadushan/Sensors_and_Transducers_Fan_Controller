#include <LiquidCrystal.h>
LiquidCrystal lcd(7,6,5,4,3,2);
int tempPin = A0; 
int fan = 11; 
int led = 8; 
int temp;
int tempMin = 25; 
int tempMax = 40; 
int fanSpeed;
int fanLCD;
 
void setup() {
pinMode(fan, OUTPUT);
pinMode(led, OUTPUT);
pinMode(tempPin, INPUT);
lcd.begin(16,2);
Serial.begin(9600);
}
 
void loop()
{
temp = readTemp(); 
Serial.print( temp );
if(temp < tempMin) 
{
fanSpeed = 0; 
analogWrite(fan, fanSpeed);
fanLCD=0;
digitalWrite(fan, LOW);
}
if((temp >= tempMin) && (temp <= tempMax)) 
{
fanSpeed = temp;
fanSpeed=0.15*fanSpeed;
fanLCD = map(temp, tempMin, tempMax, 0, 100); 
analogWrite(fan, fanSpeed); 
}
 
if(temp > tempMax) 
{
digitalWrite(led, HIGH); 
}
else 
{
digitalWrite(led, LOW);
}
 
lcd.print("TEMP: ");
lcd.print(temp); 
lcd.print("C ");
lcd.setCursor(0,1); 
lcd.print("FANS: ");
lcd.print(fanLCD); 
lcd.print("%");
delay(200);
lcd.clear();
}
 
int readTemp() { 
temp = analogRead(tempPin);
return temp * 0.48828125;
}