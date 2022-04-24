#ifndef Clickable_HPP
#define Clickable_HPP

#include "Component.hpp"
#include "GameSprite.hpp"
#include <functional>

class Clickable : public GameSprite, public Component
{
  public:
    Clickable() = delete;
    Clickable(sf::RenderWindow &window) : Component(window)
    {
        setOutlineThickness(hitboxOutlineThickness);
        setOutlineColor(sf::Color::Transparent);
    }

    void setEvent(std::function<void(void)> event)
    {
        _event = std::move(event);
    }

    void setHitbox(const sf::Vector2f &pos, const sf::Vector2f &size)
    {
        _hitbox = std::make_unique<sf::RectangleShape>(size);
        _hitbox->setPosition(pos);
        _hitbox->setOutlineColor(sf::Color::Red);
        _hitbox->setOutlineThickness(hitboxOutlineThickness);
        _hitbox->setFillColor(sf::Color::Transparent);
    }

    void update() override
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

    void draw() override
    {
        m_window.draw(*this);
        if (_hitbox)
            m_window.draw(*_hitbox);
    }

    using event_t = std::function<void(void)>;

  protected:
    std::unique_ptr<sf::RectangleShape> _hitbox; // nullptr (not initialized), means that texture = hitbox
    event_t _event;

    static constexpr int hitboxOutlineThickness = 3;
};

#endif
