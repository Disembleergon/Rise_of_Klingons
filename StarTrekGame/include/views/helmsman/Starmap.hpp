#ifndef STARMAP_HPP
#define STARMAP_HPP

#include "../../framework/Clickables.hpp"
#include "../../framework/Component.hpp"
#include "../../framework/GameSprite.hpp"
#include "../../framework/Slider.hpp"

class Starmap final : public Component
{
  public:
    Starmap(sf::RenderWindow &, const sf::Vector2f &pos = {});
    Starmap(const Starmap &) = delete;
    Starmap &operator=(const Starmap &) = delete;

    void update() override;
    void draw() override;

  protected:
    void generateButtons();

  private:
    static constexpr int _starmapWidth{1000};
    static constexpr int _starmapHeight{900};
    const GameSprite _galaxyBG;

    SliderConfig _warpsliderConfig{"./assets/controls/warpsliderTrail.png", // trail path
                                   {200, 300},                              // trail pos
                                   {250, 700},                              // trail size
                                   "./assets/controls/warpsliderKnob.png",  // knob path
                                   {350, 175}};                             // knob size
    Slider _warpslider;

    using starmapbutton_ptr = std::unique_ptr<ToggleButton>;
    std::vector<starmapbutton_ptr> _starmapButtons;
};

#endif
