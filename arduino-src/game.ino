/*
 * This file is part of "PM Game Console". (see <https://github.com/aidin36/pm-game-console>)
 * Copyright (C) 2017, Aidin Gharibnavaz <aidin@aidinhut.com>
 *
 * "PM Game Console" is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * "PM Game Console" is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 *  along with "PM Game Console".  If not, see <http://www.gnu.org/licenses/>.
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

