/*
  ==============================================================================

    AudioSpeedLookAndFeel.h
    Created: 7 Mar 2021 12:11:55pm
    Author:  philg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AudioSpeedLookAndFeel  : public juce::LookAndFeel_V4
{
public:
    AudioSpeedLookAndFeel();
    ~AudioSpeedLookAndFeel() override;

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioSpeedLookAndFeel)
};
