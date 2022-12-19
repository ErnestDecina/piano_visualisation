// main.cpp
#include "pch.h"
#include "main.h"

int main()
{
	// Variables
	Midi midi;
	Menu menu;

	// Display Menu
	menu.set_midi(&midi);
	menu.display_menu();

	// Clean up Memory
	midi.cleanup();
	return 0;
} // End main