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
    bassDial.setNumDecimalPlacesToDisplay(2);

    midDial.setRange(0.1, 100.0);
    midDial.setValue(1.0);
    midDial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    midDial.setNumDecimalPlacesToDisplay(2);

    trebleDial.setRange(0.1, 100.0);
    trebleDial.setValue(1.0);
    trebleDial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    trebleDial.setNumDecimalPlacesToDisplay(2);

    //lookAndFeel.setColour(juce::Slider::thumbColourId, juce::Colours::red);
    //bassDial.setLookAndFeel(&customLook);
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

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    //g.drawText ("EqualizerDials", getLocalBounds(),
                //juce::Justification::centred, true);   // draw some placeholder text
    //bassDial.setLookAndFeel(&customLook);
    g.drawText("Bass", 0, 0, getWidth() / 3, 40, juce::Justification::centred, true);
    g.drawText("Mid", getWidth() /3, 0, getWidth() /3, 40 , juce::Justification::centred, true);
    g.drawText("Treble", getWidth() / 3 * 2, 0, getWidth() / 3, 40, juce::Justification::centred, true);

}

//void EqualizerDials::resized()
//{
//    // This method is where you should set the bounds of any child
//    // components that your component contains..
//    bassDial.setTextBoxStyle(juce::Slider::TextBoxBelow, true, getWidth()/8, 20 );
//    midDial.setTextBoxStyle(juce::Slider::TextBoxBelow, true, getWidth() / 8, 20);
//    trebleDial.setTextBoxStyle(juce::Slider::TextBoxBelow, true, getWidth() / 8, 20);
//
//
//    double rowH = getHeight() / 8;
//
//    bassDial.setBounds(0 , 0 , getWidth() /3 , getHeight());
//    midDial.setBounds(getWidth() / 3, 0 , getWidth() / 3, getHeight());
//    trebleDial.setBounds(getWidth() / 3  *2, 0, getWidth() / 3, getHeight());
//}

void EqualizerDials::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    bassDial.setTextBoxStyle(juce::Slider::TextBoxBelow, true, getWidth() / 6, 20);
    bassDial.setSkewFactorFromMidPoint(1);
    midDial.setTextBoxStyle(juce::Slider::TextBoxBelow, true, getWidth() / 6, 20);
    midDial.setSkewFactorFromMidPoint(1);
    trebleDial.setTextBoxStyle(juce::Slider::TextBoxBelow, true, getWidth() / 6, 20);
    trebleDial.setSkewFactorFromMidPoint(1);
    
    juce::Grid grid;

    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    grid.templateRows = { Track(Fr(1)) };
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

//void EqualizerDials::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
//    const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&)
//{
//    auto radius = (float)juce::jmin(width / 2, height / 2) - 4.0f;
//    auto centreX = (float)x + (float)width * 0.5f;
//    auto centreY = (float)y + (float)height * 0.5f;
//    auto rx = centreX - radius;
//    auto ry = centreY - radius;
//    auto rw = radius * 2.0f;
//    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
//
//    // fill
//    g.setColour(juce::Colours::orange);
//    g.fillEllipse(rx, ry, rw, rw);
//
//    // outline
//    g.setColour(juce::Colours::red);
//    g.drawEllipse(rx, ry, rw, rw, 1.0f);
//
//    juce::Path p;
//    auto pointerLength = radius * 0.33f;
//    auto pointerThickness = 2.0f;
//    p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
//    p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));
//
//    // pointer
//    g.setColour(juce::Colours::yellow);
//    g.fillPath(p);
//}
