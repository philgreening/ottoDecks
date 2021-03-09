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
#include "Track.h"

//==============================================================================
/*
*/
class PlaylistComponent  : public juce::Component,
                           public juce::TableListBoxModel,
                           public juce::Button::Listener,
                           public juce::TextEditor::Listener
{
public:
    PlaylistComponent(DeckGUI* _deckGUI1,
                      DeckGUI* _deckGUI2,
                      DJAudioPlayer* _player
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

    void loadTrack(DeckGUI* deckGUI);

    juce::String trackName;

    
private:

    void importTrack();
    bool findTrack(juce::String fileName);
    void searchTracks(juce::String searchTerm);
    int findPositionInTrack(juce::String searchTerm);
    //void loadTrack(DeckGUI* deckGUI);
    void removeTrack(int id);
    juce::String getTrackLength(juce::URL url);
    void saveTracklist();
    void loadTracklist();
    

    juce::TableListBox tableComponent;
    //juce::TextButton* btn = new juce::TextButton{ "play1" };
    //juce::TextButton* btn2 = new juce::TextButton{ "play2" };
   /* juce::TextButton btn { "Play1" };
    juce::TextButton btn2 { "Play2" };*/

   
    std::vector<Track> trackData;

    juce::File trackListFile;



    std::unique_ptr<juce::XmlElement> xmlData;

    juce::TextButton importButton{ "Import Track" };
    juce::TextButton loadDeck1Button{ "Load Track to Deck 1" };
    juce::TextButton loadDeck2Button{ "Load Track to Deck 2" };
    juce::TextEditor searchBar;


    DJAudioPlayer* player;

    LookAndFeel customLook;


    DeckGUI* deckGUI1;
    DeckGUI* deckGUI2;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
