/*
  ==============================================================================

    PlaylistComponent.h
    Created: 26 Jan 2021 11:59:21am
    Author:  philg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "DeckGUI.h"

//==============================================================================
/*
*/
class PlaylistComponent  : public juce::Component,
                           public juce::TableListBoxModel,
                           public juce::Button::Listener
                            
{
public:
    PlaylistComponent(DeckGUI* _deckGUI1,
                      DeckGUI* _deckGUI2
                      );

    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    int getNumRows() override;

    void paintRowBackground(juce::Graphics&,
                            int rowNumber,
                            int width,
                            int height,
                            bool rowIsSelceted) override;

    void paintCell(juce::Graphics&,
                   int rowNumber,
                   int columnId,
                   int width,
                   int height,
                   bool rowIsSelceted) override;

    juce::Component* refreshComponentForCell(int rowNumber,
        int columnId,
        bool rowIsSelected,
        juce::Component *existingComponentToUpdate) override;

    void buttonClicked(juce::Button* button) override;
    
private:

    void importTrack();
    void loadTrack(DeckGUI* deckGUI);
    void removeTrack(int id);

    juce::TableListBox tableComponent;
    //juce::TextButton* btn = new juce::TextButton{ "play1" };
    //juce::TextButton* btn2 = new juce::TextButton{ "play2" };
   /* juce::TextButton btn { "Play1" };
    juce::TextButton btn2 { "Play2" };*/

    std::vector<juce::String> trackTitles;
    std::vector<std::string> trackLengths;
    std::vector<juce::String> tracks;
    std::vector<juce::URL> trackURL;
    
    juce::TextButton importButton{ "Import Track" };
    juce::TextButton loadDeck1Button{ "Load Track to Deck 1" };
    juce::TextButton loadDeck2Button{ "Load Track to Deck 2" };


    //DJAudioPlayer* player;
    DeckGUI* deckGUI1;
    DeckGUI* deckGUI2;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
