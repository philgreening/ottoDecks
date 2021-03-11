/*
  ==============================================================================

    LookAndFeel.h
    Created: 4 Mar 2021 3:28:22pm
    Author:  philg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class LookAndFeel : public juce::LookAndFeel_V4
{
public:
    /**Constructor*/
    LookAndFeel();

    /**Destructor*/
    ~LookAndFeel();

    /** Overrides the look and feel of the Equalizer dials*/
    void drawRotarySlider(juce::Graphics& g,
                          int x, int y,
                          int width, int height,
                          float sliderPos,
                          const float rotaryStartAngle, 
                          const float rotaryEndAngle,
                          juce::Slider&) override;

    /**Overrides the look and feel of the volume slider*/
    void drawLinearSlider(juce::Graphics& g,
                          int x, int y,
                          int width, int height,
                          float sliderPos,
                          float minSliderPos,
                          float maxSliderPos,
                          const juce::Slider::SliderStyle,
                          juce::Slider&) override;

    /**Sets the font size of the button */
    juce::Font LookAndFeel::getTextButtonFont(juce::TextButton&, int buttonHeight) override;
};