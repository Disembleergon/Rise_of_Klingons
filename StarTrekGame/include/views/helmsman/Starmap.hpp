#ifndef STARMAP_HPP
#define STARMAP_HPP

#include "../../Starship.hpp"
#include "../../framework/Component.hpp"
#include "../../framework/GameSprite.hpp"
#include "../../framework/gui/Clickables.hpp"
#include "../../framework/gui/Slider.hpp"
#include "../../framework/utils/Random.hpp"
#include "../bridge/Bridge.hpp"

class Starmap final : public Component
{
    class StarmapButton final : public ToggleButton
    {
      public:
        StarmapButton(sf::RenderWindow &window, const resources::shared_texture_ptr &texture1,
                      const resources::shared_texture_ptr &texture2)
            : ToggleButton(window, texture1, texture2)
        {
            // fill enemy vector
            const int enemyCount = Random::generate_integral(0, 3);
            for (int i = 0; i < enemyCount; ++i)
                data.enemies.emplace_back(enemyIdCounter++);
        }

        using starmapbutton_ptr = std::unique_ptr<StarmapButton>;
        SystemData data;

      private:
        static unsigned int enemyIdCounter; // default = 0
    };

  public:
    Starmap(sf::RenderWindow &, views::Bridge &, Slider &throttleSider);
    Starmap(const Starmap &) = delete;
    Starmap &operator=(const Starmap &) = delete;

    void update() override;
    void draw() override;
    void resize(sf::Vector2u prevWindowSize, sf::Vector2u newWindowSize) override;

    void updateStarshipPosition();

  protected:
    Slider &_throttleSlider;
    views::Bridge &_bridge;

    sf::Vector2f getStarshipTargetPosition();
    void slowDownShip();

    void configureButtons(); // repositioning & resizing buttons (on window resize event)
    void generateSystems();

  private:
    float _starmapWidth;
    float _starmapHeight;
    GameSprite _galaxyBG;

    std::vector<StarmapButton::starmapbutton_ptr> _starmapButtons;
    StarmapButton *_currentSystemButton{};

    GameSprite _starship;
};

#endif
