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

    ~DiauproMessage() {};

    int readFromSocket(DatagramSocket *sock);

    int readFromSocket(DatagramSocket *sock, String &targetHost, int &targetPort);

    uint16 getSequeceNumber();

    uint16 getNumberSamples();

    uint16 getNumberChannels();

    double getSampleRate();

    void setSampleRate(double rate);

    void setSequenceNumber(uint16 sequenceNumber);

    void setAudioData(AudioSampleBuffer *buffer);

    void setMidiData(MidiBuffer *midiMessages);

    void setStateData(void *stateData, size_t stateSize);

    void getMidiData(MidiBuffer &buffer);

    AudioSampleBuffer *getAudioData(AudioSampleBuffer *buffer);
    void getAudioData(OwnedArray<drow::FifoBuffer<float>> *buffers);

    float *getSampleData();

    int getSampleDataSize();

    size_t getStateSize();
    void* getState();

    void *getData();

    size_t getSize();

    void clear();
    
    String headerToString();
    
    void setProcessTime(double time);
    void setTotalTime(double time);
    void incrementTotalTime(double time);
    double getProcessTime();
    double getTotalTime();
    void setTag(uint32 tag);
    uint32 getTag();

private:

    struct diapro_header {
        uint16 sequenceNumber;
        uint16 numSamples;
        uint16 numChannels;
        double sampleRate;
        uint16 audioDataSize;
        uint16 midiDataSize;
        uint16 stateDataSize;
        double cpuUsage;
        double totalTime;
        double processTime;
        uint32 tagNr;
    };

    void setNumberChannels(uint16 numChannels);

    void setNumberSamples(uint16 numSamples);

    size_t getAudioDataOffset();

    size_t getMidiDataOffset();

    size_t getStateDataOffset();

    MemoryBlock data;
    diapro_header header;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DiauproMessage)
};

#endif  // DIAUPROMESSAGE_H_INCLUDED
