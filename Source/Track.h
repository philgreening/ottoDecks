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
    //Track(juce::File _file);
    Track(juce::String title, juce::URL URL);

    ~Track();

    juce::String title;
    juce::URL url;
    //juce::File file;

private:

    
   
    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Track)
};
