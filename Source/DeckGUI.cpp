/*
  ==============================================================================

    DeckGUI.cpp
    Created: 21 Jan 2021 7:06:54pm
    Author:  philg

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================

    DeckGUI::DeckGUI(DJAudioPlayer* _player,
                    juce::AudioFormatManager& formatManagerToUse,
                    juce::AudioThumbnailCache& cacheToUse
                    ) : player(_player),
                        waveformDisplay(formatManagerToUse, cacheToUse),
                        equalizerDials(_player)                    
{
    //make components visable
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(waveformDisplay);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);
    addAndMakeVisible(equalizerDials);

    //add listners
    playButton.addListener(this);
    stopButton.addListener(this);
    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);

    //set look and feel of components
    playButton.setLookAndFeel(&customLook);
    stopButton.setLookAndFeel(&customLook);
    posSlider.setLookAndFeel(&waveformDisplay);
    speedSlider.setLookAndFeel(&speedLook);
    volSlider.setLookAndFeel(&customLook);
    equalizerDials.setLookAndFeel(&customLook);

    //set properties of components
    volSlider.setRange(0.0, 1.0);
    volSlider.setValue(0.5);
    volSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    volSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);

    speedSlider.setRange(0.1, 2.0);
    speedSlider.setValue(1.0);
    speedSlider.setSkewFactorFromMidPoint(1.0);
    speedSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    speedSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);

    posSlider.setRange(0.0, 1.0);
    posSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    posSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);

    startTimer(200);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
    setLookAndFeel(nullptr);
}

void DeckGUI::paint (juce::Graphics& g)
{
    // draw and fill track info box
    juce::Rectangle<int> trackInfoBox(0, getHeight() / 3.2,
                                      getWidth(), getHeight() / 14);
    g.setColour(juce::Colours::antiquewhite);
    g.fillRect(trackInfoBox);

    //draw and set coulour of track info text and track position
    g.setColour(juce::Colours::darkred);
    g.setFont(getHeight()/40);
    g.drawText(trackName + "    " + player->getTrackCurrentPos(),
               trackInfoBox, juce::Justification::centred);
}

void DeckGUI::resized()
{
    //Sets up grid for layout
    juce::Grid grid;
    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    grid.templateRows = { Track(Fr(2)), Track(Fr(2)),
                          Track(Fr(1)), Track(Fr(2)),
                          Track(Fr(2)), Track(Fr(4)) };

    grid.templateColumns = { Track(Fr(1)), Track(Fr(1)),
                             Track(Fr(1)),Track(Fr(1)) };

    //positions items on grid
    grid.items = { juce::GridItem(playButton).withArea(1,1,1,3),
                   juce::GridItem(stopButton).withArea(1,3,1,5),
                   juce::GridItem(waveformDisplay).withArea(2,1,2,5),
                   juce::GridItem(posSlider).withArea(2,1,2,5),
                   juce::GridItem(speedSlider).withArea(4,1,6,4),
                   juce::GridItem(volSlider).withArea(4,4,6,5),
                   juce::GridItem(equalizerDials).withArea(6,1,6,5),
                   };

    grid.setGap(juce::Grid::Px(5));
    grid.performLayout(getLocalBounds());
}

void DeckGUI::buttonClicked(juce::Button* button)
{
    if (button == &playButton)
    {
        DBG("Play button was clicked ");
        player->start();
    }
    if (button == &stopButton)
    {
        DBG("Stop button was clicked ");
        player->stop();
    }
}

void DeckGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue());
    }
    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }
    if (slider == &posSlider)
    {
        player->setPositionRelative(slider->getValue());
    }
}

void DeckGUI::timerCallback()
{
    auto posRelative = player->getPositionRelative();
    waveformDisplay.setPositionRelative(posRelative);

    //updates slider to position of track
    if (posRelative >= 0)
    {
        posSlider.setValue(posRelative);
    }

    //sets track back to start when finished
    if (posSlider.getValue() == 1)
    {
        posSlider.setValue(0);
    }
    //updates track info
    repaint();
}

void DeckGUI::loadFile(juce::URL audioURL)
{
    player->loadURL(audioURL);
    waveformDisplay.loadURL(audioURL);
}

bool DeckGUI::isInterestedInDragSource(const SourceDetails& dragSourceDetails)
{
    DBG("DeckGUI::isInterestedinFileDragSource");
    return true;
}

void DeckGUI::itemDropped(const SourceDetails& dragSourceDetails)
{
    juce::URL audioURL = juce::URL(dragSourceDetails.description[0]);
    trackName = dragSourceDetails.description[1];

    player->loadURL(audioURL);
    waveformDisplay.loadURL(audioURL);
}