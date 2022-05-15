#ifndef SLIDER_HPP
#define SLIDER_HPP

#include "Clickables.hpp"
#include "Component.hpp"
#include "GameSprite.hpp"

struct SliderConfig
{
    sf::String trailTexture;
    sf::Vector2f trailPos;
    sf::Vector2f trailSize;

    sf::String knobTexture;
    sf::Vector2f knobSize;
};

class Slider : public Component
{
  public:
    Slider(sf::RenderWindow &, const SliderConfig &&);

    void update() override;
    void draw() override;

    void updateKnobPos();

    inline float value() const
    {
        return _value;
    }

  private:
    float _value{0.0f};
    bool _dragging{false};

    const GameSprite _trail;
    Clickable _knob;
};

#endif
