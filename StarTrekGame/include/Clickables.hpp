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

    void update() override;
    void draw() override;

  protected:
    event_t _event;
    virtual void hoverAnimation(bool hover) = 0;
};

// outline on hover
class OutlineButton final : public Clickable
{
  public:
    OutlineButton(sf::RenderWindow &, event_t event);

  private:
    static constexpr int _outlineThickness = 3;

    void hoverAnimation(bool hover) override;
    float _outlineOpacity{0};
};

#endif
