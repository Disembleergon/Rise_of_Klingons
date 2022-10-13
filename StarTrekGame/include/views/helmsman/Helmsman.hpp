#ifndef HELMSMAN_HPP
#define HELMSMAN_HPP

#include "../../framework/Component.hpp"
#include "../../framework/GameSprite.hpp"
#include "../../framework/gui/Clickables.hpp"
#include "../../framework/gui/Slider.hpp"
#include "Starmap.hpp"

namespace views
{

class Helmsman final : public Component
{
  public:
    Helmsman(sf::RenderWindow &, Bridge &);

    void update() override;
    void draw() override;
    void resize(const sf::Vector2u &prevWindowSize, const sf::Vector2u &newWindowSize) override;

    [[nodiscard]] Starmap &starmap()
    {
        return _starmap;
    }

  private:
    GameSprite _panel;
    Clickable _returnButton;
    Starmap _starmap;

    SliderConfig _warpsliderConfig{"./assets/textures/controls/warpsliderTrail.png", // trail path
                                   {200, 300},                                       // trail pos
                                   {250, 700},                                       // trail size
                                   "./assets/textures/controls/warpsliderKnob.png",  // knob path
                                   {350, 175}};                                      // knob size
    Slider _warpslider;
};

} // namespace views

#endif
