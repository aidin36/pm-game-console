/*
 * The LCD:
 * LCD RS pin to digital pin 8
 * LCD Enable pin to digital pin 6
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD BLA pin to 5V
 * LCD BLK pin to GND
 * LCD VCC pin to 5V
 * LCD V0 passed through 330 ohms to GND
 */

#include "logic.h"
#include "graphic.h"

#define UP 10
#define DOWN 11


void setup()
{
  pinMode(UP, INPUT);
  pinMode(DOWN, INPUT);

  graphic_setup();
  logic_setup();
}

void loop()
{
  bool up_pressed = digitalRead(UP);
  bool down_pressed = digitalRead(DOWN);

  bool screen_needs_refresh = logic_update(up_pressed, down_pressed);

  // Character LCDs are too slow. So, we only updates the screen if required.
  // But we update the hero everytime, to make the game more responsive to
  // user's actions.
  
  graphic_hero_update();

  if (screen_needs_refresh)
  {
    graphic_update();
  }

  delay(100);
}

