/*
  ==============================================================================

    EqualizerDials.h
    Created: 3 Mar 2021 1:42:35pm
    Author:  philg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

//==============================================================================
/*
*/
class EqualizerDials : public juce::Component,
                       public juce::Slider::Listener
{
public:
    EqualizerDials(DJAudioPlayer* player);
    ~EqualizerDials() override;

    void sliderValueChanged(juce::Slider* slider) override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    juce::Slider bassDial;
    juce::Slider midDial;
    juce::Slider trebleDial;

    DJAudioPlayer* player;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EqualizerDials)
};
