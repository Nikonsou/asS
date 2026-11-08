#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class GaevSynthAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit GaevSynthAudioProcessorEditor(GaevSynthAudioProcessor&);
    ~GaevSynthAudioProcessorEditor() override = default;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    GaevSynthAudioProcessor& audioProcessor;
};
