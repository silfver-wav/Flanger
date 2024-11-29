#pragma once

#include "Spirograph.h"

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>

class GainMeter{
public:
  GainMeter() : m_magnitude(0.f), m_gain(0.f), m_release(.2f), m_imageIdx(0),
  m_imageIdxCache(0), m_ImagesMax(0), m_ImagesMaxInv(0.f), m_isReady(false) {}

  void setImagesCount(int count) {
    m_ImagesMax = count - 1;
    m_ImagesMaxInv = 1.f / float(m_ImagesMax);
    m_images.resize(count);
  }

  void setImagesBounds(int imageWidth){
    for (auto& i : m_images){
      i = juce::Image(juce::Image::ARGB, imageWidth, imageWidth, true);
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

    m_imageIdx = int(m_gain * m_ImagesMax);
  }

  void draw(juce::Graphics & graphics, juce::Rectangle<float> bounds) {
    m_imageIdx = m_imageIdx < m_images.size() ? m_imageIdx : m_ImagesMax;
    if (m_isReady)
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
  void setImages(int armsStart, int armsEnd, int edgesStart, int edgesEnd, float twistsStart, float twistEnd, float scaleStart, float scaleEnd, float thicnessStart, float thicnessEnd, juce::Colour spiroColourStart, juce::Colour spiroColourEnd, juce::Colour armsColourStart, juce::Colour armsColourEnd) {
    if (m_images.empty()) {
      DBG("Images not initialized!");
      return;
    }

    for (auto i = 0; i < m_images.size(); ++i) {
      m_iRel = float(i) * m_ImagesMaxInv;

      auto arms = int(armsStart + m_iRel * (armsEnd - armsStart));
      auto edges = int(edgesStart + m_iRel * (edgesEnd - edgesStart));
      auto twists = twistsStart + m_iRel * (twistEnd - twistsStart);
      auto scale = scaleStart + m_iRel * (scaleEnd - scaleStart);
      auto thicness = thicnessStart + m_iRel * (thicnessEnd - thicnessStart);
      auto spirographColour = spiroColourStart.interpolatedWith(spiroColourEnd, m_iRel);
      auto armsColour = armsColourStart.interpolatedWith(armsColourEnd, m_iRel);
      auto width = m_images[i].getWidth();
      if (width <= 0) width = 100;

      Spirograph spirograph(width);
      spirograph.setImage(arms, edges, twists, scale, thicness, 1.f, spirographColour, armsColour);

      if (m_images[i].getWidth() != spirograph.image.getWidth() ||
          m_images[i].getHeight() != spirograph.image.getHeight()) {
        DBG("Dimension mismatch between m_images[" << i << "] and spirograph.image!");
        continue;
      }

      juce::Graphics g(m_images[i]);
      g.drawImageAt(spirograph.image, 0, 0);
    }
    m_isReady = true;
  }
private:
  float m_iRel = 0.f;
};

class Light : public GainMeter {
public:
  void setImages(juce::ColourGradient gradient) {
    if (m_images.empty()) {
      DBG("Images not initialized!");
      return;
    }

    DBG("Image width " << m_images[0].getWidth());

    for (auto i = 0; i < m_images.size(); ++i) {
      if (m_images[i].getWidth() == 0) {
        DBG("Image " << i << " has invalid size!");
        continue;
      }
      auto iF = float(i);
      auto iRel = iF * m_ImagesMaxInv;

      auto width = m_images[i].getWidth();
      if (width <= 0) width = 100;
      Spirograph spirograph(width);
      spirograph.setImage();

      for (auto y = 0; y < m_images[i].getHeight(); ++y)
        for (auto x = 0; x < m_images[i].getWidth(); ++x)
          m_images[i].setPixelAt(x, y, spirograph.image.getPixelAt(x, y));

    }
  }

};