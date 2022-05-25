#ifndef BRIDGE_HPP
#define BRIDGE_HPP

#include "../../framework/Clickables.hpp"
#include "../../framework/Component.hpp"
#include "../../framework/GameSprite.hpp"
#include "GalaxyWindow.hpp"

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
    galaxywindow::GalaxyWindow _galaxyWindow;

    OutlineButton _helmsman;
    OutlineButton _tacticalOfficer;
};

} // namespace views
#endif
