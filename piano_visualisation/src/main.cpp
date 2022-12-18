// midiprobe.cpp
#include "pch.h"
#include "midi.h"

int main()
{
	// Variables
	midi Midi;


	// Test Class
	Midi.get_input();
	Midi.get_output();


	// Clean up Memory
	Midi.cleanup();
	return 0;
} // End main