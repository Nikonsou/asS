#include "PluginEditor.h"

GaevSynthAudioProcessorEditor::GaevSynthAudioProcessorEditor(
    GaevSynthAudioProcessor& processor)
    : AudioProcessorEditor(&processor),
      audioProcessor(processor)
{
    setSize(600, 400);
}

void GaevSynthAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(18, 18, 25));

    g.setColour(juce::Colours::white);
    g.setFont(30.0f);
    g.drawText("СИНТЕЗАТОР ГАЕВА",
               getLocalBounds().removeFromTop(90),
               juce::Justification::centred);

    g.setColour(juce::Colour(120, 100, 255));
    g.setFont(16.0f);
    g.drawText("DIGITAL SYNTHESIZER",
               getLocalBounds().removeFromTop(130),
               juce::Justification::centred);
}

void GaevSynthAudioProcessorEditor::resized()
{
}
