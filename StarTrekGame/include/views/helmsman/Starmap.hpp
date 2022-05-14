#ifndef STARMAP_HPP
#define STARMAP_HPP

#include "../../framework/Clickables.hpp"
#include "../../framework/Component.hpp"
#include "../../framework/GameSprite.hpp"

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

    using starmapbutton_ptr = std::unique_ptr<ToggleButton>;
    std::vector<starmapbutton_ptr> _starmapButtons;
};

#endif
