#ifndef Clickable_HPP
#define Clickable_HPP

#include "Component.hpp"
#include "GameSprite.hpp"
#include <functional>

class Clickable : public GameSprite, public Component
{
  public:
    Clickable() = delete;
    Clickable(sf::RenderWindow &window);

    void setEvent(std::function<void(void)> event)
    {
        _event = std::move(event);
    }

    void setHitbox(const sf::Vector2f &pos, const sf::Vector2f &size);
    void update() override;
    void draw() override;

    using event_t = std::function<void(void)>;

  protected:
    std::unique_ptr<sf::RectangleShape> _hitbox; // nullptr (not initialized), means that texture = hitbox
    event_t _event;

    static constexpr int hitboxOutlineThickness = 3;
};

#endif
