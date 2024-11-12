#include <LiquidCrystal_I2C.h>

// Constantes
// Pines de los sensores y del boton 
const int TRIG = 9;
const int ECO = 10;
const int BUTTON = 8;

// Alutra a la cual se encuentra el sensor
const float altura = 200;

LiquidCrystal_I2C lcd(0x27,16,2);

unsigned long duracion;
float distancia;
float promedio;
float df;
int pulsaciones = 0;
int totaldistancia=0;

void imprimir_pantalla();

void setup(){
  pinMode(TRIG,OUTPUT);
  pinMode(ECO,INPUT);
  pinMode(BUTTON,INPUT_PULLUP);
  Serial.begin(9600);
	
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Altura: 0cm");
  lcd.setCursor(0,1);
  lcd.print("P:0");
}

void loop(){
  if(digitalRead(BUTTON) == LOW)
  {
    delay(700);
    pulsaciones++;
    if (pulsaciones % 1 == 0){
      df = altura - distancia;
      totaldistancia += df;
			promedio = totaldistancia / pulsaciones;
			imprimir_pantalla(df, pulsaciones, promedio);
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

void imprimir_pantalla(float altura, int pulsaciones, float promedio)
{
	Serial.println("Altura:");
	Serial.print(altura);
	Serial.println("cm");

	Serial.println("Pulsaciones: ");
	Serial.print(pulsaciones);
	Serial.println();
	
	Serial.println("Promedio: ");
	Serial.println(promedio);
}
// by vstian
