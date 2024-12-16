#pragma once

#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>
#include <vector>

struct Paintings {
  Paintings() = default;

  Paintings(auto width) {
    setBounds(width);
  }

  void setBounds(auto width) {
    image = juce::Image(juce::Image::PixelFormat::ARGB, width, width, true);
  }

  void draw(juce::Graphics& g) {
      g.drawImage(image, image.getBounds().toFloat());
  }

  void draw(juce::Graphics& g, juce::Rectangle<float> bounds, int rp = juce::RectanglePlacement::stretchToFit, bool fillAlphaWithCurrentBrush = false) {
    g.drawImage(image, bounds, rp, fillAlphaWithCurrentBrush);
  }

  juce::Image image;
  juce::Random random;
};

class Spirograph : public Paintings {
public:
  void setImage(int arms = 27, int edges = 2056, float spirograph = 8.f, float scale = .9f, float spirographThickness = 3.f, float loopLength = 1.f,
    juce::Colour spirographColour = juce::Colours::yellow.withAlpha(.5f), juce::Colour armsColour = juce::Colours::limegreen.withAlpha(.5f)) {
    juce::Graphics g{ image };
    g.setColour(armsColour);

    auto centreX = float(image.getWidth()) * 0.5f;
    auto centreY = float(image.getHeight()) * 0.5f;
    auto minDimension = float(juce::jmin(image.getWidth(), image.getHeight()));
    auto radius = minDimension * .5f;
    auto armLength = radius / float(arms) * scale;
    std::vector<juce::Line<float>> armVec;
    armVec.resize(arms);
    juce::Path path;
    auto pathAlreadyStarted = false;
    auto points = float(edges);
    auto angle = 0.f;
    auto angleInc = juce::MathConstants<float>::twoPi / points;
    points *= loopLength;
    for (int p = 0; p < points; p++) {
      for (int a = 0; a < arms; a++) {
        armVec[a] = juce::Line<float>(0.f, 0.f, 0.f, armLength);
        auto rotation = juce::AffineTransform::rotation(float(a) * spirograph * angle + angle);
        armVec[a].applyTransform(rotation);
        if (a == 0) {
          auto translate = juce::AffineTransform::translation(centreX, centreY);
          armVec[a].applyTransform(translate);
        } else {
          auto endX = armVec[a - 1].getEndX();
          auto endY = armVec[a - 1].getEndY();
          auto translate = juce::AffineTransform::translation(endX, endY);
          armVec[a].applyTransform(translate);
        }
        g.drawLine(armVec[a], 1.f);
      }
      if (pathAlreadyStarted) {
        path.lineTo(armVec[armVec.size() - 1].getEnd());
      } else {
        path.startNewSubPath(armVec[armVec.size() - 1].getEnd());
        pathAlreadyStarted = true;
      }
      angle += angleInc;
    }
    if (std::fmodf(loopLength, 1.f) == 0.f && std::fmodf(spirograph, 1.f) == 0)
      path.closeSubPath();
    g.setColour(spirographColour);
    g.strokePath(path, juce::PathStrokeType(spirographThickness));
  }
};