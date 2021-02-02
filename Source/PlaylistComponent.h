/*
  ==============================================================================

    PlaylistComponent.h
    Created: 26 Jan 2021 11:59:21am
    Author:  philg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class PlaylistComponent  : public juce::Component,
                           public juce::TableListBoxModel,
                           public juce::Button::Listener
{
public:
    PlaylistComponent();
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

    juce::TableListBox tableComponent;
    std::vector<std::string> trackTitles;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
