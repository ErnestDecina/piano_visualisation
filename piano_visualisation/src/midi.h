/**********************************************************************/
/*! midi.h
    Methods to get midi input and read it
*/
/**********************************************************************/

class midi
{
public:
    void get_input(void);
    void get_output(void);
    void cleanup(void);

private:
    // Variables
    RtMidiIn* midi_input = 0;
    RtMidiOut* midi_output = 0;


    // Methods
    void probing_input(void);
    void probing_output(void);
};