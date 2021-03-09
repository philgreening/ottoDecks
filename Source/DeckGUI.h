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
    //DeckGUI(int _id,
    //        DJAudioPlayer* player,
    //        juce::AudioFormatManager& formatManagerToUse,
    //        juce::AudioThumbnailCache& cacheToUse);

    DeckGUI(DJAudioPlayer* player,
        juce::AudioFormatManager& formatManagerToUse,
        juce::AudioThumbnailCache& cacheToUse);
        //EqualizerDials equalizerDials);
            
        

    ~DeckGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    /** implement button listener */
    void buttonClicked(juce::Button*) override;

    /** implement Slider:: listner*/
    void sliderValueChanged(juce::Slider* slider) override;

    bool isInterestedInFileDrag (const juce::StringArray &files) override;
    void filesDropped(const juce::StringArray &files, int x, int y) override;

    void timerCallback() override;

    void loadFile(juce::URL audioURL);

    //juce::Slider volSlider;

    juce::String trackName;



private:

    //int id;

    juce::TextButton playButton{ "PLAY" };
    juce::TextButton stopButton{ "STOP" };
    juce::TextButton loadButton{ "LOAD" };

    juce::Slider volSlider;
    juce::Slider speedSlider;
    juce::Slider posSlider;

    //juce::Slider bassFreq;
    //juce::Slider midFreq;
    //juce::Slider trebleFreq;

    DJAudioPlayer* player;
    
    WaveformDisplay waveformDisplay;

    EqualizerDials equalizerDials;

    LookAndFeel customLook;

    AudioSpeedLookAndFeel speedLook;

    //WaveformDisplay look;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
