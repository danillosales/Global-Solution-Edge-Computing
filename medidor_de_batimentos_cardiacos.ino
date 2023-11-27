#include <LiquidCrystal.h>
LiquidCrystal lcd (12,11,10,9,8,7);

int pinTemp = A1;
float temperaturaC = 0.0;
int valorTemp=0;

int pinBtn = 2;
int estadoBtn = 0;
int ultimoEstadoBtn = LOW;
boolean modoMedicao = false;


int pinLEDred = 4;
int pinLEDgreen = 5;


unsigned long tempoInicial = 0;
const unsigned long duracaoMaxima = 20000;

boolean sistemaDesligado = false;

void setup()
{
  pinMode(pinTemp, INPUT);
  pinMode(pinBtn, INPUT);
  Serial.begin(9600);
  pinMode(pinLEDred,OUTPUT);
  pinMode(pinLEDgreen,OUTPUT);
  lcd.begin(16, 2);
  randomSeed(analogRead(0));
  
  lcd.setCursor(0, 0);
  lcd.print("Sis. Desligado");
  delay(2000);
 
}

void loop()
{
  estadoBtn = digitalRead(pinBtn);
  if (estadoBtn != ultimoEstadoBtn) {
    if (estadoBtn == HIGH) {
      modoMedicao = !modoMedicao;
      tempoInicial = millis(); 
      sistemaDesligado = false; 
    }
    delay(50);
  }
  
      
  ultimoEstadoBtn = estadoBtn;    
      
  if (modoMedicao == true && (millis() - tempoInicial < duracaoMaxima)){    
    digitalWrite(pinLEDgreen,HIGH);
    digitalWrite(pinLEDred,LOW);
    
    valorTemp=analogRead(pinTemp);
    float voltagem = valorTemp * (5.0 / 1023.0) * 1000; 
    temperaturaC = (voltagem - 500) / 10.0;
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperaturaC);
    lcd.print(" C");
    
    int batimentos = random(60, 121);
    lcd.setCursor(0, 1);
    lcd.print("Bat: ");
    lcd.print(batimentos);
    lcd.print(" bpm");
    delay(2000);
    Serial.print(modoMedicao);
  }else{
     modoMedicao = false;
     digitalWrite(pinLEDred, HIGH);
     digitalWrite(pinLEDgreen, LOW);
     if (!sistemaDesligado) { // Verifica se o sistema já está desligado
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print("Sis. Desligado");
       sistemaDesligado = true; // Marca que o sistema foi desligado
     }
      delay(100);
  }
}