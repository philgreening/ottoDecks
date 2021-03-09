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

    //g.drawFittedText();

    juce::Path p;
    //juce::Path t;
    auto pointerLength = radius * 0.33f;
    auto pointerThickness = 3.0f;
    p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
    //t.addRectangle(-pointerThickness * 0.5f, -radiusSmall, pointerThickness, pointerLength -5);
    //t.addRectangle(-pointerThickness * 0.5f + 10, -radiusSmall , pointerThickness, pointerLength - 5);

    p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));
    //t.applyTransform(juce::AffineTransform::rotation(0).translated(centreX, centreY));

    // pointer
    g.setColour(juce::Colours::black);
    g.fillPath(p);
    //g.fillPath(t);
}

void LookAndFeel::drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
    float sliderPos, float minSliderPos, float maxSliderPos,
    const juce::Slider::SliderStyle, juce::Slider&)

{
 /*   int y = (int)deckGUI->volSlider.getValue();

    g.fillRect(x,y, deckGUI->getWidth(),deckGUI->getHeight());*/

    //g.fillRect();


    g.setColour(juce::Colours::antiquewhite);
    //juce::Line<int> tick(width/2, 0, width/4, 0);

    auto numTicks = 11;
    juce::Rectangle<int> tick(width / 2.7, y, width /4, height /70);
    juce::Rectangle<int> tickLabel(width /6, y, width/1.6 , height / 70);

    for (auto  i = numTicks; i >= 0; i--)
    {
        auto numbers = juce::String(i);
        g.setFont(10.0f);
        g.drawText(numbers, tickLabel, juce::Justification::left);
        g.drawText(numbers, tickLabel, juce::Justification::right);
        g.fillRect(tick);
        tick.translate(0, height/11);
        tickLabel.translate(0, height / 11);
    }

    g.setColour(juce::Colours::slategrey);
    g.fillRect(width / 2.3, y, width / 8, height);
    g.setColour(juce::Colours::red);
    g.fillRect(width / 2.3, (int) sliderPos, width / 8,  (int)minSliderPos - (int)sliderPos);

    g.setColour(juce::Colours::antiquewhite);
    g.fillRect(width / 3, (int)sliderPos, width / 3, height / 20);

}