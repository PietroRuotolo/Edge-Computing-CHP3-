#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
 
// DHT22
#define DHTPIN  4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
 
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
// Pinos
const int pinoLDR      = A2;
const int ledVerde     = 8;
const int ledAmarelo   = 9;
const int ledVermelho  = 10;
const int buzzer       = 11;
 
unsigned long ultimoBuzzer = 0;
bool buzzerLigado = false;
 
// ── Caracteres customizados para o coração ──────────────────────────
// Metade esquerda do coração (5x8 pixels)
byte coracao_esq[8] = {
  0b00000,
  0b00110,
  0b01111,
  0b01111,
  0b01111,
  0b00111,
  0b00011,
  0b00001
};
 
// Metade direita do coração (5x8 pixels)
byte coracao_dir[8] = {
  0b00000,
  0b11000,
  0b11110,
  0b11110,
  0b11110,
  0b11100,
  0b11000,
  0b10000
};
 
void animacaoCoracao() {
  lcd.createChar(0, coracao_esq);
  lcd.createChar(1, coracao_dir);
 
  // Pisca o coração 3 vezes
  for (int i = 0; i < 3; i++) {
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.write((uint8_t)0);   // metade esquerda
    lcd.write((uint8_t)1);   // metade direita
    lcd.setCursor(4, 1);
    lcd.print("Vinheria!");
    delay(500);
 
    lcd.clear();
    delay(300);
  }
 
  // Exibe coração fixo por 1 segundo antes de continuar
  lcd.setCursor(7, 0);
  lcd.write((uint8_t)0);
  lcd.write((uint8_t)1);
  lcd.setCursor(4, 1);
  lcd.print("Vinheria!");
  delay(1000);
  lcd.clear();
}
// ────────────────────────────────────────────────────────────────────
 
bool exibirMensagemLCD(int nivelTemp, int nivelUmid, int nivelLuz,
                        float tempC, float umidade, int luzPercent) {
 
  if (nivelLuz == 2) {
    lcd.setCursor(0, 0); lcd.print("CRITICO         ");
    lcd.setCursor(0, 1);
    lcd.print("LUZ ALTA:");
    lcd.print(luzPercent);
    lcd.print("%      ");
    return true;
  }
  if (nivelTemp == 2) {
    lcd.setCursor(0, 0); lcd.print("CRITICO         ");
    lcd.setCursor(0, 1);
    lcd.print("TEMP ALTA:");
    lcd.print(tempC, 1);
    lcd.print("C   ");
    return true;
  }
  if (nivelUmid == 2) {
    lcd.setCursor(0, 0); lcd.print("CRITICO         ");
    lcd.setCursor(0, 1);
    if (umidade < 40) {
      lcd.print("UMID BAIXA:");
      lcd.print((int)umidade);
      lcd.print("%  ");
    } else {
      lcd.print("UMID ALTA:");
      lcd.print((int)umidade);
      lcd.print("%   ");
    }
    return true;
  }
  if (nivelTemp == 1) {
    lcd.setCursor(0, 0); lcd.print("ALERTA          ");
    lcd.setCursor(0, 1);
    lcd.print("TEMP:");
    lcd.print(tempC, 1);
    lcd.print("C ACIMA ");
    return true;
  }
  if (nivelUmid == 1) {
    lcd.setCursor(0, 0); lcd.print("ALERTA          ");
    lcd.setCursor(0, 1);
    if (umidade < 50) {
      lcd.print("UMID BAIXA:");
      lcd.print((int)umidade);
      lcd.print("%  ");
    } else {
      lcd.print("UMID ALTA:");
      lcd.print((int)umidade);
      lcd.print("%   ");
    }
    return true;
  }
  if (nivelLuz == 1) {
    lcd.setCursor(0, 0); lcd.print("ALERTA          ");
    lcd.setCursor(0, 1);
    lcd.print("LUZ:");
    lcd.print(luzPercent);
    lcd.print("% ACIMA    ");
    return true;
  }
 
  lcd.setCursor(0, 0); lcd.print("                ");
  lcd.setCursor(0, 1); lcd.print("  Status: OK!!  ");
  return false;
}
 
void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();
 
  pinMode(ledVerde,    OUTPUT);
  pinMode(ledAmarelo,  OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(buzzer,      OUTPUT);
 
  lcd.print("Vinheria Agnello");
  delay(2000);
  lcd.clear();
 
  animacaoCoracao();   // ← coração pisca aqui antes do loop
}
void loop() {
  float tempC   = dht.readTemperature();
  float umidade = dht.readHumidity();
 
  if (isnan(tempC) || isnan(umidade)) {
    lcd.setCursor(0, 0); lcd.print("Erro sensor DHT ");
    lcd.setCursor(0, 1); lcd.print("Aguardando...   ");
    Serial.println("Falha na leitura do DHT22!");
    delay(2000);
    return;
  }
 
  int luzRaw     = analogRead(pinoLDR);
  int luzPercent = map(luzRaw, 0, 1023, 0, 100);
 
  int nivelTemp = 0;
  if      (tempC > 25.0) nivelTemp = 2;
  else if (tempC > 23.0) nivelTemp = 1;
 
  int nivelUmid = 0;
  if      (umidade < 40 || umidade > 80) nivelUmid = 2;
  else if (umidade < 50 || umidade > 70) nivelUmid = 1;
 
  int nivelLuz = 0;
  if      (luzPercent > 60) nivelLuz = 2;
  else if (luzPercent >= 30) nivelLuz = 1;
 
  int nivelGeral = max(nivelTemp, max(nivelUmid, nivelLuz));
 
  digitalWrite(ledVerde,    nivelGeral == 0 ? HIGH : LOW);
  digitalWrite(ledAmarelo,  nivelGeral == 1 ? HIGH : LOW);
  digitalWrite(ledVermelho, nivelGeral == 2 ? HIGH : LOW);
 
  unsigned long agora     = millis();
  unsigned long intervalo = (nivelGeral == 2) ? 2000UL : 5000UL;
 
  if (nivelGeral == 0) {
    noTone(buzzer);
    buzzerLigado = false;
    ultimoBuzzer = agora;
  } else {
    if (agora - ultimoBuzzer >= intervalo) {
      ultimoBuzzer = agora;
      buzzerLigado = !buzzerLigado;
      if (buzzerLigado) tone(buzzer, 1000);
      else              noTone(buzzer);
    }
  }
 
  exibirMensagemLCD(nivelTemp, nivelUmid, nivelLuz,
                    tempC, umidade, luzPercent);
 
  Serial.print("Temp: ");     Serial.print(tempC, 1);
  Serial.print("C | Umid: "); Serial.print(umidade, 1);
  Serial.print("% | Luz: ");  Serial.print(luzPercent);
  Serial.print("% | Nivel: ");
  if      (nivelGeral == 0) Serial.println("OK");
  else if (nivelGeral == 1) Serial.println("ALERTA");
  else                      Serial.println("CRITICO");
 
  delay(2000);
}