#ifndef BRIDGE_HPP
#define BRIDGE_HPP

#include "../Clickables.hpp"
#include "../Component.hpp"
#include "../GameSprite.hpp"

namespace views
{
class Bridge final : public Component
{
  public:
    Bridge(sf::RenderWindow &window);
    void update() override;
    void draw() override;

  private:
    const GameSprite _bg;
    OutlineButton _helmsman;
    OutlineButton _tacticalOfficer;
};

} // namespace views
#endif
