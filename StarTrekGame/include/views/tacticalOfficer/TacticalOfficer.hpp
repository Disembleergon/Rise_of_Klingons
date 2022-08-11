#ifndef TACTICALOFFICER_HPP
#define TACTICALOFFICER_HPP

#include "../../framework/Component.hpp"
#include "../../framework/GameSprite.hpp"
#include "../../framework/gui/Clickables.hpp"
#include "AttackPanel.hpp"

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
    void resize(sf::Vector2u prevWindowSize, sf::Vector2u newWindowSize) override;

  private:
    GameSprite _panel;
    Clickable _returnButton;

    AttackPanel _attackPanel;
};

} // namespace views
#endif
