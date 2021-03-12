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
                                     DeckGUI* _deckGUI2,
                                     DJAudioPlayer* _player
                                     ): deckGUI1(_deckGUI1),
                                        deckGUI2(_deckGUI2),
                                        player(_player)
{
    //set headers for table
    tableComponent.getHeader().addColumn("Track title", 1, 158);
    tableComponent.getHeader().addColumn("Length", 2, 50);
    tableComponent.getHeader().addColumn("Remove", 3, 55);

    tableComponent.setModel(this);

    //make components visable
    addAndMakeVisible(tableComponent);
    addAndMakeVisible(importButton);
    addAndMakeVisible(searchBar);
    addAndMakeVisible(loadDeck1Button);
    addAndMakeVisible(loadDeck2Button);

    //add listners
    importButton.addListener(this);
    searchBar.addListener(this);
    loadDeck1Button.addListener(this);
    loadDeck2Button.addListener(this);

    //set component custom look and feel
    tableComponent.setLookAndFeel(&customLook);
    importButton.setLookAndFeel(&customLook);
    searchBar.setLookAndFeel(&customLook);
    loadDeck1Button.setLookAndFeel(&customLook);
    loadDeck2Button.setLookAndFeel(&customLook);

    //set search bar parameters
    searchBar.setFont(20.0f);
    searchBar.setTextToShowWhenEmpty("Search for a track...", juce::Colours::darkred);
    searchBar.onReturnKey = [this] {searchTracks(searchBar.getText()); };

    //set location of xml file to save tracklist
    trackListFile = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userMusicDirectory).getChildFile("TrackList.xml");

    //load tracklist on start
    loadTracklist();
}

PlaylistComponent::~PlaylistComponent()
{
    //save tracklist on exit
    saveTracklist();
    setLookAndFeel(nullptr);
}

void PlaylistComponent::resized()
{
    //Sets up grid for layout
    juce::Grid grid;
    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    grid.templateRows = { Track(Fr(2)), Track(Fr(1)), Track(Fr(10)),Track(Fr(2)) };
    grid.templateColumns = { Track(Fr(1)),Track(Fr(1)) };

    //positions items on grid
    grid.items = { juce::GridItem(importButton).withArea(1,1,1,3),
                    juce::GridItem(searchBar).withArea(2,1,2,3),
                    juce::GridItem(tableComponent).withArea(3,1,4,3),
                    juce::GridItem(loadDeck1Button),
                    juce::GridItem(loadDeck2Button),
    };

    grid.setGap(juce::Grid::Px(5));
    grid.performLayout(getLocalBounds());
}

int PlaylistComponent::getNumRows()
{
    return trackData.size();
}

void PlaylistComponent::paintRowBackground(juce::Graphics & g,
                                           int rowNumber,
                                           int width,
                                           int height,
                                           bool rowIsSelceted)
{
    if (rowIsSelceted)
    {
        g.fillAll(juce::Colours::darkslategrey);
        g.setColour(juce::Colours::antiquewhite);
    }
    else
    {
        g.fillAll(juce::Colours::antiquewhite);
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
            g.drawText(trackData[rowNumber].title,
                2, 0,
                width - 4, height,
                juce::Justification::centredLeft,
                true);
        }

        if (columnId == 2)
        {
            g.drawText(trackData[rowNumber].length,
                2, 0,
                width - 4, height,
                juce::Justification::centredLeft,
                true);
        }
    }  
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
            juce::TextButton* btn = new juce::TextButton{ "-" };
            btn->setColour(juce::TextButton::buttonColourId, juce::Colours::darkslategrey);
            btn->setColour(juce::TextButton::textColourOffId, juce::Colours::antiquewhite);
            juce::String id{ std::to_string(rowNumber) };
            btn->setComponentID(id); 
            btn->addListener(this);
            existingComponentToUpdate = btn;
        }
    }
    return existingComponentToUpdate;
}

void PlaylistComponent::buttonClicked(juce::Button* button)
{
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
        removeTrack(id);
        tableComponent.updateContent();
    }
}

void PlaylistComponent::importTrack()
{
    juce::FileChooser fileSelect{ "Select file to import" };

    //adds track to playlist if not in library
    if (fileSelect.browseForMultipleFilesToOpen())
    {
        for (const juce::File& file : fileSelect.getResults())
        {
            juce::String fileName{ file.getFileNameWithoutExtension() };
            if (!findTrack(fileName))
            {
                juce::URL url{ file };
                juce::String length = getTrackLength(url);
                Track addTrack(fileName, length, url);
                trackData.push_back(addTrack);
            }
            else
            {
                juce::AlertWindow::showMessageBox(juce::AlertWindow::AlertIconType::NoIcon,
                                                  "Import Error",
                                                  fileName + " is already in your library",
                                                  "", nullptr);
            }
        };
    }
}
//code adapted from https://stackoverflow.com/questions/15517991/search-a-vector-of-objects-by-object-attribute
bool PlaylistComponent::findTrack(juce::String fileName)
{
    std::string file = fileName.toStdString();

    auto it = std::find_if(trackData.begin(),
              trackData.end(),
              [&file](const Track& t)
              {return t.title.toStdString() == file; });

    if (it != trackData.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void PlaylistComponent::searchTracks(juce::String searchTerm)
{
    if (searchTerm != "")
    {
        int row = findPositionInTrack(searchTerm);
        tableComponent.selectRow(row);
    }
    else
    {
        tableComponent.deselectAllRows();
    }
}

//code adapted from https://stackoverflow.com/questions/15517991/search-a-vector-of-objects-by-object-attribute
int PlaylistComponent::findPositionInTrack(juce::String searchTerm)
{
    auto it = std::find_if(trackData.begin(),
              trackData.end(),
              [&searchTerm](const Track& t)
              {return t.title.containsIgnoreCase(searchTerm); });

    int pos = -1;

    if (it != trackData.end())
    {
        pos = std::distance(trackData.begin(), it);
    }

    return pos;
}

void PlaylistComponent::loadTrack(DeckGUI* deckGUI)
{
    int selectedRow{ tableComponent.getSelectedRow() };
    if (selectedRow != -1)
    {
        deckGUI->loadFile(trackData[selectedRow].url);
        trackTitle = trackData[selectedRow].title;
        deckGUI->trackName = trackTitle;
    }
}

void  PlaylistComponent::removeTrack(int id)
{
    trackData.erase(trackData.begin() + id);
}

juce::String PlaylistComponent::getTrackLength(juce::URL audioURL)
{
    player->loadURL(audioURL);

    int minutes( player->getLengthInSeconds() / 60 );
    int seconds(player->getLengthInSeconds() % 60);

    juce::String trackLength = std::to_string(minutes) + ":"  + std::to_string(seconds);

    if (seconds < 10)
    {
        trackLength = std::to_string(minutes) + ":" + "0" + std::to_string(seconds);
    }
 
    return trackLength;
}

void  PlaylistComponent::saveTracklist()
{
    //Creates xml element
    juce::XmlElement trackList { "Track_List" };

    //adds tracks and attribute info to track xml child element
    for (Track& e : trackData)
    {
        juce::XmlElement* track = new juce::XmlElement{ "Track" };

        track->setAttribute("title", e.title);
        track->setAttribute("length", e.length);
        track->setAttribute("URL", e.url.toString(false));

        trackList.addChildElement(track);
    }
    trackList.writeTo(trackListFile);
}

void PlaylistComponent::loadTracklist()
{
    //loads tracklist from xml file
    if (trackListFile.exists())
    {
        xmlData = juce::parseXML(trackListFile);
       
        forEachXmlChildElement(*xmlData, data)

        {
            juce::String title = data->getStringAttribute("title");
            juce::String length = data->getStringAttribute("length");
            juce::URL url = data->getStringAttribute("URL");

            Track addTrack{ title, length, url };

            trackData.push_back(addTrack);
        }
    }
}

bool PlaylistComponent::isInterestedInFileDrag(const juce::StringArray& files)
{
    DBG("PlaylistComponent::isInterestedinFileDrag");
    return true;
}

void PlaylistComponent::filesDropped(const juce::StringArray& files, int x, int y)
{
    DBG("PlaylistComponent::filesDropped");
    if (files.size() == 1)
    {
        juce::File file =  juce::File{files[0]};
        juce::String fileName =  file.getFileNameWithoutExtension();
        if (!findTrack(fileName))
        {
            juce::URL url{ file };
            juce::String length = getTrackLength(url);
            Track addTrack(fileName, length, url);
            trackData.push_back(addTrack);
            tableComponent.updateContent();
        }
        else
        {
            juce::AlertWindow::showMessageBox(juce::AlertWindow::AlertIconType::NoIcon,
                "Import Error",
                fileName + " is already in your library",
                "", nullptr);
        }
    }
}

juce::var PlaylistComponent::getDragSourceDescription(const juce::SparseSet< int >& rowsToDescribe)
{
    int selectedRow{ tableComponent.getSelectedRow() };
    
    if (selectedRow != -1)
    {
        juce::StringArray td;
        juce::String url = trackData[selectedRow].url.toString(false);
        
        td.insert(0,url);
        td.insert(1, trackData[selectedRow].title);

        return td;
    }
    else
    {
        return false;
    }
}