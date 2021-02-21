/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 20 Jan 2021 5:49:50pm
    Author:  philg

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class DJAudioPlayer : public juce::AudioSource{
public:

    DJAudioPlayer(juce::AudioFormatManager& _formatManager);
    ~DJAudioPlayer();

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void loadURL(juce::URL audioURL);
    void setGain(double gain);
    void setSpeed(double ratio);
    void setPosition(double posInSecs);
    void setPositionRelative(double pos);
    int getLengthInSeconds();

    void start();
    void stop();

    /** get the relative position of the playhead*/
    double getPositionRelative();

private:
    juce::AudioFormatManager& formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
    juce::ResamplingAudioSource resampleSource{ &transportSource, false, 2 };


};