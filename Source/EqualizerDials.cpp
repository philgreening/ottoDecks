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
    //makes dials visable
    addAndMakeVisible(bassDial);
    addAndMakeVisible(midDial);
    addAndMakeVisible(trebleDial);

    //adds listners
    bassDial.addListener(this);
    midDial.addListener(this);
    trebleDial.addListener(this);

    //set properties of dials
    bassDial.setRange(0.1, 100.0);
    bassDial.setValue(1.0);
    bassDial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    bassDial.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    bassDial.setSkewFactorFromMidPoint(1);

    midDial.setRange(0.1, 100.0);
    midDial.setValue(1.0);
    midDial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    midDial.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    midDial.setSkewFactorFromMidPoint(1);

    trebleDial.setRange(0.1, 100.0);
    trebleDial.setValue(1.0);
    trebleDial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    trebleDial.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    trebleDial.setSkewFactorFromMidPoint(1);
}

EqualizerDials::~EqualizerDials()
{
    setLookAndFeel(nullptr);
}

void EqualizerDials::paint (juce::Graphics& g)
{
    //fill component background
    g.fillAll(juce::Colours::darkred);

    //sets text colour, size and position and draws text
    g.setColour (juce::Colours::antiquewhite);
    g.setFont ((float)getHeight() / 9);

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
    //sets up grid for layout
    juce::Grid grid;
    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    grid.templateRows = { Track(Fr(1))};
    grid.templateColumns = { Track(Fr(1)), Track(Fr(1)), Track(Fr(1)) };

    //position items on grid
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


