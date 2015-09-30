/*
  ==============================================================================

    DiauproMessage.h
    Created: 26 Sep 2015 2:09:13pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#ifndef DIAUPROMESSAGE_H_INCLUDED
#define DIAUPROMESSAGE_H_INCLUDED

#include "JuceHeader.h"


class DiauproMessage {
public:

    DiauproMessage(int initialSize, bool initializeToZero = false);

    ~DiauproMessage() {
    };

    int readFromSocket(DatagramSocket *sock);

    int readFromSocket(DatagramSocket *sock, String &targetHost, int &targetPort);

    int getSequeceNumber();

    int getNumberSamples();

    int getNumberChannels();

    double getSampleRate();

    void setSampleRate(double rate);

    void setSequenceNumber(int sequenceNumber);

    void setAudioData(AudioSampleBuffer *buffer);

    void setMidiData(MidiBuffer *midiMessages);

    void getMidiData(MidiBuffer &buffer);

    AudioSampleBuffer *getAudioData(AudioSampleBuffer *buffer);

    float *getSampleData();

    int getSampleDataSize();

    void *getData();

    size_t getSize();

private:

    struct diapro_header {
        int sequenceNumber;
        int numSamples;
        int numChannels;
        double sampleRate;
        int audioDataSize;
        int midiDataSize;
        float* sampleData;
        uint8* midiData;
    };

    void setNumberChannels(int numChannels);

    void setNumberSamples(int numSamples);

    void setPointerToSampleData(float *ptr);

    void setPointerToMidiData(uint8 *ptr);

    size_t getAudioDataOffset();

    size_t getMidiDataOffset();

    MemoryBlock data;
    diapro_header header;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DiauproMessage)
};

#endif  // DIAUPROMESSAGE_H_INCLUDED
