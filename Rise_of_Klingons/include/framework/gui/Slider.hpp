#ifndef SLIDER_HPP
#define SLIDER_HPP

#include "../Component.hpp"
#include "../GameSprite.hpp"
#include "Clickables.hpp"

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
    void resize(const sf::Vector2u &prevWindowSize, const sf::Vector2u &newWindowSize) override;

    void updateKnobPos();

    void setValue(float val)
    {
        _value = val;
    }

    [[nodiscard]] inline float value() const
    {
        return _value;
    }

  private:
    float _value{0.0f};
    bool _dragging{false};

    // --- relative values, for resizing ---
    const sf::Vector2f _relTrailPos;
    const sf::Vector2f _relTrailSize;
    const sf::Vector2f _relKnobSize;

    GameSprite _trail;
    Clickable _knob;
};

#endif
