/*******************************************************
 * Projeto: Controle de LEDs + Display OLED
 * Autor: Willys IoT
 * Plataforma: ESP8266 (NodeMCU)
 * Descrição:
 * - Pisca LED interno e externo
 * - Mostra status no display OLED
 * - Espelha informação em dois displays (interno e externo)
 *******************************************************/

#include <Arduino.h>     // Biblioteca principal do Arduino
#include <Wire.h>        // Biblioteca para comunicação I2C
#include <U8g2lib.h>     // Biblioteca para controle do display OLED

// ===== DISPLAY INTERNO (I2C por software) =====
// clock = GPIO12 (D6) | data = GPIO14 (D5)
U8G2_SSD1306_128X64_NONAME_F_SW_I2C 
displayInterno(U8G2_R0, /* clock=*/ 12, /* data=*/ 14, U8X8_PIN_NONE);

// ===== DISPLAY EXTERNO (I2C por hardware) =====
// Usa os pinos padrão do ESP8266 (D1 e D2)
U8G2_SSD1306_128X64_NONAME_F_HW_I2C 
displayExterno(U8G2_R0, U8X8_PIN_NONE);

// ===== DEFINIÇÃO DOS LEDs =====
#define LED_INTERNO LED_BUILTIN  // LED da placa (invertido)
#define LED_EXTERNO D7           // LED externo ligado ao pino D7

// ===== FUNÇÃO SETUP =====
void setup(void) {

  // Configura os pinos dos LEDs como saída
  pinMode(LED_INTERNO, OUTPUT);
  pinMode(LED_EXTERNO, OUTPUT);

  // Inicializa o barramento I2C (SDA = D2 | SCL = D1)
  Wire.begin(D2, D1);

  // Inicializa os displays
  displayInterno.begin();
  displayExterno.begin();
}

// ===== FUNÇÃO LOOP =====
void loop(void) {

  // ===== ESTADO: LED LIGADO =====

  digitalWrite(LED_INTERNO, LOW);   // Liga LED interno (invertido)
  digitalWrite(LED_EXTERNO, HIGH);  // Liga LED externo

  // Limpa o buffer dos displays
  displayInterno.clearBuffer();
  displayExterno.clearBuffer();

  // Define a fonte do texto
  displayInterno.setFont(u8g2_font_ncenB08_tr);
  displayExterno.setFont(u8g2_font_ncenB08_tr);

  // Escreve o texto nos displays
  displayInterno.drawStr(10, 30, "LED ON");
  displayExterno.drawStr(10, 30, "LED ON");

  // Envia o conteúdo para os displays
  displayInterno.sendBuffer();
  displayExterno.sendBuffer();

  delay(1000); // Espera 1 segundo

  // ===== ESTADO: LED DESLIGADO =====

  digitalWrite(LED_INTERNO, HIGH);  // Desliga LED interno
  digitalWrite(LED_EXTERNO, LOW);   // Desliga LED externo

  // Limpa novamente os displays
  displayInterno.clearBuffer();
  displayExterno.clearBuffer();

  // Escreve o novo estado
  displayInterno.drawStr(10, 30, "LED OFF");
  displayExterno.drawStr(10, 30, "LED OFF");

  // Atualiza os displays
  displayInterno.sendBuffer();
  displayExterno.sendBuffer();

  delay(1000); // Espera 1 segundo
}