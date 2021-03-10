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
    bassDial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    bassDial.setSkewFactorFromMidPoint(1);


    midDial.setRange(0.1, 100.0);
    midDial.setValue(1.0);
    midDial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    midDial.setSkewFactorFromMidPoint(1);

    trebleDial.setRange(0.1, 100.0);
    trebleDial.setValue(1.0);
    trebleDial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    trebleDial.setSkewFactorFromMidPoint(1);

}

EqualizerDials::~EqualizerDials()
{
    setLookAndFeel(nullptr);
}

void EqualizerDials::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.


       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(juce::Colours::darkred);
    g.setColour (juce::Colours::antiquewhite);
    g.setFont (getHeight() / 9);

    int x = getWidth() / 3;
    int y = getHeight() / 20;
    int w = getWidth() / 3;
    int h = getHeight() / 5;

    g.drawText("Bass", 0, y, w, h, juce::Justification::centredTop, true);
    g.drawText("Mid", x, y, w, h , juce::Justification::centredTop, true);
    g.drawText("Treble", x * 2, y, w, h, juce::Justification::centredTop, true);

}

void EqualizerDials::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    bassDial.setTextBoxStyle(juce::Slider::NoTextBox, true, 0,0);
    midDial.setTextBoxStyle(juce::Slider::NoTextBox, true, 0,0);
    trebleDial.setTextBoxStyle(juce::Slider::NoTextBox, true, 0,0);
    
    juce::Grid grid;

    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    grid.templateRows = { Track(Fr(1))};
    grid.templateColumns = { Track(Fr(1)), Track(Fr(1)), Track(Fr(1)) };

    grid.items = { juce::GridItem(bassDial), juce::GridItem(midDial), juce::GridItem(trebleDial) };

    grid.performLayout(getLocalBounds());
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


