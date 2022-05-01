#ifndef Clickable_HPP
#define Clickable_HPP

#include "Component.hpp"
#include "GameSprite.hpp"
#include <functional>

// abstract
class Clickable : public GameSprite, public Component
{
  public:
    using event_t = std::function<void(void)>;

    Clickable() = delete;
    Clickable(sf::RenderWindow &window, event_t event);

    virtual void setHitbox(const sf::Vector2f &pos, const sf::Vector2f &size) = 0;
    void update() override;
    void draw() override;

  protected:
    std::unique_ptr<sf::RectangleShape> _hitbox; // nullptr (not initialized), means that texture = hitbox
    event_t _event;

    virtual void hoverAnimation(bool hover) = 0;
};

// outline on hover
class OutlineButton final : public Clickable
{
  public:
    OutlineButton(sf::RenderWindow &, event_t event);
    void setHitbox(const sf::Vector2f &pos, const sf::Vector2f &size) override;

  private:
    static constexpr int hitboxOutlineThickness = 3;

    void hoverAnimation(bool hover) override;
    float _hitboxOpacity{0};
};

#endif
