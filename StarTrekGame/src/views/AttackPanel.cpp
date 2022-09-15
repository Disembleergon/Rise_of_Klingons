#include "../../include/views/tacticalOfficer/AttackPanel.hpp"
#include "../../include/Globals.hpp"
#include "../../include/framework/utils/Time.hpp"

#define PROGRESSBAR_SIZE 200u

AttackPanel::AttackPanel(sf::RenderWindow &window)
    : Component(window), _enemyPanel("./assets/textures/enemyOverviewPanel.png"),
      _phaserProgressbar(window, PROGRESSBAR_SIZE), _torpedoProgressbar(window, PROGRESSBAR_SIZE),
      _enemyShieldProgressbar(window), _enemyHullProgressbar(window), _phaserShootButton(window),
      _torpedoShootButton(window), _prevSystemData{*Starship::get().currentSystemData}
{
    // --- configure progress bars ---
    progress::Config progressCircleConfig{"Phaser", Globals::get().UI_BLUE,
                                          Globals::get().FONT}; // only the title changes
    _phaserProgressbar.configure(progressCircleConfig);
    progressCircleConfig.title = "Torpedo";
    _torpedoProgressbar.configure(progressCircleConfig);

    progress::Config enemyShieldConfig{"Shield", Globals::get().SHIELD_BLUE, Globals::get().FONT};
    _enemyShieldProgressbar.configure(enemyShieldConfig);

    progress::Config enemyHullConfig{"Hull", Globals::get().HULL_RED, Globals::get().FONT};
    _enemyHullProgressbar.configure(enemyHullConfig);

    // shoot buttons
    const sf::String btnImg = "./assets/textures/controls/shootButton.png";
    _phaserShootButton.setNewTexture(btnImg);
    _torpedoShootButton.setNewTexture(btnImg);

    resize(m_window.getSize(), m_window.getSize());
    generateEnemyButtons();
}

void AttackPanel::update()
{
    const auto currentThrust = Starship::get().thrust;
    if (currentThrust > 0 && !_cleanupAlreadyHappened) // no enemies when travelling
    {
        _enemyButtons.clear();
        _selectedEnemy = nullptr;
        updateEnemyStatDisplays();
        _cleanupAlreadyHappened = true;
    }

    // regenerate buttons on system arrival
    const SystemData *systemData = Starship::get().currentSystemData;
    if (*systemData != _prevSystemData)
    {
        _selectedEnemy = nullptr;
        generateEnemyButtons();
        updateEnemyStatDisplays();
        _prevSystemData = *systemData;
        _cleanupAlreadyHappened = false; // reset for next travel
    }

    const Starship::phaserAmmo_t currentPhaserAmmo = Starship::get().phaserAmmo;
    const Starship::torpedoAmmo_t currentTorpedoAmmo = Starship::get().torpedoAmmo;

    // update progressbars if values have changed
    if (_prevPhaserAmmo != currentPhaserAmmo)
    {
        _prevPhaserAmmo = currentPhaserAmmo;
        _phaserProgressbar.setPercentage(currentPhaserAmmo / MAX_PHASER_AMMO);
        _phaserProgressbar.update();
    }
    if (_prevTorpedoAmmo != currentTorpedoAmmo)
    {
        _prevTorpedoAmmo = currentTorpedoAmmo;
        _torpedoProgressbar.setPercentage(static_cast<float>(currentTorpedoAmmo) / MAX_TORPEDO_AMMO);
        _torpedoProgressbar.update();
    }
    //

    // update enemy buttons
    for (EnemyButton::enemybutton_ptr &btn : _enemyButtons)
    {
        btn->update();
        if (btn->clicked())
        {
            btn->setToggled(true);
            _selectedEnemy = btn.get();

            updateEnemyStatDisplays();

            // untoggle all buttons except the one that was clicked
            for (EnemyButton::enemybutton_ptr &b : _enemyButtons)
            {
                if (b == btn)
                    continue;
                b->setToggled(false);
            }
        }
        else
        {
            btn->toggledSinceCurrentClick = false;
        }
    }

    // update shooting buttons
    _phaserShootButton.update();
    if (_phaserShootButton.clicked())
        _isShootingPhaser = true;

    _torpedoShootButton.update();
    if (_torpedoShootButton.clicked())
        _isShootingTorpedo = true;

    if (_isShootingPhaser)
        phaser();

    if (_isShootingTorpedo)
        torpedo();
}

void AttackPanel::draw()
{
    m_window.draw(_enemyPanel);
    for (EnemyButton::enemybutton_ptr &enemyBtn : _enemyButtons)
        enemyBtn->draw();

    _phaserProgressbar.draw();
    _torpedoProgressbar.draw();
    _enemyShieldProgressbar.draw();
    _enemyHullProgressbar.draw();
    _phaserShootButton.draw();
    _torpedoShootButton.draw();
}

void AttackPanel::resize(sf::Vector2u prevWindowSize, sf::Vector2u newWindowSize)
{
    sf::Vector2f prevEnemyPanelPos = _enemyPanel.getPosition();
    sf::Vector2f prevEnemyPanelSize = _enemyPanel.getSize();

    _enemyPanel.setPosition(newWindowSize.x * 0.56f, newWindowSize.y * 0.12f);
    _enemyPanel.setSize({newWindowSize.x * 0.35f, newWindowSize.y * 0.24f});

    const sf::Vector2f newEnemyPanelPos = _enemyPanel.getPosition();
    const sf::Vector2f newEnemyPanelSize = _enemyPanel.getSize();

    // for resizing the progressbars at the beginning
    if (prevEnemyPanelSize == sf::Vector2f{0, 0})
    {
        prevEnemyPanelSize = newEnemyPanelSize;
        prevEnemyPanelPos = newEnemyPanelPos;
    }

    for (EnemyButton::enemybutton_ptr &btn : _enemyButtons)
    {
        const sf::Vector2f pos = btn->getPosition() - prevEnemyPanelPos;
        const sf::Vector2f relPos{pos.x / prevEnemyPanelSize.x, pos.y / prevEnemyPanelSize.y};
        btn->setPosition(newEnemyPanelPos.x + relPos.x * newEnemyPanelSize.x,
                         newEnemyPanelPos.y + relPos.y * newEnemyPanelSize.y);

        const sf::Vector2f size = btn->getSize();
        const sf::Vector2f relSize{size.x / prevEnemyPanelSize.x, size.y / prevEnemyPanelSize.y};
        btn->setSize({relSize.x * newEnemyPanelSize.x, relSize.y * newEnemyPanelSize.y});
    }

    _phaserProgressbar.setPos({newWindowSize.x * 0.645f, newWindowSize.y * 0.625f});
    _phaserProgressbar.resize(prevEnemyPanelSize.y, newEnemyPanelSize.y);
    _torpedoProgressbar.setPos({newWindowSize.x * 0.825f, newWindowSize.y * 0.625f});
    _torpedoProgressbar.resize(prevEnemyPanelSize.y, newEnemyPanelSize.y);

    _enemyShieldProgressbar.setPos({newWindowSize.x * 0.58f, newWindowSize.y * 0.4f});
    _enemyShieldProgressbar.setSize({newWindowSize.x * 0.14f, newWindowSize.y * 0.05f});
    _enemyHullProgressbar.setPos({newWindowSize.x * 0.75f, newWindowSize.y * 0.4f});
    _enemyHullProgressbar.setSize({newWindowSize.x * 0.14f, newWindowSize.y * 0.05f});

    _phaserShootButton.setPosition(newWindowSize.x * 0.597f, newWindowSize.y * 0.8f);
    _phaserShootButton.setSize({newWindowSize.x * 0.1f, newWindowSize.y * 0.05f});
    _torpedoShootButton.setPosition(newWindowSize.x * 0.778f, newWindowSize.y * 0.8f);
    _torpedoShootButton.setSize({newWindowSize.x * 0.1f, newWindowSize.y * 0.05f});
}

void AttackPanel::generateEnemyButtons()
{
    _enemyButtons.clear();

    resources::shared_texture_ptr untoggledTexture = std::make_shared<sf::Texture>();
    resources::loadResource<sf::Texture>(untoggledTexture.get(),
                                         "./assets/textures/controls/enemyButton_untoggled.png");

    resources::shared_texture_ptr toggledTexture = std::make_shared<sf::Texture>();
    resources::loadResource<sf::Texture>(toggledTexture.get(), "./assets/textures/controls/enemyButton_toggled.png");

    const auto enemyCount = Starship::get().currentSystemData->enemies.size();
    const auto SPACE_BETWEEN = _enemyPanel.getSize().x * 0.05f;
    const auto BUTTON_SIZE = _enemyPanel.getSize().x * 0.2f;
    const auto buttonAreaWidth = BUTTON_SIZE * enemyCount + SPACE_BETWEEN * (enemyCount - 1);
    const auto panelCenter = _enemyPanel.getPosition() + 0.5f * _enemyPanel.getSize();

    auto enemyIterator = Starship::get().currentSystemData->enemies.begin();
    for (int i = 0; i < enemyCount; ++i)
    {
        EnemyButton::enemybutton_ptr btn =
            std::make_unique<EnemyButton>(m_window, untoggledTexture, toggledTexture, *enemyIterator);
        std::advance(enemyIterator, 1);

        btn->setSize({BUTTON_SIZE, BUTTON_SIZE});
        btn->setPosition(panelCenter.x - buttonAreaWidth * 0.5f + i * (BUTTON_SIZE + SPACE_BETWEEN),
                         panelCenter.y - BUTTON_SIZE * 0.5f);

        _enemyButtons.push_back(std::move(btn));
    }
}

void AttackPanel::updateEnemyStatDisplays()
{
    // standard values if there's no ship selected
    float hull = 0.0f;
    float shield = 0.0f;

    if (_selectedEnemy)
    {
        hull = _selectedEnemy->data.hull;
        shield = _selectedEnemy->data.shield;
    }

    _enemyHullProgressbar.setPercentage(hull / MAX_HULL);
    _enemyHullProgressbar.update();
    _enemyShieldProgressbar.setPercentage(shield / MAX_SHIELD);
    _enemyShieldProgressbar.update();
}

void AttackPanel::phaser()
{
    if (_phaserShootingProgress > 2.5f || Starship::get().phaserAmmo <= 0.0f)
    {
        _isShootingPhaser = false;
        _phaserShootingProgress = 0.0f;
        return;
    }

    _phaserShootingProgress += Time::deltaTime;
    Starship::get().phaserAmmo -= Time::deltaTime;

    // no enemy selected
    if (!_selectedEnemy)
        return;

    static constexpr int SHIELD_DAMAGE = 8;
    static constexpr int HULL_DAMAGE = 3;

    if (_enemyShieldProgressbar.percentage() > 0.0f)
        _selectedEnemy->data.shield -= Time::deltaTime * SHIELD_DAMAGE;
    else if (_enemyHullProgressbar.percentage() > 0.0f)
        _selectedEnemy->data.hull -= Time::deltaTime * HULL_DAMAGE;

    if (_selectedEnemy->data.hull == 0.0f)
        killSelectedShip();

    updateEnemyStatDisplays();
}

void AttackPanel::torpedo()
{
    // after pressing the button, directly substract the used ammo
    if (!_torpedoWasReleased)
    {
        Starship::get().torpedoAmmo--;
        _torpedoWasReleased = true;
    }

    if (_torpedoShootingProgress > 4.0f || Starship::get().torpedoAmmo == 0)
    {
        // --- torpedo hit ---
        static constexpr int SHIELD_DAMAGE = 10;
        static constexpr int HULL_DAMAGE = 55;

        if (_enemyShieldProgressbar.percentage() > 0.0f)
            _selectedEnemy->data.shield = std::max(0.0f, _selectedEnemy->data.shield - SHIELD_DAMAGE);
        else if (_enemyHullProgressbar.percentage() > 0.0f)
            _selectedEnemy->data.hull = std::max(0.0f, _selectedEnemy->data.hull - HULL_DAMAGE);

        if (_selectedEnemy->data.hull == 0.0f)
            killSelectedShip();

        updateEnemyStatDisplays();

        // reset
        _isShootingTorpedo = false;
        _torpedoWasReleased = false;
        _torpedoShootingProgress = 0.0f;
        return;
    }

    _torpedoShootingProgress += Time::deltaTime;
}

void AttackPanel::killSelectedShip()
{
    // kill (remove) enemy ship
    auto &enemyVector = Starship::get().currentSystemData->enemies;
    auto isSelectedEnemy = std::remove(enemyVector.begin(), enemyVector.end(), _selectedEnemy->data);
    enemyVector.erase(isSelectedEnemy, enemyVector.end());

    _selectedEnemy = nullptr;
}
