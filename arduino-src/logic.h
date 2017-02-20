
#define PLANE byte(0)
#define BLOCK byte(1)
#define HUMAN byte(2)
#define BLANK byte(255)

#define PLAYING 1
#define LOSE 0

byte state = PLAYING;

byte* lines[4];

// Initial position of plane.
short hero_position = 2;

unsigned long last_screen_move = millis();
unsigned long moving_rate = 500;

/*
 * Moves the screen to the left. i.e. moves blocks toward the plane.
 */
void move_screen()
{
  for (int c = 0;c < 18;c++)
  {
    lines[0][c] = lines[0][c + 1];
    lines[1][c] = lines[1][c + 1];
    lines[2][c] = lines[2][c + 1];
    lines[3][c] = lines[3][c + 1];
  }

  // For now, blocks appears randomly.
  for (int i = 0;i < 4;i++)
  {
    if (random(4) == 3)
    {
      // 25% chance that a block appears.
      lines[i][18] = BLOCK;
    }
    else
    {
      lines[i][18] = BLANK;
    }
  }
}

void check_losing_condition()
{
  if (lines[hero_position][0] == BLOCK)
  {
    state = LOSE;
  }
}

/*
 * Initializes logic module.
 */
void logic_setup()
{
  /*
   * Initializing random.
   * Seed is an analog value of a not-connected pin. According to
   * the Arduino reference's suggestion.
   */
  randomSeed(analogRead(0));

  // Allocating memory for lines.
  lines[0] = new byte[19];
  lines[1] = new byte[19];
  lines[2] = new byte[19];
  lines[3] = new byte[19];

  // Initializing all lines with blanks.
  for (int i = 0; i < 19; i++)
  {
    lines[0][i] = BLANK;
    lines[1][i] = BLANK;
    lines[2][i] = BLANK;
    lines[3][i] = BLANK;
  }
}

/*
 * Updates logic of the game (e.g moves there screen, check pressed buttons, etc).
 * 
 * Returns TRUE if the whole screen needs a refresh.
 * We only refresh the screen if required, because character LCDs are too slow.
 */
bool logic_update(bool up_pressed, bool down_pressed)
{
  if (state == LOSE)
  {
    // If player lose, do nothing anymore.
    return;
  }
  
  /*
   * Calculating new position of hero.
   */
  if (up_pressed)
  {
    if (hero_position > 0)
    {
      hero_position -= 1;
    }
  }
  if (down_pressed)
  {
    if (hero_position < 3)
    {
      hero_position += 1;
    }
  }

  check_losing_condition();

  if (millis() - last_screen_move >= moving_rate)
  {
    // Moving the screen (blocks) every 500ms.
    // TODO: This should speed up as the game progress.
    move_screen();
    last_screen_move = millis();

    return true;
  }

  return false;
}

