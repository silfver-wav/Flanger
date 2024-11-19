cmake_minimum_required(VERSION 3.22)

project(FlangerPlugin VERSION 0.0.1)

set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/FlangerPlugin")

juce_add_plugin(${PROJECT_NAME}
    COMPANY_NAME LICK_MY_DICK
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    PLUGIN_MANUFACTURER_CODE MCMP
    PLUGIN_CODE EXPL
    FORMATS Standalone VST3
    PRODUCT_NAME "Flanger"
)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB_RECURSE SOURCE_FILES "${SOURCE_DIR}/*.cpp" "${SOURCE_DIR}/*.h")
target_sources(FlangerPlugin PRIVATE ${SOURCE_FILES})

#target_sources(${PROJECT_NAME}
#    PRIVATE
#        source/PluginEditor.cpp
#        source/PluginProcessor.cpp
#        ${INCLUDE_DIR}/PluginEditor.h
#        ${INCLUDE_DIR}/PluginProcessor.h
#)

#target_include_directories(${PROJECT_NAME}
#    PUBLIC
#        ${CMAKE_CURRENT_SOURCE_DIR}/include
#)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        juce::juce_audio_utils
        juce::juce_dsp
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# In Visual Studio this command provides a nice grouping of source files in "filters".
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/..)
