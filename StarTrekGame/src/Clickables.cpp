#include "../include/Clickables.hpp"
#include "../include/utils/Time.hpp"

// ----- clickable -----

Clickable::Clickable(sf::RenderWindow &window, event_t event) : Component(window), _event{event}
{
}

void Clickable::update()
{
    // hitbox = entire texture, if hitbox not defined
    bool textureIsHitbox = (_hitbox == nullptr);
    sf::RectangleShape *hitbox = textureIsHitbox ? this : _hitbox.get();

    if (hitbox->getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window))))
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            _event();

        hoverAnimation(true);
    }
    else
        hoverAnimation(false);
}

void Clickable::draw()
{
    m_window.draw(*this);
    if (_hitbox)
        m_window.draw(*_hitbox);
}

// ----- outline button -----

OutlineButton::OutlineButton(sf::RenderWindow &window, event_t event) : Clickable(window, event)
{
    setOutlineThickness(hitboxOutlineThickness);
    setOutlineColor(sf::Color::Transparent);
}

void OutlineButton::setHitbox(const sf::Vector2f &pos, const sf::Vector2f &size)
{
    _hitbox = std::make_unique<sf::RectangleShape>(size);
    _hitbox->setPosition(pos);
    _hitbox->setOutlineThickness(hitboxOutlineThickness);
    _hitbox->setFillColor(sf::Color::Transparent);
}

void OutlineButton::hoverAnimation(bool hover)
{
    // hitbox = entire texture, if hitbox not defined
    bool textureIsHitbox = (_hitbox == nullptr);
    sf::RectangleShape *hitbox = textureIsHitbox ? this : _hitbox.get();

    const sf::Color outlineClr{247, 216, 37, static_cast<sf::Uint8>(_hitboxOpacity)};
    hitbox->setOutlineColor(outlineClr);

    static constexpr int animationDuration = 800;

    if (hover) // fade in
    {
        _hitboxOpacity = std::min(255.0f, _hitboxOpacity + animationDuration * Time::deltaTime);
    }
    else // fade out
    {
        _hitboxOpacity = std::max(0.0f, _hitboxOpacity - animationDuration * Time::deltaTime);
    }
}
