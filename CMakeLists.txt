cmake_minimum_required(VERSION 3.22)

project(GaevSynth VERSION 1.0.0)

include(FetchContent)

FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG 8.0.6
)

FetchContent_MakeAvailable(JUCE)

juce_add_plugin(GaevSynth
    COMPANY_NAME "Gaev"
    PLUGIN_NAME "Синтезатор Гаева"
    FORMATS VST3
    PRODUCT_NAME "Синтезатор Гаева"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
)

target_sources(GaevSynth PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginEditor.cpp
)

target_compile_features(GaevSynth PRIVATE cxx_std_17)

target_link_libraries(GaevSynth PRIVATE
    juce::juce_audio_utils
    juce::juce_dsp
)
