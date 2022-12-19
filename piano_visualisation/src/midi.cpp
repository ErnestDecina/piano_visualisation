// midi.cpp

// Header Files
#include "pch.h"
#include "midi.h"

// Public Methods
void Midi::get_input(void)
{
	std::cout << "\nInputs Available:\n";
	probing_input();
}


void Midi::get_output(void)
{
	std::cout << "\nOutputs Available:\n";
	probing_output();
}


void Midi::input_details(void)
{
	// Error Check
	if (selected_input_port == NULL)
	{
		std::cout << "No input device selected\n";
		return;
	} // End if

	std::cout << "\nInput device details\n";
	std::cout << "Port number: " << selected_input_port << "\n";
	std::cout << "Device Name: " << midi_input->getPortName(selected_input_port - 1) << "\n";
}


void Midi::output_details(void)
{
	// Error Check
	if (selected_output_port == NULL)
	{
		std::cout << "No output device selected\n";
		return;
	} // End if

	std::cout << "\nOutput device details\n";
	std::cout << "Port number: " << selected_output_port << "\n";
	std::cout << "Device Name: " << midi_output->getPortName(selected_output_port - 1) << "\n";
}


void Midi::select_input(void)
{
	// User input
	std::cin.clear();
	std::cout << "Enter input port: ";
	std::cin >> selected_input_port;


	// Error Check
	while (true)
	{
		if (std::cin.fail() || selected_input_port <= 0 || selected_input_port > available_input_ports)
		{
			// Clear Buffer
			std::cin.clear();
			std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n');

			// Input
			std::cout << "Enter available input port: ";
			std::cin >> selected_input_port;
		} // End if

		if (!std::cin.fail() && selected_input_port > 0 && selected_input_port < available_input_ports + 1)
			return;
	} // End while
}


void Midi::select_output(void)
{
	// User input
	std::cin.clear();
	std::cout << "Enter output port: ";
	std::cin >> selected_output_port;


	// Error Check
	while (true)
	{
		if (std::cin.fail() || selected_output_port <= 0 || selected_output_port > available_output_ports)
		{
			// Clear Buffer
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			// Input
			std::cout << "Enter available input port: ";
			std::cin >> selected_output_port;
		} // End if

		if (!std::cin.fail() && selected_output_port > 0 && selected_output_port < available_output_ports + 1)
			return;
	} // End while
}

void Midi::listen_input(void)
{
	// Variables
	std::vector<unsigned char> message;
	unsigned int i = 0;
	unsigned int number_bytes = 0;
	double stamp = 0;

	// Error Checking
	if (selected_input_port == NULL)
	{
		std::cout << "No input selcted\n";
		return;
	} // eND IF



	midi_input->openPort(selected_input_port - 1);
	// Don't ignore sysex, timing, or active sensing messages.
	midi_input->ignoreTypes(false, false, false);

	// Periodically check input queue.
	std::cout << "Reading MIDI from port ... quit with Ctrl-C.\n";
	while (true) {
		stamp = midi_input->getMessage(&message);
		number_bytes = message.size();
		for (i = 0; i < number_bytes; i++)
			std::cout << "Byte " << i << " = " << (int)message[i] << ", ";
		if (number_bytes > 0)
			std::cout << "stamp = " << stamp << std::endl;
		// Sleep for 10 milliseconds ... platform-dependent.
		// Sleep(10);
	}

}

void Midi::listen_output(void)
{
}


// Private Methods
void Midi::probing_input(void)
{
	// Variables
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
	available_input_ports = midi_input->getPortCount();


	// Error Check for 0 port counts
	if (available_input_ports == 0)
	{
		std::cout << "No Input Ports Avaiable\n" << "Terminating Program\n";
		return;
	} // End if


	// Print amount of ports
	std::cout << available_input_ports << " Available Input Ports\n";


	// Loop Through all available midi input ports
	for (unsigned int port_number = 0; port_number < available_input_ports; port_number++)
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


void Midi::probing_output(void)
{
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
	available_output_ports = midi_output->getPortCount();


	// Error Check for 0 port counts
	if (available_output_ports == 0)
	{
		std::cout << "No Output Ports Avaiable\n" << "Terminating Program\n";
		return;
	} // End if


	// Print amount of ports
	std::cout << available_output_ports << " Available Output Ports\n";


	// Loop Through all available midi input ports
	for (unsigned int port_number = 0; port_number < available_output_ports; port_number++)
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

void Midi::cleanup(void)
{
	delete midi_input;
	delete midi_output;
}
