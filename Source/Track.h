/*
  ==============================================================================

    Track.h
    Created: 19 Feb 2021 2:55:56pm
    Author:  philg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Track  
{
public:
    /**Constructor */
    Track(juce::String title,
          juce::String length,
          juce::URL URL);
    /** */
    ~Track();

    /**Stores track title */
    juce::String title;

    /**Stores track length */
    juce::String length;

    /**Stores track url */
    juce::URL url;

private:   
};
