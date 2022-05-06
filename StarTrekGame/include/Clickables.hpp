#ifndef Clickable_HPP
#define Clickable_HPP

#include "Component.hpp"
#include "GameSprite.hpp"
#include <functional>

class Clickable : public GameSprite, public Component
{
  public:
    using event_t = std::function<void(void)>;

    Clickable() = delete;
    Clickable(sf::RenderWindow &window);

    void setClickEvent(std::function<void(void)>);

    void update() override;
    void draw() override;

  protected:
    event_t _event;
    virtual void hoverAnimation(bool hover){
        // EMPTY
    };
};

// outline on hover
class OutlineButton final : public Clickable
{
  public:
    OutlineButton(sf::RenderWindow &);

  private:
    static constexpr int _outlineThickness = 3;

    void hoverAnimation(bool hover) override;
    float _outlineOpacity{0};
};

#endif
