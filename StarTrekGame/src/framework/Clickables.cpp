#include "../../include/framework/Clickables.hpp"
#include "../../include/framework/utils/Time.hpp"

// ----- clickable -----

Clickable::Clickable(sf::RenderWindow &window) : Component(window)
{
}

void Clickable::update()
{
    if (getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window))))
    {
        _clicked = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        hoverAnimation(true);
    }
    else
    {
        hoverAnimation(false);
        _clicked = false;
    }
}

void Clickable::draw()
{
    m_window.draw(*this);
}

// ----- outline button -----

OutlineButton::OutlineButton(sf::RenderWindow &window) : Clickable(window)
{
    setOutlineThickness(_outlineThickness);
    setOutlineColor(sf::Color::Transparent);
}

void OutlineButton::hoverAnimation(bool hover)
{
    const sf::Color outlineClr{247, 216, 37, static_cast<sf::Uint8>(_outlineOpacity)};
    setOutlineColor(outlineClr);

    static constexpr int animationDuration = 800;

    if (hover) // fade in
    {
        _outlineOpacity = std::min(255.0f, _outlineOpacity + animationDuration * Time::deltaTime);
    }
    else // fade out
    {
        _outlineOpacity = std::max(0.0f, _outlineOpacity - animationDuration * Time::deltaTime);
    }
}

// ----- toggle button -----

ToggleButton::ToggleButton(sf::RenderWindow &window, const TextureLoader::texture_ptr &texture1,
                           const TextureLoader::texture_ptr &texture2)
    : OutlineButton(window), _texture1{texture1}, _texture2{texture2}
{
    setTexture(_texture1.get());
}

void ToggleButton::toggle()
{
    setToggled(!_toggled);
}

void ToggleButton::setToggled(bool state)
{
    if (toggledSinceCurrentClick) // only toggle on second click (one click =
        return;                   // holding down mouse button -> flashy)

    toggledSinceCurrentClick = true;
    _toggled = state;
    setTexture(_toggled ? _texture2.get() : _texture1.get());
}
