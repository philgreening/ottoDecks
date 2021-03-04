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
    LookAndFeel();
    ~LookAndFeel();

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) override;

private:

};