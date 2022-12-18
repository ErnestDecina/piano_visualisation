

// Header Files
#include "pch.h"
#include "midi.h"

// Public Methods
void midi::get_input(void)
{
	std::cout << "\nInputs Available:\n";
	probing_input();
}


void midi::get_output(void)
{
	std::cout << "\nOutputs Available:\n";
	probing_output();
}


// Private Methods
void midi::probing_input(void)
{
	// Variables
	unsigned int number_ports = 0;
	std::string port_name;


	// RtMidiIn constructor
	try {
		midi_input = new RtMidiIn();
	}
	catch (RtMidiError& error) {
		std::cout << "Unable to create midi_in\n";
		error.printMessage();
		exit(EXIT_FAILURE);
	}


	// Check Inputs Available
	number_ports = midi_input->getPortCount();


	// Error Check for 0 port counts
	if (number_ports == 0)
	{
		std::cout << "No Input Ports Avaiable\n" << "Terminating Program\n";
		return;
	} // End if


	// Print amount of ports
	std::cout << number_ports << " Available Input Ports\n";


	// Loop Through all available midi input ports
	for (unsigned int port_number = 0; port_number < number_ports; port_number++)
	{
		try {
			port_name.assign(midi_input->getPortName(port_number));
		}
		catch (RtMidiError& error) {
			std::cout << "Error in getting input port name\n" << "Terminating program\n";
			error.printMessage();

			// Clear Memory
			cleanup();
		}
		std::cout << "  Input Port #" << port_number + 1 << ": " << port_name << '\n';
	} // End for 
}


void midi::probing_output(void)
{
	// Variables
	unsigned int number_ports = 0;
	std::string port_name;


	// RtMidiOut constructor
	try {
		midi_output = new RtMidiOut();
	}
	catch (RtMidiError& error) {
		std::cout << "Unable to create midi_in\n";
		error.printMessage();
		exit(EXIT_FAILURE);
	}


	// Check Output Available
	number_ports = midi_output->getPortCount();


	// Error Check for 0 port counts
	if (number_ports == 0)
	{
		std::cout << "No Output Ports Avaiable\n" << "Terminating Program\n";
		return;
	} // End if


	// Print amount of ports
	std::cout << number_ports << " Available Output Ports\n";


	// Loop Through all available midi input ports
	for (unsigned int port_number = 0; port_number < number_ports; port_number++)
	{
		try {
			port_name.assign(midi_output->getPortName(port_number));
		}
		catch (RtMidiError& error) {
			std::cout << "Error in getting output port name\n" << "Terminating program\n";
			error.printMessage();

			// Clear Memory
			cleanup();
		}
		std::cout << "  Output Port #" << port_number + 1 << ": " << port_name << '\n';
	} // End for 
}


void midi::cleanup(void)
{
	delete midi_input;
	delete midi_output;
}
