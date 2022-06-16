#ifndef STARMAP_HPP
#define STARMAP_HPP

#include "../../framework/Clickables.hpp"
#include "../../framework/Component.hpp"
#include "../../framework/GameSprite.hpp"
#include "../../framework/Slider.hpp"

class Starmap final : public Component
{
  public:
    Starmap(sf::RenderWindow &, Slider &throttleSider, const sf::Vector2f &pos = {});
    Starmap(const Starmap &) = delete;
    Starmap &operator=(const Starmap &) = delete;

    void update() override;
    void draw() override;

    void updateStarshipPosition();

  protected:
    Slider &_throttleSlider;

    sf::Vector2f getStarshipTargetPosition();
    void slowDownShip();

    void generateButtons();

  private:
    static constexpr int _starmapWidth{1000};
    static constexpr int _starmapHeight{900};
    const GameSprite _galaxyBG;

    static constexpr int SYSTEM_COUNT = 7;

    using starmapbutton_ptr = std::unique_ptr<ToggleButton>;
    std::vector<starmapbutton_ptr> _starmapButtons;
    ToggleButton *_currentSystemButton;

    GameSprite _starship;
};

#endif
