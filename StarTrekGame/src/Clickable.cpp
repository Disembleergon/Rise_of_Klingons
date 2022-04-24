#include "../include/Clickable.hpp"

Clickable::Clickable(sf::RenderWindow &window) : Component(window)
{
    setOutlineThickness(hitboxOutlineThickness);
    setOutlineColor(sf::Color::Transparent);
}

void Clickable::setHitbox(const sf::Vector2f &pos, const sf::Vector2f &size)
{
    _hitbox = std::make_unique<sf::RectangleShape>(size);
    _hitbox->setPosition(pos);
    _hitbox->setOutlineColor(sf::Color::Red);
    _hitbox->setOutlineThickness(hitboxOutlineThickness);
    _hitbox->setFillColor(sf::Color::Transparent);
}

void Clickable::update()
{
    bool textureIsHitbox = (_hitbox == nullptr);
    sf::RectangleShape *hitbox = textureIsHitbox ? this : _hitbox.get();

    if (hitbox->getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window))))
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            _event();

        hitbox->setOutlineColor(sf::Color::Yellow);
        return;
    }

    hitbox->setOutlineColor(sf::Color::Transparent);
}

void Clickable::draw()
{
    m_window.draw(*this);
    if (_hitbox)
        m_window.draw(*_hitbox);
}
