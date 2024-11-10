#include <LiquidCrystal_I2C.h>

// Sensor Pins
int TRIG = 9;
int ECO = 10;
// Button Pin
int button = 8;

float duracion;
float distancia;
float altura = 200;
float df;
LiquidCrystal_I2C lcd(0x27,16,2);
int pulsaciones = 0;
bool firstPress = true;
int totaldistancia=0;

void setup(){
  
  pinMode(TRIG,OUTPUT);
  pinMode(ECO,INPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(button,INPUT_PULLUP);
  lcd.setCursor(0,0);
  lcd.print("Altura: 0cm");
  lcd.setCursor(0,1);
  lcd.print("P:0");
}
void loop(){
  if(digitalRead(button) == LOW)
  {
    delay(700);
    pulsaciones++;
    if (pulsaciones % 1 == 0){
      df = altura - distancia;
      totaldistancia += df;
      Serial.println("Altura:");
      Serial.print(df);
      Serial.println("cm");
      Serial.println("Pulsaciones: ");
      Serial.print(pulsaciones);
      Serial.println();
      Serial.println("Promedio: ");
      if (135<(totaldistancia/(pulsaciones/1))<200)
      {
        Serial.print(totaldistancia/(pulsaciones/1));
        Serial.println("cm");
      }
      lcd.setCursor(0,0);
      lcd.print("Altura: ");
      lcd.print(df);
      lcd.print("cm");
      lcd.setCursor(0,1);
      lcd.print("P:");
      lcd.print(pulsaciones/1);
      lcd.setCursor(5,1);
    }
  }
  digitalWrite(TRIG, HIGH);
  delay(1);
  digitalWrite(TRIG,LOW);
  duracion = pulseIn(ECO, HIGH);
  distancia = (duracion/58.2);
}
// by vstian
