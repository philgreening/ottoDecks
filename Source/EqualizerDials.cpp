/*
  ==============================================================================

    EqualizerDials.cpp
    Created: 3 Mar 2021 1:42:35pm
    Author:  philg

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EqualizerDials.h"

//==============================================================================
EqualizerDials::EqualizerDials(DJAudioPlayer* _player) : player(_player)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(bassDial);
    addAndMakeVisible(midDial);
    addAndMakeVisible(trebleDial);

    bassDial.addListener(this);
    midDial.addListener(this);
    trebleDial.addListener(this);

    bassDial.setRange(0.1, 100.0);
    bassDial.setValue(1.0);
    midDial.setRange(0.1, 100.0);
    midDial.setValue(1.0);
    trebleDial.setRange(0.1, 100.0);
    trebleDial.setValue(1.0);
}

EqualizerDials::~EqualizerDials()
{
}

void EqualizerDials::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("EqualizerDials", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void EqualizerDials::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    double rowH = getHeight() / 8;

    bassDial.setBounds(0 , rowH , getWidth() /3 , getHeight());
    midDial.setBounds(getWidth() / 3, rowH , getWidth() / 3, getHeight());
    trebleDial.setBounds(getWidth() / 3  *2, rowH, getWidth() / 3, getHeight());
}

void EqualizerDials::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &bassDial)
    {
        player->setBass(slider->getValue());

    }
    if (slider == &midDial)
    {
        player->setMid(slider->getValue());
    }
    if (slider == &trebleDial)
    {
        player->setTreble(slider->getValue());
    }
}
