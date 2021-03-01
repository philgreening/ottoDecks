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

    void setBass(double bassGain);
    void setMid(double midGain);
    void setTreble(double trebleGain);

    /** get the relative position of the playhead*/
    double getPositionRelative();

private:

    double sampleRateStored;

    juce::AudioFormatManager& formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
  
    juce::AudioTransportSource transportSource;
    juce::ResamplingAudioSource resampleSource{ &trebleFilter, false, 2 };

    juce::IIRFilterAudioSource bassFilter{&transportSource, false};
    juce::IIRFilterAudioSource midFilter{ &bassFilter, false };
    juce::IIRFilterAudioSource trebleFilter{ &midFilter, false };


};