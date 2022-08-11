#ifndef ATTACKPANEL_HPP
#define ATTACKPANEL_HPP

#include "../../Starship.hpp"
#include "../../framework/Component.hpp"
#include "../../framework/GameSprite.hpp"
#include "../../framework/gui/Clickables.hpp"

class AttackPanel final : public Component
{
    using enemybutton = ToggleButton;
    using enemybutton_ptr = std::unique_ptr<enemybutton>;

  public:
    AttackPanel(sf::RenderWindow &);

    void update() override;
    void draw() override;
    void resize(sf::Vector2u prevWindowSize, sf::Vector2u newWindowSize) override;

  protected:
    void generateEnemyButtons();

  private:
    GameSprite _enemyPanel;
    std::vector<enemybutton_ptr> _enemyButtons;
    SystemData _prevSystemData;
};

#endif
