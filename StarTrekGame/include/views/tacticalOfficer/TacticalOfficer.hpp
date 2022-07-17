#ifndef TACTICALOFFICER_HPP
#define TACTICALOFFICER_HPP

#include "../../framework/Clickables.hpp"
#include "../../framework/Component.hpp"
#include "../../framework/GameSprite.hpp"

namespace views
{
class TacticalOfficer final : public Component
{
  public:
    TacticalOfficer(sf::RenderWindow &);

    void update() override;
    void draw() override;
    void resize(sf::Vector2u prevWindowSize, sf::Vector2u newWindowSize) override;

  private:
    GameSprite _panel;
    Clickable _returnButton;
};

} // namespace views
#endif
