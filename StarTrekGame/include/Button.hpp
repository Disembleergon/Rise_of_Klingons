#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "GameScript.hpp"
#include "GameSprite.hpp"
#include <functional>
#include <optional>

#define SHOWHITBOXES

class Button : public GameSprite, public GameScript
{
  public:
    Button() = delete;
    Button(sf::RenderWindow &window) : GameScript(window)
    {
    }

    void setEvent(std::function<void(void)> event)
    {
        _event = std::move(event);
    }

    void setHitbox(const sf::Vector2f &pos, const sf::Vector2f &size)
    {
        _hitbox = sf::RectangleShape{size};
        _hitbox.value().setPosition(pos);
        _hitbox.value().setOutlineColor(sf::Color::Red); // only visited if #define SHOWHITBOXES
        _hitbox.value().setOutlineThickness(10);
        _hitbox.value().setFillColor(sf::Color::Transparent);
    }

    void update() override
    {
        const auto hitBox = _hitbox.value_or(*this);
        sf::Cursor cursor;

        if (hitBox.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window))))
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                _event();

            cursor.loadFromSystem(sf::Cursor::Type::Hand);
            m_window.setMouseCursor(cursor);
        }
        else
        {
            cursor.loadFromSystem(sf::Cursor::Type::Arrow);
            m_window.setMouseCursor(cursor);
        }
    }

    void draw() override
    {
        m_window.draw(*this);

#ifdef SHOWHITBOXES
        if (_hitbox.has_value())
            m_window.draw(_hitbox.value());
#endif
    }

    using event_t = std::function<void(void)>;

  protected:
    std::optional<sf::RectangleShape> _hitbox;
    event_t _event;
};

#endif
