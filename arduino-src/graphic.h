
#include <LiquidCrystal.h>

// A custom character for the hero.
byte plane_char[8] = {
  B11000,
  B00100,
  B10010,
  B11111,
  B10010,
  B00100,
  B11000,
};

// A custom character for blocks.
byte block_char[8] = {
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B00000,
};

// A custom character for humans.
byte human_char[8] = {
  B01110,
  B01110,
  B00100,
  B01110,
  B10101,
  B00100,
  B11011,
};

// initializing the library with the numbers of the interface pins
LiquidCrystal lcd(8, 6, 5, 4, 3, 2);

/*
 * Setups graphic of the game.
 */
void graphic_setup()
{
  // set up the LCD's number of columns and rows:
  lcd.begin(20, 4);

  // Writing our custom chars to LCD.
  lcd.createChar(PLANE, plane_char);
  lcd.createChar(BLOCK, block_char);
  lcd.createChar(HUMAN, human_char);

  lcd.clear();
}

void draw_line(byte line_no, byte* line_data)
{
  for (int c = 0;c < 19;c++)
  {
    if (c == 0 && c == hero_position && line_data[c] == BLANK)
    {
      // We don't want to clear the hero! But, we draw blocks over it.
      continue;
    }

    if (line_data[c] != BLANK)
    {
      // First column is showing score. We start from the second column.
      lcd.setCursor(c + 1, line_no);

      // Enumeration of objects and their character numbers are the same.
      // So we simply write the line data (enum) to the lcd (char).
      lcd.write(line_data[c]);
    }
  }
}

/*
 * Updates the screen. i.e. blocks and humans.
 */
void graphic_update()
{
  lcd.clear();
  
  // Drawing lines.
  for (int i = 0;i < 4;i++)
  {
    draw_line(i, lines[i]);
  }
}

/*
 * Updates the hero on screen.
 */
void graphic_hero_update()
{
  // Cleaning previous location of hero by re-drawing the first line.
  for (int i = 0;i < 4;i++)
  {
    lcd.setCursor(1, i);

    byte line_data = lines[i][0];

    // We draw blocks over the hero. i.e. we only draw hero if location is blank.
    if (line_data == BLANK)
    {
      if (i == hero_position)
      {
        lcd.write(PLANE);
      }
      else
      {
        lcd.write(" ");
      }
    }
    else
    {
      lcd.write(lines[i][0]);
    }
  }
}

