/*
  ==============================================================================

    LookAndFeel.cpp
    Created: 4 Mar 2021 3:28:22pm
    Author:  philg

  ==============================================================================
*/
#include <JuceHeader.h>
#include "LookAndFeel.h"

LookAndFeel::LookAndFeel()
{
    setColour(juce::TextButton::buttonColourId, juce::Colours::antiquewhite);
    setColour(juce::TextButton::textColourOffId, juce::Colours::darkred);
    setColour(juce::TextEditor::backgroundColourId, juce::Colours::antiquewhite);
    setColour(juce::TextEditor::textColourId, juce::Colours::darkslategrey);
    setColour(juce::TableListBox::backgroundColourId, juce::Colours::darkred);
    //getTextButtonFont(20);
}

LookAndFeel::~LookAndFeel()
{
}

void LookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
    const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&)
{
    auto radius = (float)juce::jmin(width /2, height / 2) - 8.0f;
    auto radiusSmall = (float)juce::jmin(width / 4, height / 4) - 4.0f;
    auto centreX = (float)x + (float)width * 0.5f;
    auto centreY = (float)y + (float)height * 0.5f;
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    auto rw = radius * 2.0f;
    auto rxSmall = centreX - radiusSmall;
    auto rySmall = centreY - radiusSmall;
    auto rwSmall = radiusSmall * 2.0f;
    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    // fill
    g.setColour(juce::Colours::antiquewhite);
    g.fillEllipse(rx, ry, rw, rw);

    // outline
    g.setColour(juce::Colours::black);
    g.drawEllipse(rx, ry, rw, rw, 2.0f);

    g.setColour(juce::Colours::darkslategrey);
    g.fillEllipse(rxSmall, rySmall , rwSmall, rwSmall);

    juce::Path p;
    auto pointerLength = radius * 0.33f;
    auto pointerThickness = 3.0f;
    p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
    p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));

    // pointer
    g.setColour(juce::Colours::black);
    g.fillPath(p);
}

void LookAndFeel::drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
    float sliderPos, float minSliderPos, float maxSliderPos,
    const juce::Slider::SliderStyle, juce::Slider&)

{
    auto numTicks = 11;

    auto h1 = height / 70;
    auto h2 = height / 11;
    auto x1 = width / 2.3;
    auto x2 = width / 3;
    auto w1 = width / 8;
    
    juce::Rectangle<int> tick(width / 2.7, y, width /4, h1);
    juce::Rectangle<int> tickLabel(width /7, y, width/1.4 , h1);

    g.fillAll(juce::Colours::antiquewhite);

    for (auto  i = numTicks; i >= 0; i--)
    {
        
        auto numbers = juce::String(i);
        g.setFont(height/13);
        g.setColour(juce::Colours::black);
        g.drawText(numbers, tickLabel, juce::Justification::left);
        g.drawText(numbers, tickLabel, juce::Justification::right);
        g.setColour(juce::Colours::lightslategrey);
        g.fillRect(tick);
        tick.translate(0, h2);
        tickLabel.translate(0, h2);
    }


    g.fillRect(x1, y, w1, height);
    g.setColour(juce::Colours::darkred);
    g.fillRect(x1, (int) sliderPos, w1,  (int)minSliderPos - (int)sliderPos);

    g.setColour(juce::Colours::darkslategrey);
    g.fillRoundedRectangle(x2, (int)sliderPos, x2, height / 20, 5);
}

//void LookAndFeel::drawButtonText(juce::Graphics& g, juce::TextButton&, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
//{
//    g.setFont(20.0f);
//}

juce::Font LookAndFeel::getTextButtonFont(juce::TextButton&, int buttonHeight)
{
    return buttonHeight / 4;
}

