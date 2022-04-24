#ifndef BRIDGE_HPP
#define BRIDGE_HPP

#include "../Clickable.hpp"
#include "../GameScript.hpp"
#include "../GameSprite.hpp"

class Bridge final : public GameScript
{
  public:
    Bridge(sf::RenderWindow &window);
    void update() override;
    void draw() override;

  private:
    const GameSprite _bg;
    Clickable _helmsman;
    Clickable _tacticalOfficer;
};

#endif
