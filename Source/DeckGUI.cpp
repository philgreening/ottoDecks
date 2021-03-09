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
                    //EqualizerDials _equalizerDials
                    ) : player(_player),
                        waveformDisplay(formatManagerToUse, cacheToUse),
                        equalizerDials(_player)                    
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(playButton);

    playButton.setLookAndFeel(&customLook);
    stopButton.setLookAndFeel(&customLook);

    addAndMakeVisible(stopButton);
    //addAndMakeVisible(loadButton);

    addAndMakeVisible(waveformDisplay);

    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);

    addAndMakeVisible(equalizerDials);

    playButton.addListener(this);
    
    stopButton.addListener(this);
    //loadButton.addListener(this);

    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);

    volSlider.setRange(0.0, 1.0);
    volSlider.setValue(0.5);
    volSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    volSlider.setNumDecimalPlacesToDisplay(1);

    speedSlider.setRange(0.1, 2.0);
    speedSlider.setValue(1.0);
    speedSlider.setSkewFactorFromMidPoint(1.0);
    speedSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    speedSlider.setNumDecimalPlacesToDisplay(1);

    posSlider.setRange(0.0, 1.0);
    posSlider.setNumDecimalPlacesToDisplay(1);
    posSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);

    equalizerDials.setLookAndFeel(&customLook);
    speedSlider.setLookAndFeel(&speedLook);
    posSlider.setLookAndFeel(&waveformDisplay);
    volSlider.setLookAndFeel(&customLook);

    startTimer(200);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
    setLookAndFeel(nullptr);
}

void DeckGUI::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::white);
    g.drawText(trackName, getWidth()/2, getHeight()/2, 50, 50, juce::Justification::centredLeft);
    DBG("DeckGUI::paint track name:" << trackName);
}

void DeckGUI::resized()
{
    volSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, getWidth() / 8, 20);
    posSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, getWidth() / 8, 20);
    speedSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, getWidth() /8, 20);

    juce::Grid grid;
    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    grid.templateRows = { Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(2)) };
    grid.templateColumns = { Track(Fr(1)), Track(Fr(1)), Track(Fr(1)),Track(Fr(1)) };

    grid.items = { juce::GridItem(playButton).withArea(1,1,1,3),
                   juce::GridItem(stopButton).withArea(1,3,1,5),
                   juce::GridItem(waveformDisplay).withArea(2,1,2,5),
                   juce::GridItem(posSlider).withArea(2,1,2,5),
                   juce::GridItem(speedSlider).withArea(3,1,5,4),
                   juce::GridItem(volSlider).withArea(3,4,5,5),
                   juce::GridItem(equalizerDials).withArea(5,1,5,5),
                   };
    grid.setGap(juce::Grid::Px(5));

    grid.performLayout(getLocalBounds());

}

void DeckGUI::buttonClicked(juce::Button* button)

{
    if (button == &playButton)
    {
        std::cout << "Play button was clicked " << std::endl;
        //playing = true;
        player->start();
    }
    if (button == &stopButton)
    {
        std::cout << "Stop button was clicked " << std::endl;
        //playing = false;
        player->stop();
    }

}

void DeckGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volSlider)
    {
        //std::cout << "vol slider moved  " << slider->getValue() << std::endl;
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

bool DeckGUI::isInterestedInFileDrag(const juce::StringArray& files)
{
    std::cout << "DeckGUI::isInterestedinFileDrag" << std::endl;
    return true;
}
void DeckGUI::filesDropped(const juce::StringArray& files, int x, int y)
{
    std::cout << "DeckGUI::filesDropped" << std::endl;
    if (files.size() == 1)
    {
        player->loadURL(juce::URL{ juce::File{files[0]} });
    }
}

void DeckGUI::timerCallback()
{
   // std::cout << "DeckGUI::timerCallBack" << std::endl;
    auto posRelative = player->getPositionRelative();
    //DBG("DeckGUI::timerCallback position: " << posRelative);

    waveformDisplay.setPositionRelative(posRelative);

    if (posRelative >= 0)
    {
        posSlider.setValue(posRelative);
    }
    if (posRelative >= 1)
    {
        player->setPosition(0);
    }
}
void DeckGUI::loadFile(juce::URL audioURL)
{
    player->loadURL(audioURL);
    waveformDisplay.loadURL(audioURL);
}

