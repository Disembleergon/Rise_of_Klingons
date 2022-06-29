#include "../../include/framework/Slider.hpp"
#include "../../include/Game.hpp" // for PREFERRED_WINDOW_[...]

Slider::Slider(sf::RenderWindow &window, const SliderConfig &&config)
    : Component(window), _knob{window}, _trail{config.trailTexture},
      _relTrailPos{config.trailPos.x / PREFERRED_WINDOW_WIDTH, config.trailPos.y / PREFERRED_WINDOW_HEIGHT},
      _relTrailSize{config.trailSize.x / PREFERRED_WINDOW_WIDTH, config.trailSize.y / PREFERRED_WINDOW_HEIGHT},
      _relKnobSize{config.knobSize.x / PREFERRED_WINDOW_WIDTH, config.knobSize.y / PREFERRED_WINDOW_HEIGHT}
{
    _knob.setNewTexture(config.knobTexture);
    resize(m_window.getSize(), m_window.getSize());
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

void Slider::resize(sf::Vector2u prevWindowSize, sf::Vector2u newWindowSize)
{
    _knob.setSize({_relKnobSize.x * newWindowSize.x, _relKnobSize.y * newWindowSize.y});
    _knob.setOrigin({_knob.getSize().x * 0.5f, 0});

    const auto knobPos = _knob.getPosition();
    const sf::Vector2f relKnobPos{knobPos.x / prevWindowSize.x, knobPos.y / prevWindowSize.y};
    _knob.setPosition(relKnobPos.x * newWindowSize.x, relKnobPos.y * newWindowSize.y);

    _trail.setPosition(_relTrailPos.x * newWindowSize.x, _relTrailPos.y * newWindowSize.y);
    _trail.setSize({_relTrailSize.x * newWindowSize.x, _relTrailSize.y * newWindowSize.y});
}

void Slider::updateKnobPos()
{
    const auto trailPos = _trail.getPosition();
    const auto trailSize = _trail.getSize();
    const float knobY = trailPos.y + trailSize.y - _value * _trail.getSize().y - _knob.getSize().y * 0.5f;
    const float knobX = trailPos.x + trailSize.x * 0.5f; // centered on trail

    _knob.setPosition({knobX, knobY});
}
