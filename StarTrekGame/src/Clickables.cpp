#include "../include/Clickables.hpp"
#include "../include/utils/Time.hpp"

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
