#ifndef Clickable_HPP
#define Clickable_HPP

#include "../Component.hpp"
#include "../GameSprite.hpp"
#include "../utils/ResourceLoader.hpp"

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
class OutlineButton : public Clickable
{
  public:
    OutlineButton(sf::RenderWindow &);

  private:
    static constexpr int _outlineThickness = 3;

    void hoverAnimation(bool hover) override;
    float _outlineOpacity{0};
};

class ToggleButton : public OutlineButton
{
  public:
    ToggleButton(sf::RenderWindow &window, const resources::shared_texture_ptr &texture1,
                 const resources::shared_texture_ptr &texture2);

    void toggle();
    void setToggled(bool state);
    bool toggledSinceCurrentClick{false}; // take a look at toggle()

  private:
    const resources::shared_texture_ptr _texture1;
    const resources::shared_texture_ptr _texture2;
    bool _toggled{false};
};

#endif
