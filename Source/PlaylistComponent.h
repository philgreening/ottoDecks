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
                           public juce::TextEditor::Listener,
                           public juce::FileDragAndDropTarget,
                           public juce::DragAndDropContainer
{
public:
    /**Constructor */
    PlaylistComponent(DeckGUI* _deckGUI1,
                      DeckGUI* _deckGUI2,
                      DJAudioPlayer* _player
                      );
    /**Destructor */
    ~PlaylistComponent() override;
    
    /** */
    void resized() override;

    /**Gets number of rows with content */
    int getNumRows() override;

    /** Paints table row background */
    void paintRowBackground(juce::Graphics&,
                            int rowNumber,
                            int width,
                            int height,
                            bool rowIsSelceted) override;

    /** Paints table cell bacground */
    void paintCell(juce::Graphics&,
                   int rowNumber,
                   int columnId,
                   int width,
                   int height,
                   bool rowIsSelceted) override;

    /**Updates table cell contents */
    juce::Component* refreshComponentForCell(int rowNumber,
                                             int columnId,
                                             bool rowIsSelected,
                                             juce::Component *existingComponentToUpdate) override;
    /**Implement button listner */
    void buttonClicked(juce::Button* button) override;

    /** Checks if file drag from external source is being detected */
    bool isInterestedInFileDrag(const juce::StringArray& files) ;

    /** Receives external files dragged and dropped and passes them to DJAudioPlayer and WaveformDisplay*/
    void filesDropped(const juce::StringArray& files, int x, int y) override;

    /** gets row information on drag and stores it in an array of strings to pass to DeckGUI::isInterestedInDragSource*/
    juce::var getDragSourceDescription(const juce::SparseSet< int >& rowsToDescribe) override;

    /**Loads track file to DeckGUI for playback and updates track info */
    void loadTrack(DeckGUI* deckGUI);

    /**Stores track title to pass onto Deck GUI */
    juce::String trackTitle;

private:
    void importTrack();
    bool findTrack(juce::String fileName);
    void searchTracks(juce::String searchTerm);
    int findPositionInTrack(juce::String searchTerm);
    void removeTrack(int id);
    juce::String getTrackLength(juce::URL url);
    void saveTracklist();
    void loadTracklist();
    
    juce::TableListBox tableComponent;

    juce::File trackListFile;
    std::vector<Track> trackData;
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
