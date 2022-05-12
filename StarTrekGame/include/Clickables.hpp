#ifndef Clickable_HPP
#define Clickable_HPP

#include "Component.hpp"
#include "GameSprite.hpp"

class Clickable : public GameSprite, public Component
{
  public:
    Clickable() = delete;
    Clickable(sf::RenderWindow &window);

    bool clicked() const
    {
        return _clicked;
    }

    void update() override;
    void draw() override;

  protected:
    bool _clicked{false};
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
