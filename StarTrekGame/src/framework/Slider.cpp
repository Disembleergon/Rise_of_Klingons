#include "../../include/framework/Slider.hpp"

Slider::Slider(sf::RenderWindow &window, const SliderConfig &&config)
    : Component(window), _knob{window}, _trail{config.trailTexture, config.trailPos, config.trailSize}
{
    _knob.setNewTexture(config.knobTexture);
    _knob.setSize(config.knobSize);
    _knob.setOrigin({_knob.getSize().x / 2, 0});
    updateKnobPos();
}

void Slider::update()
{
    updateKnobPos();

    const auto mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window));
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        _dragging = false;
        return;
    }

    bool knobNotDragged = !_knob.getGlobalBounds().contains(mousePos) && !_dragging;
    if (knobNotDragged)
        return;

    _dragging = true;

    // mouse not hovering over slider -> out of bound
    if (!_trail.getGlobalBounds().contains(mousePos))
        return;

    const auto trailEndY = _trail.getPosition().y + _trail.getSize().y;
    const auto mouseYRelative = trailEndY - mousePos.y;
    _value = mouseYRelative / _trail.getSize().y;
}

void Slider::draw()
{
    m_window.draw(_trail);
    m_window.draw(_knob);
}

void Slider::updateKnobPos()
{
    const auto trailPos = _trail.getPosition();
    const auto trailSize = _trail.getSize();
    const float knobY = trailPos.y + trailSize.y - _value * _trail.getSize().y - _knob.getSize().y * 0.5f;
    const float knobX = trailPos.x + trailSize.x * 0.5f; // centered on trail

    _knob.setPosition({knobX, knobY});
}
