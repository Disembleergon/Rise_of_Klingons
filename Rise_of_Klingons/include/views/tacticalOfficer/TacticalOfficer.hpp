#ifndef TACTICALOFFICER_HPP
#define TACTICALOFFICER_HPP

#include "../../framework/Component.hpp"
#include "../../framework/GameSprite.hpp"
#include "../../framework/gui/Clickables.hpp"
#include "AttackPanel.hpp"
#include "ContactPanel.hpp"
#include <memory>

namespace views
{
class TacticalOfficer final : public Component
{
    using enemybutton = ToggleButton;
    using enemybutton_ptr = std::unique_ptr<enemybutton>;

  public:
    TacticalOfficer(sf::RenderWindow &);

    void update() override;
    void draw() override;
    void resize(const sf::Vector2u &prevWindowSize, const sf::Vector2u &newWindowSize) override;

  private:
    GameSprite _panel;
    Clickable _returnButton;

    progress::ProgressCircle _starshipHullDisplay;
    progress::ProgressCircle _starshipShieldDisplay;
    float _prevStarshipHull;   // used to update the displays when health changed (comparision)
    float _prevStarshipShield; // ^

    AttackPanel _attackPanel;
    ContactPanel _contactPanel;
};

} // namespace views
#endif
