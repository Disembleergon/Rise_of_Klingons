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

    [[nodiscard]] bool clicked() const
    {
        return _clicked;
    }

    [[nodiscard]] bool held() const
    {
        return _stillClicking;
    }

    void update() override;
    void draw() override;

  protected:
    bool _clicked{false};
    bool _stillClicking{false};

    virtual void hoverAnimation(bool hover){
        // EMPTY
    };
};

class TitledClickable : public Clickable
{
  public:
    struct Config
    {
        sf::String title;
        sf::Color color;
        resources::shared_font_ptr font;
    };

    TitledClickable(sf::RenderWindow &);
    void configure(const Config &);

    void draw() override;
    void resize(const sf::Vector2u &prevWindowSize, const sf::Vector2u &newWindowSize) override;

  private:
    resources::shared_font_ptr _font;
    sf::Text _title;
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

  private:
    const resources::shared_texture_ptr _texture1;
    const resources::shared_texture_ptr _texture2;
    bool _toggled{false};
};

#endif
