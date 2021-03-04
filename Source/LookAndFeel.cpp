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
    auto pointerLength = radius * 0.33f;
    auto pointerThickness = 3.0f;
    p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
    p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));

    // pointer
    g.setColour(juce::Colours::black);
    g.fillPath(p);
}