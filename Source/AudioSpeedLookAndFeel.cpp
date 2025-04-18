/*
  ==============================================================================

    AudioSpeedLookAndFeel.cpp
    Created: 7 Mar 2021 12:11:55pm
    Author:  philg

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AudioSpeedLookAndFeel.h"

//==============================================================================
AudioSpeedLookAndFeel::AudioSpeedLookAndFeel()
{
}

AudioSpeedLookAndFeel::~AudioSpeedLookAndFeel()
{
}

void AudioSpeedLookAndFeel::drawRotarySlider(juce::Graphics& g,
                                             int x, int y,
                                             int width, int height,
                                             float sliderPos,
                                             const float rotaryStartAngle,
                                             const float rotaryEndAngle, juce::Slider&)
{
    //sets radius of each ellipse
    auto radius = (float)juce::jmin(width / 2, height / 2) - 8.0f;
    auto radiusSmall = (float)juce::jmin(width / 6, height / 6) - 2.0f;
    auto radiusTiny = (float)juce::jmin(width / 12, height / 12) - 8.0f;
    auto radius1 = (float)juce::jmin(width / 2.5, height / 2.5) - 2.0f;
    auto radius2 = (float)juce::jmin(width / 3, height / 3) - 5.0;
    auto radius3 = (float)juce::jmin(width / 3.5, height / 3.5) - 10.0f;

    auto centreX = (float)x + (float)width * 0.5f;
    auto centreY = (float)y + (float)height * 0.5f;

    //Viynl ellipse settings
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    auto rw = radius * 2.0f;

    // Small ellipse and tiny ellipse settings
    auto rxSmall = centreX - radiusSmall;
    auto rySmall = centreY - radiusSmall;
    auto rwSmall = radiusSmall * 2.0f;

    auto rxTiny = centreX - radiusTiny;
    auto ryTiny = centreY - radiusTiny;
    auto rwTiny = radiusTiny * 2.0f;

    //settings for viynl grooves
    auto rx1 = centreX - radius1;
    auto ry1 = centreY - radius1;
    auto rw1 = radius1 * 2.0f;

    auto rx2 = centreX - radius2;
    auto ry2 = centreY - radius2;
    auto rw2 = radius2 * 2.0f;

    auto rx3 = centreX - radius3;
    auto ry3 = centreY - radius3;
    auto rw3 = radius3 * 2.0f;

    //sets angle of rotary slider
    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    g.fillAll(juce::Colours::antiquewhite);

    // fill viynl ellipse
    g.setColour(juce::Colours::black);
    g.fillEllipse(rx, ry, rw, rw);

    // draws viynl grooves
    g.setColour(juce::Colours::grey);
    g.drawEllipse(rx1, ry1, rw1, rw1, 1.0f);
    g.drawEllipse(rx2, ry2, rw2, rw2, 1.0f);
    g.drawEllipse(rx3, ry3, rw3, rw3, 1.0f);

    //fill small ellipse
    g.setColour(juce::Colours::darkred);
    g.fillEllipse(rxSmall , rySmall , rwSmall , rwSmall );

    //fill tiny ellipse
    g.setColour(juce::Colours::grey);
    g.fillEllipse(rxTiny, ryTiny, rwTiny, rwTiny);

    //draws pointer along path and updates relating to slider position
    juce::Path p;
    auto pointerLength = radius * 0.33f;
    auto pointerThickness = 3.0f;
    p.addRectangle(-pointerThickness * 1.0f, 
                   -radius, pointerThickness,
                    pointerLength);
    p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));

    g.setColour(juce::Colours::darkred);
    g.fillPath(p);
}
