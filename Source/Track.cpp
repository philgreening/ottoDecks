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
             juce::URL _URL) 
    : title(_title),
    url(_URL)

{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    DBG("Track::Track URL: " << url.toString(false));

}

Track::~Track()
{
}

