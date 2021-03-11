/*
  ==============================================================================

    DJAudioPlayer.cpp
    Created: 20 Jan 2021 5:49:50pm
    Author:  philg

  ==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(juce::AudioFormatManager& _formatManager)
                            : formatManager(_formatManager)
{
}
DJAudioPlayer::~DJAudioPlayer()
{
}

void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate) 
{
    sampleRateStored = sampleRate;

    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);;
}
void DJAudioPlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) 
{
    resampleSource.getNextAudioBlock(bufferToFill);
}

void DJAudioPlayer::releaseResources()
{
    transportSource.releaseResources();
    resampleSource.releaseResources();
}

void DJAudioPlayer::loadURL(juce::URL audioURL)
{
    // load file
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr)//good file!
    {
        std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
    }
}

void DJAudioPlayer::setGain(double gain)
{
    if (gain < 0 || gain >1.0)
    {
        std::cout << "DJAudioPlayer::setGain. gain should be between 0 and 1" << std::endl;
    }
    else {
        transportSource.setGain(gain);
    }
}

void DJAudioPlayer::setSpeed(double ratio)
{

    if (ratio < 0 || ratio > 2.0)
    {
        std::cout << "DJAudioPlayer::setSpeed. ratio should be between 1 and 100" << std::endl;
    }
    else {
        resampleSource.setResamplingRatio(ratio);
    }
}

void DJAudioPlayer::setPosition(double posInSecs)
{
    transportSource.setPosition(posInSecs);
}

void DJAudioPlayer::start()
{
    transportSource.start();
}

void DJAudioPlayer::stop()
{
    transportSource.stop();
}

double DJAudioPlayer::getPositionRelative()
{
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}

void DJAudioPlayer::setPositionRelative(double pos)
{
    if (pos < 0 || pos > 1.0)
    {
        DBG("DJAudioPlayer::setPositionRelative - pos should be between 0 and 1");
    }
    else {
        double posInSeconds = transportSource.getLengthInSeconds() * pos;
        setPosition(posInSeconds);
    }
}

int DJAudioPlayer::getLengthInSeconds()
{
    return transportSource.getLengthInSeconds(); 
}

void DJAudioPlayer::setBass(double bassGain)
{
    if (bassGain < 0 || bassGain > 100)
    {
        DBG("DJAudioPlayer::filters - bassGain should be between 0 and 100");
    }
    else{
        bassFilter.setCoefficients(juce::IIRCoefficients::makeLowShelf(sampleRateStored, 300, 1, bassGain));
    }
}

void DJAudioPlayer::setMid(double midGain)
{
    if (midGain < 0 || midGain > 100)
    {
        DBG("DJAudioPlayer::filters - midGain should be between 0 and 100");
    }
    else{
        midFilter.setCoefficients(juce::IIRCoefficients::makePeakFilter(sampleRateStored, 4000, 1, midGain));
    }
}

void DJAudioPlayer::setTreble(double trebleGain)
{
    if (trebleGain < 0 || trebleGain > 100)
    {
        DBG("DJAudioPlayer::filters - trebleGain should be between 0 and 100");
    }
    else{
        trebleFilter.setCoefficients(juce::IIRCoefficients::makeHighShelf(sampleRateStored, 10000, 1, trebleGain));
    }
}

juce::String DJAudioPlayer::getTrackCurrentPos()
{
    //calculate minutes and seconds
    int minutes (transportSource.getCurrentPosition() /60);
    int seconds((int)transportSource.getCurrentPosition() % 60);

    juce::String trackCurrentPos = std::to_string(minutes) + ":" + std::to_string(seconds);

    //adds a extra zero at begining of seconds if < 10
    if (seconds < 10)
    {
        trackCurrentPos = std::to_string(minutes) + ":" + "0" + std::to_string(seconds);
    }
    return trackCurrentPos;
}