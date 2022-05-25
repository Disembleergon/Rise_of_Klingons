#ifndef HELMSMAN_HPP
#define HELMSMAN_HPP

#include "../../framework/Clickables.hpp"
#include "../../framework/Component.hpp"
#include "../../framework/GameSprite.hpp"
#include "../../framework/Slider.hpp"
#include "Starmap.hpp"

namespace views
{

class Helmsman final : public Component
{
  public:
    Helmsman(sf::RenderWindow &);

    void update() override;
    void draw() override;

  private:
    const GameSprite _panel;
    Clickable _returnButton;
    Starmap _starmap;

    SliderConfig _warpsliderConfig{"./assets/controls/warpsliderTrail.png", // trail path
                                   {200, 300},                              // trail pos
                                   {250, 700},                              // trail size
                                   "./assets/controls/warpsliderKnob.png",  // knob path
                                   {350, 175}};                             // knob size
    Slider _warpslider;
};

} // namespace views

#endif
