
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
 * These are pre-designed lines of blocks. We randomly select one of these and
 * put it in front of our hero.
 */
#define NUMBER_OF_PREDEFINED 4
unsigned int pre_designed_lines[NUMBER_OF_PREDEFINED][4] =
{
  {
     54532, //1101010100000100
     12354, //0011000001000010
     33449, //1000001010101001
     24336, //0101111100010000
  },
  {
     65528, //1111111111111000
     36803, //1000111111000011
     8727,  //0010001000010111
     63743  //1111100011111111
  },
  {
     32536, //0111111100011000
     13891, //0011011001000011
     33363, //1000001001010011
     51440  //1100100011110000
  },
  {
     20754, //0101000100010010
     17744, //0100010101010000
     21586, //0101010001010010
     5442   //0001010101000010
  },
};

byte current_predefined_path = 0;
byte current_predefined_index = 0;

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

  // Adding new blocks.
  if (current_predefined_index == 0)
  {
    // Randomly select another pre-defined path.
    current_predefined_path = random(NUMBER_OF_PREDEFINED);
    current_predefined_index = 16;

    // Adding an empty column, to ensure there's always a path.
    lines[0][18] = BLANK;
    lines[1][18] = BLANK;
    lines[2][18] = BLANK;
    lines[3][18] = BLANK;

    return;
  }

  for (int i = 0;i < 4;i++)
  {
    Serial.println(current_predefined_index);
    if (pre_designed_lines[current_predefined_path][i] & (1<<(current_predefined_index - 1)))
    {
      lines[i][18] = BLOCK;
    }
    else
    {
      lines[i][18] = BLANK;
    }
  }

  current_predefined_index--;
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


  Serial.begin(9600);
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
    return false;
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

