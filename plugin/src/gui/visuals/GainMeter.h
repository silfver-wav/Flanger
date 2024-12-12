#pragma once

#include "Spirograph.h"

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>

class GainMeter{
public:
  GainMeter() : m_magnitude(0.f), m_gain(0.f), m_release(.2f), m_imageIdx(0),
  m_imageIdxCache(0), m_ImagesMax(0), m_ImagesMaxInv(0.f), m_isReady(false) {}

  void initImages(int count, int bounds) {
    m_ImagesMax = count - 1;
    m_ImagesMaxInv = 1.f / float(m_ImagesMax);
    m_images.resize(count);

    for (auto& i : m_images){
      i = juce::Image(juce::Image::ARGB, bounds, bounds, true);
    }
  }

  void setRelease(float release) {
    m_release = release;
  }

  void setBuffer(juce::AudioBuffer<float>& buffer, int skipSamples = 0) {
    if (buffer.getNumChannels() == 0 || buffer.getNumSamples() == 0) return;

    m_magnitude = 0.f;

    for (auto ch = 0; ch < buffer.getNumChannels(); ++ch) {
      auto magnitude = buffer.getMagnitude(ch,m_magnitude, buffer.getNumSamples());
      if (magnitude > m_magnitude)
        m_magnitude = magnitude;
    }

    if (m_gain < m_magnitude)
      m_gain = m_magnitude;
    else
      m_gain = m_gain + m_release * (m_magnitude - m_gain);

    m_imageIdx = juce::jlimit(0, m_ImagesMax, int(m_gain * m_ImagesMax));
  }

  void draw(juce::Graphics & graphics, juce::Rectangle<float> bounds) {
    m_imageIdx = m_imageIdx < m_images.size() ? m_imageIdx : m_ImagesMax;
    if (m_imageIdx >= 0 && m_imageIdx < m_images.size() && m_isReady)
      graphics.drawImage(m_images[m_imageIdx], bounds);
  }

  bool shouldRepaint() {
    if (m_imageIdxCache == m_imageIdx) {
      return false;
    }
    m_imageIdxCache = m_imageIdx;
    return true;
  }

private:
  float m_magnitude, m_gain, m_release, m_imageIdx, m_imageIdxCache;
protected:
  int m_ImagesMax;
  float m_ImagesMaxInv;
  bool m_isReady;
  std::vector<juce::Image> m_images;
};

class GainMeterSpirograph : public GainMeter {
public:
  struct ImageOptions {
    int armsStart, armsEnd;
    int edgesStart, edgesEnd;
    float twistsStart, twistEnd;
    float scaleStart, scaleEnd;
    float thicknessStart, thicknessEnd;
    juce::Colour spiroColourStart, spiroColourEnd;
    juce::Colour armsColourStart, armsColourEnd;
  };

  void setImages(const ImageOptions& opts)
  {
    if (m_images.empty()) {
      DBG("Images not initialized!");
      return;
    }

    Spirograph spirograph(m_images[0].getWidth());
    for (auto i = 0; i < m_images.size(); ++i) {
      m_iRel = float(i) * m_ImagesMaxInv;

      auto arms = int(opts.armsStart + m_iRel * (opts.armsEnd - opts.armsStart));
      auto edges = int(opts.edgesStart + m_iRel * (opts.edgesEnd - opts.edgesStart));
      auto twists = opts.twistsStart + m_iRel * (opts.twistEnd - opts.twistsStart);
      auto scale = opts.scaleStart + m_iRel * (opts.scaleEnd - opts.scaleStart);
      auto thickness = opts.thicknessStart + m_iRel * (opts.thicknessEnd - opts.thicknessStart);
      auto spirographColour = opts.spiroColourStart.interpolatedWith(opts.spiroColourEnd, m_iRel);
      auto armsColour = opts.armsColourStart.interpolatedWith(opts.armsColourEnd, m_iRel);

      spirograph.setImage(arms, edges, twists, scale, thickness, 1.f, spirographColour, armsColour);

      juce::Graphics g(m_images[i]);
      g.drawImageAt(spirograph.image, 0, 0);
    }
    m_isReady = true;
  }
private:
  float m_iRel = 0.f;
};