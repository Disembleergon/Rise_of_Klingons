#ifndef BRIDGE_HPP
#define BRIDGE_HPP

#include "../Button.hpp"
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
    Button _helmsman;
};

#endif
