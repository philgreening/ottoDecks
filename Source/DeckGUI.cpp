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
//DeckGUI::DeckGUI(int _id,
//                DJAudioPlayer* _player,
//                juce::AudioFormatManager& formatManagerToUse,
//                juce::AudioThumbnailCache& cacheToUse
//                ) : id(_id),
//                   player(_player),
//                   waveformDisplay(id, formatManagerToUse, cacheToUse)


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
    addAndMakeVisible(stopButton);
    //addAndMakeVisible(loadButton);

    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);

    //addAndMakeVisible(bassFreq);
    //addAndMakeVisible(midFreq);
    //addAndMakeVisible(trebleFreq);

    addAndMakeVisible(waveformDisplay);

    addAndMakeVisible(equalizerDials);

    playButton.addListener(this);
    stopButton.addListener(this);
    //loadButton.addListener(this);

    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);

    //bassFreq.addListener(this);
    //midFreq.addListener(this);
    //trebleFreq.addListener(this);

    volSlider.setRange(0.0, 1.0);
    volSlider.setValue(0.5);
    volSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    volSlider.setNumDecimalPlacesToDisplay(1);

    speedSlider.setRange(0.1, 10.0);
    speedSlider.setValue(1.0);
    speedSlider.setNumDecimalPlacesToDisplay(1);

    posSlider.setRange(0.0, 1.0);
    posSlider.setNumDecimalPlacesToDisplay(1);


    //bassFreq.setRange(0.1, 100.0);
    //bassFreq.setValue(1.0);
    //midFreq.setRange(0.1, 100.0);
    //midFreq.setValue(1.0);
    //trebleFreq.setRange(0.1, 100.0);
    //trebleFreq.setValue(1.0);
    //

    startTimer(500);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (juce::Graphics& g)
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
    g.drawText ("DeckGUI", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

//void DeckGUI::resized()
//{
//    // This method is where you should set the bounds of any child
//    // components that your component contains..
//    volSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, getWidth() / 8, 20);
//
//
//    double rowH = getHeight() / 8;
//    playButton.setBounds(0, 0, getWidth()/2, rowH);
//    stopButton.setBounds(getWidth()/2, 0, getWidth()/2, rowH);
//    volSlider.setBounds(getWidth()/2, rowH , getWidth()/2, rowH * 2);
//    speedSlider.setBounds(0, rowH , getWidth()/2, rowH);
//    posSlider.setBounds(0, rowH * 2, getWidth()/2, rowH);
//
//    //bassFreq.setBounds(getWidth()/2, rowH * 2, getWidth()/2, rowH);
//    //midFreq.setBounds(getWidth()/2, rowH * 3, getWidth()/2, rowH);
//    //trebleFreq.setBounds(getWidth() / 2, rowH * 4, getWidth() / 2, rowH);
//    equalizerDials.setBounds(0, rowH * 3, getWidth(), rowH * 3);
//
//    waveformDisplay.setBounds(0, rowH * 6, getWidth(), rowH * 2);
//
//    //comboBox.setBounds(0, 0 , getWidth() /5, 50);
//    //loadButton.setBounds(0, rowH * 7, getWidth(), rowH);
//
//}

void DeckGUI::resized()
{
    volSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, getWidth() / 8, 20);
    posSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, getWidth() / 8, 20);
    speedSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, getWidth() / 8, 20);

    juce::Grid grid;
    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    grid.templateRows = { Track(Fr(1)), Track(Fr(2)), Track(Fr(1)), Track(Fr(1)), Track(Fr(2)) };
    grid.templateColumns = { Track(Fr(1)), Track(Fr(1))};

    grid.items = { juce::GridItem(playButton).withArea(1,1),
                   juce::GridItem(stopButton).withArea(1,2),
                   juce::GridItem(speedSlider).withArea(3,1),
                   juce::GridItem(posSlider).withArea(4,1),
                   juce::GridItem(volSlider).withArea(3,2,5,2),
                   juce::GridItem(equalizerDials).withArea(5,1,5,3),
                   juce::GridItem(waveformDisplay).withArea(2,1,2,3)
                   };

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
    //if (button == &loadButton)
    //{
    //    juce::FileChooser chooser{"Select a file...."};
    //    if (chooser.browseForFileToOpen())
    //    {
    //        /*loadURL(juce::URL{ chooser.getURLResult()});
    //        trackTime = transportSource.getLengthInSeconds();
    //        posSlider.setRange(0.0, trackTime);*/
    //        player->loadURL(juce::URL{chooser.getResult()});
    //        waveformDisplay.loadURL(juce::URL{ chooser.getResult() });
    //    }
    //}
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
    //if (slider == &bassFreq)
    //{
    //    player->setBass(slider->getValue());

    //}
    //if (slider == &midFreq)
    //{
    //    player->setMid(slider->getValue());
    //}
    //if (slider == &trebleFreq)
    //{
    //    player->setTreble(slider->getValue());
    //}
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

    waveformDisplay.setPositionRelative(
            player->getPositionRelative());
}
void DeckGUI::loadFile(juce::URL audioURL)
{
    player->loadURL(audioURL);
    waveformDisplay.loadURL(audioURL);
}

