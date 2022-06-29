#ifndef STARMAP_HPP
#define STARMAP_HPP

#include "../../framework/Clickables.hpp"
#include "../../framework/Component.hpp"
#include "../../framework/GameSprite.hpp"
#include "../../framework/Slider.hpp"
#include <random>

class Starmap final : public Component
{
    using starmapbutton_ptr = std::unique_ptr<ToggleButton>;

  public:
    Starmap(sf::RenderWindow &, Slider &throttleSider);
    Starmap(const Starmap &) = delete;
    Starmap &operator=(const Starmap &) = delete;

    void update() override;
    void draw() override;
    void resize(sf::Vector2u prevWindowSize, sf::Vector2u newWindowSize) override;

    void updateStarshipPosition();

  protected:
    Slider &_throttleSlider;

    sf::Vector2f getStarshipTargetPosition();
    void slowDownShip();

    void configureButtons(); // repositioning & resizing buttons (on window resize event)
    void generateButtons();

  private:
    float _starmapWidth;
    float _starmapHeight;
    GameSprite _galaxyBG;

    static constexpr int SYSTEM_COUNT = 7;
    std::vector<starmapbutton_ptr> _starmapButtons;
    ToggleButton *_currentSystemButton{};

    GameSprite _starship;
};

#endif
