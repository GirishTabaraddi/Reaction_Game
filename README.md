# Reaction_Game

A simpler reaction game using Erika OS

## Reaction game

The task is to develop a simple reaction game using Erika OS and to extend this functionality with some Arcadian light effects.

**NFR1** The application runs as an Erika-OS Application

**FR2** Upon startup, the program will show a welcome message via the serial port.

**FR3** After pressing one of the two white buttons, the program will wait for a ran-dom time. After waiting for 1s to 3s a random value (1 or 2) will be dis-played on both 7segment displays

**FR4** The user has to press the right button in case a ‘1’ is displayed and the left button in case a ‘2’ is displayed

**FR5** In case the correct button is being pressed, the measured reaction time in [ms] will be shown and the game can be started again by pressing one of the two buttons.

**FR6** In case a wrong button is pressed, an error message will be displayed and the game can be started again by pressing one of the two buttons.

**FR7** In case the user does not press a button within 1 s, the message “Too slow” will appear and the game can be started again by pressing one of the two buttons.

**FR8** One game consists out of 10 rounds

**FR9** At the end of a game, print the score (i.e. correct number of button pressed), the total time and the average time#

**NFR10** Use the switch-case pattern to implement the state machine. Use private functions for the actions and guards.

**NFR11** Write the code of the reaction game logic in an own file

**NFR12** Provide good comments and self-explaining variable und function names.

**Example output via the serial port:**

	Reaction test program round 1
	press one of the two buttons to start...
	Great - correct button pressed
	Reaction time in ms: 249
	=======================================================
	

## Glower

Using the RGB LED, we want to implement an easily configurable glowing function. Using a const - table like the following (pseudo code)

	const RG__Glow_t RG_glowtable_1[] = {
	//Red Green Blue TimeInMS
	{255, 0, 0, 500},
	{0, 255, 0, 500},
	{0, 0, 255, 500},
	{0, 0, 0, 100},
	{255, 255, 255, 100},
	{0, 0, 0, 100},
	{255, 255, 255, 100},
	{0, 0, 0, 100},
	{255, 255, 255, 100}
	};

will create the sequence:

	• 500ms red
	• 500ms green
	• 500ms blue
	• 100ms off
	• 100ms white
	• 100ms off
	• 100ms white
	• 100ms off
	• 100ms white

This sequence will be repeated permanently.
