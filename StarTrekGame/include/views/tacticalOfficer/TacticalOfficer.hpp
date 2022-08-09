#ifndef TACTICALOFFICER_HPP
#define TACTICALOFFICER_HPP

#include "../../framework/gui/Clickables.hpp"
#include "../../framework/Component.hpp"
#include "../../framework/GameSprite.hpp"
#include "../../Starship.hpp"

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

  protected:
    void generateEnemyButtons();

  private:
    GameSprite _panel;
    Clickable _returnButton;

    GameSprite _enemyPanel;
    std::vector<enemybutton_ptr> _enemyButtons;
    SystemData _prevSystemData;
};

} // namespace views
#endif
