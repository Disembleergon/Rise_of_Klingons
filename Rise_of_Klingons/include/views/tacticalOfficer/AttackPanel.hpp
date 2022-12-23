#ifndef ATTACKPANEL_HPP
#define ATTACKPANEL_HPP

#include "../../Starship.hpp"
#include "../../framework/Component.hpp"
#include "../../framework/GameSprite.hpp"
#include "../../framework/SoundSystem.hpp"
#include "../../framework/gui/Clickables.hpp"
#include "../../framework/gui/Progress.hpp"
#include "EnemyButton.hpp"

class AttackPanel final : public Component
{
  public:
    AttackPanel(sf::RenderWindow &);

    void update() override;
    void draw() override;
    void resize(const sf::Vector2u &prevWindowSize, const sf::Vector2u &newWindowSize) override;

    inline static EnemyButton *selectedEnemy{nullptr};

  protected:
    void generateEnemyButtons();
    void updateEnemyStatDisplays();
    void phaser();
    void torpedo();
    void killSelectedShip();

  private:
    GameSprite _enemyPanel;
    std::vector<EnemyButton::enemybutton_ptr> _enemyButtons;

    progress::ProgressBar _enemyShieldProgressbar;
    progress::ProgressBar _enemyHullProgressbar;
    float _prevShields{MAX_SHIELD};
    float _prevHull{MAX_HULL};

    progress::ProgressCircle _phaserProgressbar;
    progress::ProgressCircle _torpedoProgressbar;
    Starship::phaserAmmo_t _prevPhaserAmmo;   // used to decide whether to update the progressbars or not (if changed)
    Starship::torpedoAmmo_t _prevTorpedoAmmo; // ^

    Clickable _phaserShootButton;
    Clickable _torpedoShootButton;

    // when checking if thrust is >0, reset all values and progress bars and set this value to true
    bool _cleanupAlreadyHappened{false}; // (so nothing has to get updated every frame).
    SystemData _prevSystemData;          // to check if we arrived at new system

    bool _isShootingPhaser{false};
    float _phaserShootingProgress{0.0f}; // shows how long the phaser was active already

    bool _isShootingTorpedo{false};
    bool _torpedoWasReleased{false};
    float _torpedoShootingProgress{0.0f}; // ^

    std::unique_ptr<sf::SoundBuffer> _torpedoSoundBuffer;
    std::unique_ptr<sf::SoundBuffer> _phaserSoundBuffer;
    sf::Sound _phaserSound;
};

#endif
