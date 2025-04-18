#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include <iostream>
#include "DeckGUI.h"
#include "PlaylistComponent.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public juce::AudioAppComponent
                     
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    /** Prepares resources ready for playback */
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;

    /** Fetches blocks of audio data */
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;

    /** Releases memory at end of playback*/
    void releaseResources() override;

    //==============================================================================
    /** Paints background colour*/
    void paint (juce::Graphics& g) override;

    /** implement layout of components*/
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...

    juce::AudioFormatManager formatManager;
    juce::AudioThumbnailCache thumbCache{ 100 };

    DJAudioPlayer player1{ formatManager };
    DJAudioPlayer player2{ formatManager };
    DJAudioPlayer player{formatManager};

    DeckGUI deckGUI1{ &player1, formatManager, thumbCache };
    DeckGUI deckGUI2{ &player2, formatManager, thumbCache };

    juce::MixerAudioSource mixerSource;

    PlaylistComponent playlistComponent{ &deckGUI1, &deckGUI2, &player};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)

};
