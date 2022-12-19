/**********************************************************************/
/*! midi.h
    Methods to get midi input and read it
*/
/**********************************************************************/

class Midi
{
public:
    // Vairables
    unsigned int selected_input_port = NULL;
    unsigned int selected_output_port = NULL;

    // Methods
    void get_input(void);
    void get_output(void);
    void input_details(void);
    void output_details(void);
    void select_input(void);
    void select_output(void);
    void listen_input(void);
    void listen_output(void);
    void stop_listen(void);
    void cleanup(void);

private:
    // Variables
    RtMidiIn* midi_input = 0;
    RtMidiOut* midi_output = 0;
    unsigned int available_input_ports = 0;
    unsigned int available_output_ports = 0;
    bool input_listen_status = false;

    // Methods
    void probing_input(void);
    void probing_output(void);
};