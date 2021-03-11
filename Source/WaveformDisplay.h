/*
  ==============================================================================

    WaveformDisplay.h
    Created: 24 Jan 2021 12:47:58pm
    Author:  philg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveformDisplay : public juce::Component,
                        public juce::ChangeListener,
                        public juce::LookAndFeel_V4
{
public:
    /**Constructor */
    WaveformDisplay(
        juce::AudioFormatManager& formatManagerToUse,
        juce::AudioThumbnailCache& cacheToUse);

    /**Destructor */
    ~WaveformDisplay() override;

    /**Draws the waveform when file loaded based on audio thumbnail*/
    void paint (juce::Graphics&) override;

    /**Listens for new audio info and repaints waveform */
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

    /**Loads file URL to waveform and repaints */
    void loadURL(juce::URL audioURL);

    /** set the relative position of the playhead */
    void setPositionRelative(double pos);

    /**Overrides the look and feel of the position slider and places it over waveform */
    void drawLinearSlider(juce::Graphics&, int x, int y,
                          int width, int height,
                          float sliderPos, float minSliderPos,
                          float maxSliderPos,
                          const juce::Slider::SliderStyle,
                          juce::Slider&) override;

private:

    juce::AudioThumbnail audioThumb;

    double position;
    bool fileLoaded;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
