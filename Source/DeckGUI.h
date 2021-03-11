/*
  ==============================================================================

    DeckGUI.h
    Created: 21 Jan 2021 7:06:54pm
    Author:  philg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "EqualizerDials.h"
#include "LookAndFeel.h"
#include "AudioSpeedLookAndFeel.h"

//==============================================================================
/*
*/

class DeckGUI : public juce::Component,
                public juce::Button::Listener,
                public juce::Slider::Listener,
                public juce::FileDragAndDropTarget,
                public juce::Timer        
{
public:
    /** Constructor */
    DeckGUI(DJAudioPlayer* player,
        juce::AudioFormatManager& formatManagerToUse,
        juce::AudioThumbnailCache& cacheToUse);
             
    /** Destructor */
    ~DeckGUI() override;

    /** Paints to deck*/
    void paint (juce::Graphics&) override;

    /** implement layout of deck*/
    void resized() override;

    /** implement button listener */
    void buttonClicked(juce::Button*) override;

    /** implement Slider:: listner*/
    void sliderValueChanged(juce::Slider* slider) override;

    /** Checks if file drag from external source is being detected */
    bool isInterestedInFileDrag (const juce::StringArray &files) override;

    /** Receives external files dragged and dropped and passes them to DJAudioPlayer and WaveformDisplay*/
    void filesDropped(const juce::StringArray &files, int x, int y) override;

    /** listens for changes to the waveform position and updates pos slider and track info*/
    void timerCallback() override;

    /** Receives audio URL and loads it to the DJAudioPlayer and WaveformDisplay */
    void loadFile(juce::URL audioURL);

    /** Variable to hold track name passed from PlaylistComponent*/
    juce::String trackName;

private:
    juce::TextButton playButton{ "Play" };
    juce::TextButton stopButton{ "Stop" };

    juce::Slider volSlider;
    juce::Slider speedSlider;
    juce::Slider posSlider;

    juce::Rectangle<int> trackInfo;

    juce::String trackCurrenPos;

    DJAudioPlayer* player;
    WaveformDisplay waveformDisplay;
    EqualizerDials equalizerDials;
    LookAndFeel customLook;
    AudioSpeedLookAndFeel speedLook;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};

