/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 26 Jan 2021 11:59:21am
    Author:  philg

  ==============================================================================
*/
#pragma once

#include <JuceHeader.h>
#include "PlaylistComponent.h"
#include <vector>

//==============================================================================
PlaylistComponent::PlaylistComponent(DeckGUI* _deckGUI1,
                                     DeckGUI* _deckGUI2
                                     ): deckGUI1(_deckGUI1),
                                        deckGUI2(_deckGUI2)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    /*trackTitles.push_back("Track 1");
    trackTitles.push_back("Track 2");
    trackTitles.push_back("Track 3");
    trackTitles.push_back("Track 4");
    trackTitles.push_back("Track 5");
    trackTitles.push_back("Track 6");*/


    tableComponent.getHeader().addColumn("Track title", 1, 400);
    tableComponent.getHeader().addColumn("2", 2, 200);
    tableComponent.getHeader().addColumn("3", 3, 50);

    tableComponent.setModel(this);

    addAndMakeVisible(tableComponent);
    addAndMakeVisible(importButton);
    addAndMakeVisible(loadDeck1Button);
    addAndMakeVisible(loadDeck2Button);

    importButton.addListener(this);
    loadDeck1Button.addListener(this);
    loadDeck2Button.addListener(this);



   //importTrack();


}

PlaylistComponent::~PlaylistComponent()
{
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("PlaylistComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    double pad = getHeight() - 50;
    tableComponent.setBounds(0, 0, getWidth(), pad);
    importButton.setBounds(0, pad, getWidth()/2, getHeight()/6);
    loadDeck1Button.setBounds(getWidth() / 2, pad, getWidth()/4, getHeight()/6);
    loadDeck2Button.setBounds(getWidth() - getWidth() /4, pad, getWidth() / 4, getHeight() / 6);


}

int PlaylistComponent::getNumRows()
{
    return trackTitles.size();
}

void PlaylistComponent::paintRowBackground(juce::Graphics & g,
                                           int rowNumber,
                                           int width,
                                           int height,
                                           bool rowIsSelceted)
{
    if (rowIsSelceted)
    {
        g.fillAll(juce::Colours::orange);
    }
    else
    {
        g.fillAll(juce::Colours::darkgrey);
    }
}

void PlaylistComponent::paintCell(juce::Graphics & g,
                                 int rowNumber,
                                 int columnId,
                                 int width,
                                 int height,
                                 bool rowIsSelceted)
{
    if (rowNumber < getNumRows())
    {
        if (columnId == 1)
        {
            g.drawText(trackTitles[rowNumber],
                2, 0,
                width - 4, height,
                juce::Justification::centredLeft,
                true);
        }
        
    }
   /* g.drawText(trackTitles[rowNumber],
               2, 0,
               width - 4, height,
               juce::Justification::centredLeft,
               true);*/
}

juce::Component* PlaylistComponent::refreshComponentForCell(int rowNumber,
                            int columnId,
                            bool rowIsSelected,
                            juce::Component *existingComponentToUpdate)
{
    if (columnId == 3)
    {
        if (existingComponentToUpdate == nullptr)
        {
            juce::TextButton* btn = new juce::TextButton{ "x" };
            juce::String id{ std::to_string(rowNumber) };
            btn->setComponentID(id); 

            btn->addListener(this);
            existingComponentToUpdate = btn;
        }
    }
    return existingComponentToUpdate;

  /* if (columnId == 3)
    {
        if (existingComponentToUpdate == nullptr)
        {
            juce::TextButton* btn2 = new juce::TextButton{ "play2" };
            juce::String id{ std::to_string(rowNumber) };
            btn2->setComponentID(id);

            btn2->addListener(this);
            existingComponentToUpdate = btn2;
        }
    }
    return existingComponentToUpdate;*/

}



void PlaylistComponent::buttonClicked(juce::Button* button)
{
    //int id = std::stoi(button->getComponentID().toStdString());
    //std::cout << "PlaylistComponent::buttonClicked " << trackTitles[id] << std::endl;

    //if (button == &btn)
    //{
    //    std::cout << "Play button was clicked1 " << std::endl;
    //    //playing = true;
    //    player->start();
    //}
    //if (button == &btn2)
    //{
    //    std::cout << "play button was clicked2 " << std::endl;
    //    //playing = false;
    //    player->start();
    //}
    if (button == &importButton)
    {
        importTrack();
        tableComponent.updateContent();

    }
    else if (button == &loadDeck1Button)
    {
        loadTrack(deckGUI1);
    }
    else if (button == &loadDeck2Button)
    {
        loadTrack(deckGUI2);
    }
    else
    {
        int id = std::stoi(button->getComponentID().toStdString());
        std::cout << "PlaylistComponent::buttonClicked " << trackTitles[id] << std::endl;
        DBG("PlaylistComponent::buttonClicked " + trackTitles[id]);
        removeTrack(id);
        tableComponent.updateContent();

    }
    
   
}

void PlaylistComponent::importTrack()
{

    juce::FileChooser fileSelect{ "Select file to import" };

    if (fileSelect.browseForMultipleFilesToOpen())
    {
        for (const juce::File& file : fileSelect.getResults())
        {
            
            juce::String fileName{ file.getFileNameWithoutExtension() };
            juce::URL audioFileURL{ file };
            trackTitles.push_back(fileName);
            trackURL.push_back(audioFileURL);
        }
        
    }
  
}

void PlaylistComponent::loadTrack(DeckGUI* deckGUI)
{
    int selectedRow{ tableComponent.getSelectedRow() };
    if (selectedRow != -1)
    {
        deckGUI->loadFile(trackURL[selectedRow]);
    }
}

void  PlaylistComponent::removeTrack(int id)
{
    trackTitles.erase(trackTitles.begin() + id);
    trackURL.erase(trackURL.begin() + id);

}
