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
    /** Constructor */
    DJAudioPlayer(juce::AudioFormatManager& _formatManager);

    /** Destructor */
    ~DJAudioPlayer();

    /** Prepares resources ready for playback */
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;

    /** Fetches blocks of audio data */
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;

    /** Releases memory at end of playback*/
    void releaseResources() override;

    /** Loads received file for playback*/
    void loadURL(juce::URL audioURL);

    /** Sets the volume*/
    void setGain(double gain);

    /** Sets the speed*/
    void setSpeed(double ratio);

    /** Sets the track position*/
    void setPosition(double posInSecs);
    
    /** sets the relavive position of the playhead */
    void setPositionRelative(double pos);

    /** Returns the track length in seconds */
    int getLengthInSeconds();

    /** Starts playback*/
    void start();

    /** Stops playback*/
    void stop();

    /** Sets the value of the bass */
    void setBass(double bassGain);

    /** Sets the value of the mids */
    void setMid(double midGain);

    /** Sets the value of the treble */
    void setTreble(double trebleGain);

    /** Get the relative position of the playhead*/
    double getPositionRelative();

    /** stores the current track position in minutes and seconds */
    juce::String getTrackCurrentPos();

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