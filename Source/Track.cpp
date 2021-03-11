/*
  ==============================================================================

    Track.cpp
    Created: 19 Feb 2021 2:55:56pm
    Author:  philg

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Track.h"

//==============================================================================

Track::Track(juce::String  _title,
             juce::String _length,
             juce::URL _URL
             ) : title(_title),
                 length(_length),
                 url(_URL)
{
    DBG("Track::Track : " << title + ", " + length + ", " + url.toString(false));
}

Track::~Track()
{
}

