#include "PluginProcessor.h"
#include "PluginEditor.h"

class GaevVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound(juce::SynthesiserSound* sound) override
    {
        return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
    }

    void startNote(int midiNote, float velocity,
                   juce::SynthesiserSound*, int) override
    {
        phase = 0.0;
        frequency = juce::MidiMessage::getMidiNoteInHertz(midiNote);
        level = velocity * 0.2f;
        active = true;
    }

    void stopNote(float, bool allowTailOff) override
    {
        if (!allowTailOff)
            clearCurrentNote();
        active = false;
    }

    void pitchWheelMoved(int) override {}
    void controllerMoved(int, int) override {}

    void renderNextBlock(juce::AudioBuffer<float>& output,
                         int start, int count) override
    {
        auto* left = output.getWritePointer(0);
        auto* right = output.getNumChannels() > 1
                    ? output.getWritePointer(1) : left;

        for (int i = 0; i < count; ++i)
        {
            float sample = std::sin(phase) * level;
            phase += juce::MathConstants<double>::twoPi
                   * frequency / getSampleRate();

            if (phase > juce::MathConstants<double>::twoPi)
                phase -= juce::MathConstants<double>::twoPi;

            left[start + i] += sample;
            if (output.getNumChannels() > 1)
                right[start + i] += sample;
        }
    }

private:
    double phase = 0.0;
    double frequency = 440.0;
    float level = 0.0f;
    bool active = false;
};

class GaevSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote(int) override { return true; }
    bool appliesToChannel(int) override { return true; }
};

GaevSynthAudioProcessor::GaevSynthAudioProcessor()
    : AudioProcessor(BusesProperties()
        .withOutput("Output", juce::AudioChannelSet::stereo(), true))
{
    synth.addSound(new GaevSound());

    for (int i = 0; i < 8; ++i)
        synth.addVoice(new GaevVoice());
}

void GaevSynthAudioProcessor::prepareToPlay(double sampleRate, int)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
}

void GaevSynthAudioProcessor::releaseResources() {}

void GaevSynthAudioProcessor::processBlock(
    juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi)
{
    juce::ScopedNoDenormals noDenormals;
    buffer.clear();
    synth.renderNextBlock(buffer, midi, 0, buffer.getNumSamples());
}

juce::AudioProcessorEditor*
GaevSynthAudioProcessor::createEditor()
{
    return new GaevSynthAudioProcessorEditor(*this);
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GaevSynthAudioProcessor();
}
