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
    DBG("DJAudioPlayer::prepareToPlay - sampleRate " << sampleRateStored);

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

    if (ratio < 0 || ratio > 10.0)
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
        std::cout << "DJAudioPlayer::setPositionRelative . pos should be between 0 and 1" << std::endl;
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

        DBG("DJAudiPlayer::filters - sampleRateStored " << sampleRateStored);
        DBG("DJAudiPlayer::filters - bassGain " << bassGain);
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

        DBG("DJAudiPlayer::filters - sampleRateStored " << sampleRateStored);
        DBG("DJAudiPlayer::filters - midGain " << midGain);
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

        DBG("DJAudiPlayer::filters - sampleRateStored " << sampleRateStored);
        DBG("DJAudiPlayer::filters - trebleGain " << trebleGain);
    }
}
