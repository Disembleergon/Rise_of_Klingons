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
    void resize(sf::Vector2u prevWindowSize, sf::Vector2u newWindowSize) override;

  private:
    GameSprite _bg;
    galaxywindow::GalaxyWindow _galaxyWindow;

    OutlineButton _helmsman;
    OutlineButton _tacticalOfficer;
};

} // namespace views
#endif
