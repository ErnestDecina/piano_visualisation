// menu.cpp
#include "pch.h"
#include "menu.h"

void Menu::set_midi(Midi* main_midi)
{
	menu_midi = main_midi;
}

void Menu::display_menu(void)
{
	while (true)
	{
		std::cout << "1. Select Midi Input Source\n";
		std::cout << "2. Select Midi Output Source\n";
		std::cout << "3. Display Midi Input Details\n";
		std::cout << "4. Display Mifi Output Details\n";
		std::cout << "5. Listen to Midi Input\n";
		std::cout << "6. Listen to Midi Output\n";
		std::cout << "7. End Program\n";

		user_option = get_user_input("Select option: ");

		if (user_option == 1)
		{
			std::cout << "\n\n";
			menu_midi->get_input();
			menu_midi->select_input();
		}

		else if (user_option == 2)
		{
			std::cout << "\n\n";
			menu_midi->get_output();
			menu_midi->select_output();
		}

		else if (user_option == 3)
		{
			std::cout << "\n\n";
			menu_midi->input_details();
			std::cout << "\n\n";
		}

		else if (user_option == 4)
		{
			std::cout << "\n\n";
			menu_midi->output_details();
			std::cout << "\n\n";
		}

		else if (user_option == 5)
		{
			// Create Thread to listen for midi
			std::thread thread_listen_input(&Midi::listen_input, menu_midi);

			// Thread to stop listen loop
			std::thread thread_stop_listen(&Midi::stop_listen, menu_midi);

			// Thread join
			thread_listen_input.join();
			thread_stop_listen.join();

		}

		else if (user_option == 6)
		{

		}

		else if (user_option == 7)
		{
			std::cout << "\n\nEnding Program\n";
			return;
		}

		else
		{
			std::cout << "Please select valid option.";
		}

		/*
		switch (user_option)
		{
		case 1:
			std::cout << "\n\n";
			menu_midi->get_input();
			menu_midi->select_input();
			break;

		case 2:
			std::cout << "\n\n";
			menu_midi->get_output();
			menu_midi->select_output();
			break;

		case 3:
			std::cout << "\n\n";
			menu_midi->input_details();
			std::cout << "\n\n";
			break;

		case 4:
			std::cout << "\n\n";
			menu_midi->output_details();
			std::cout << "\n\n";
			break;

		case 5:
			// Create Thread to listen for midi
			std::thread thread_listen_input(&Midi::listen_input, menu_midi);

			// Thread to stop listen loop
			std::thread thread_stop_listen(&Midi::stop_listen, menu_midi);

			// Thread join
			thread_listen_input.join();
			thread_stop_listen.join();

			break;

		case 6:
			break;

		case 7:
			std::cout << "\n\nEnding Program\n";
			return;
			break;

		default:
			std::cout << "Please select valid option.";
			break;
		} // End switch
		*/
		std::cout << "\n\n";
	} // End while
}

unsigned int Menu::get_user_input(std::string input_message)
{
	// Variables
	unsigned int user_input;

	// User input
	std::cin.clear();
	std::cout << input_message;
	std::cin >> user_input;


	// Error Check
	while (true)
	{
		if (std::cin.fail())
		{
			// Clear Buffer
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			// Input
			std::cout << "Enter valid option: ";
			std::cin >> user_input;
		} // End if

		if (!std::cin.fail())
			return user_input;
	} // End while
}