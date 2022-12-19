// menu.h

// Header Files
#include "midi.h"

class Menu
{
public:
	// Methods
	void set_midi(Midi*);
	void display_menu(void);

private:
	// Variables
	unsigned int user_option = 0;
	Midi* menu_midi = nullptr;

	// Methods
	unsigned int get_user_input(std::string);
};