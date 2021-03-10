/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 24 Jan 2021 12:47:58pm
    Author:  philg

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================

WaveformDisplay::WaveformDisplay(juce::AudioFormatManager& formatManagerToUse,
                                 juce::AudioThumbnailCache& cacheToUse) :
                                 audioThumb(1000, formatManagerToUse, cacheToUse),
                                 fileLoaded(false),
                                 position(0)
                                
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    audioThumb.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (juce::Graphics& g)
{
    //fill wavform background
    g.fillAll(juce::Colours::antiquewhite);
    //set colour of waveform
    g.setColour (juce::Colours::darkred);

    if (fileLoaded)// draw waveform
    {
        audioThumb.drawChannel(g,
            getLocalBounds(),
            0,
            audioThumb.getTotalLength(),
            0,
            1.0f
            );
    }
    else
    {
        g.setFont(getHeight()/4);
        g.drawText("File not loaded...", getLocalBounds(),
                    juce::Justification::centred, true);   // draw some placeholder text
    }
}

    

void WaveformDisplay::resized()
{
}

void WaveformDisplay::loadURL(juce::URL audioURL)
{
    DBG("wfd:: loadURL");

    audioThumb.clear();
    fileLoaded = audioThumb.setSource(new juce::URLInputSource(audioURL));

    if (fileLoaded)
    {
        DBG("wfd:: loaded!");
        repaint();
    }
    else {
        DBG("wfd:: not loaded!");
    }
}

void WaveformDisplay::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    std::cout << "wfd: change recieved! " << std::endl;
    DBG("wfd: change recieved! ");
    repaint();

}

void WaveformDisplay::setPositionRelative(double pos)
{
    if (pos != position && !isnan(pos))
    {
        position = pos;
        repaint();
    }
}

void WaveformDisplay::drawLinearSlider(juce::Graphics& g, int x, int y,
                                       int width, int height, float sliderPos,
                                       float minSliderPos, float maxSliderPos,
                                       const juce::Slider::SliderStyle, juce::Slider&)
{
    g.setColour(juce::Colours::darkslategrey);
    g.setOpacity(0.5);
    g.fillRect(position * getWidth(), 0, getWidth() / 20, getHeight());
}
