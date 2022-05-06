#ifndef STARMAP_HPP
#define STARMAP_HPP

#include "../../Component.hpp"
#include "../../GameSprite.hpp"

class Starmap final : public Component
{
  public:
    Starmap(sf::RenderWindow &, const sf::Vector2f &pos = {});

    void update() override;
    void draw() override;

  private:
    static constexpr int _starmapWidth{1000};
    static constexpr int _starmapHeight{900};

    const GameSprite _galaxyBG;
};

#endif
