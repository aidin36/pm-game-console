Intro
-----

Poor Man's Game Console is a game designed using [Arduino](https://www.arduino.cc/). The screen of the game is a 20x4 character LCD (HD44780), and controls are two push buttons.

![Photo of the Project](https://github.com/aidin36/pm-game-console/raw/master/screen-shots/shot-01.JPG)   ![Photo of the Project](https://github.com/aidin36/pm-game-console/raw/master/screen-shots/shot-02.JPG)

How To
------

First, you need to create the circuit. You can simply assemble it on a bread board. An image of an assembled bread board and the schematic of the circuit can be found on `circuit` directory.

Then, to upload the code on Arduino, copy `Arduino-src` directory into your Arduino's workspace (where you save your Arduino projects), rename it to something meaningful (i.e. pm-game-console) and open `game.ino` using Arduino IDE. Then upload it to your Arduino.

If you are on Gnu/Linux, you can link the directory inside your workspace to `Arduino-src` too.

Copyright
---------

Copyright (C) 2017, Aidin Gharibnavaz <aidin@aidinhut.com>

"PM Game Console" is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 3. See LICENSE file for more information.
