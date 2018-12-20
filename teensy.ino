#include <ssd1351.h>
#include <core_pins.h>

#include <Keyboard.h>

#define RESTART_ADDR       0xE000ED0C
#define READ_RESTART()     (*(volatile uint32_t *)RESTART_ADDR)
#define WRITE_RESTART(val) ((*(volatile uint32_t *)RESTART_ADDR) = (val))

const unsigned int ledPin = 13;
const unsigned int delayTime = 35000;
const unsigned int MAX_INPUT = 50;


void setup()
{
  delay(1500);
  // Setup LED
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  delay(80);
  digitalWrite(ledPin, LOW);
  delay(80);
  digitalWrite(ledPin, HIGH);
  delay(80);
  digitalWrite(ledPin, LOW);
  delay(80);
  digitalWrite(ledPin, HIGH);
  delay(80);
  digitalWrite(ledPin, LOW);
  delay(80);
  digitalWrite(ledPin, LOW);
  delay(80);
  digitalWrite(ledPin, HIGH);
  delay(80);
  
  // Do the shit...
  pwn();

}

void key(int KEY, int MODIFIER)
 {
  Keyboard.set_modifier(MODIFIER);
  Keyboard.set_key1(KEY);
  Keyboard.send_now();
  delay(20);
  Keyboard.set_modifier(0);
  Keyboard.set_key1(0);
  Keyboard.send_now();
  delay(20);
 }

void pwn()
{
  delay(delayTime);
  Keyboard.println("Your BIOS/LUKS password");
}


void processIncomingByte (const byte inByte)
{
  static char input_line [MAX_INPUT];
  static unsigned int input_pos = 0;

switch (inByte){

  case '\n': // discard carriage return
  break;

  case 'k':
    Serial.println("Reiniciando!!");
    digitalwrite(ledPin, HIGH);
    delay(25000);  
    WRITE_RESTART(0x5FA0004);
    break;

  default:
    Serial.println("Eso no ve vale!!");
    delay(20);
    break;

  }  // end of switch

}


void loop()
{
  digitalWrite(ledPin, HIGH);
  delay(80);
  digitalWrite(ledPin, LOW);
  delay(80);
  while (Serial.available() > 0) {
    processIncomingByte(Serial.read());
    Serial.println("Acho dame un char no?");
  }
}
