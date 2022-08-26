#ifndef ATTACKPANEL_HPP
#define ATTACKPANEL_HPP

#include "../../Starship.hpp"
#include "../../framework/Component.hpp"
#include "../../framework/GameSprite.hpp"
#include "../../framework/gui/Clickables.hpp"
#include "../../framework/gui/Progress.hpp"

class AttackPanel final : public Component
{
    class EnemyButton final : public ToggleButton
    {
      public:
        EnemyButton(sf::RenderWindow &window, const resources::shared_texture_ptr &texture1,
                    const resources::shared_texture_ptr &texture2, unsigned int index)
            : ToggleButton(window, texture1, texture2), data{Starship::get().currentSystemData->enemies[index]}
        {
        }

        EnemyData &data; // modify enemy data value of current system data (stored in current selected StarmapButton)
        using enemybutton_ptr = std::unique_ptr<EnemyButton>;
    };

  public:
    AttackPanel(sf::RenderWindow &);

    void update() override;
    void draw() override;
    void resize(sf::Vector2u prevWindowSize, sf::Vector2u newWindowSize) override;

  protected:
    void generateEnemyButtons();

  private:
    GameSprite _enemyPanel;
    std::vector<EnemyButton::enemybutton_ptr> _enemyButtons;

    progress::ProgressBar _enemyShieldProgressbar;
    progress::ProgressBar _enemyHullProgressbar;

    progress::ProgressCircle _phaserProgressbar;
    progress::ProgressCircle _torpedoProgressbar;
    Starship::phaserAmmo_t _prevPhaserAmmo;   // used to decide whether to update the progressbars or not (if changed)
    Starship::torpedoAmmo_t _prevTorpedoAmmo; // ^

    Clickable _phaserShootButton;
    Clickable _torpedoShootButton;
};

#endif
