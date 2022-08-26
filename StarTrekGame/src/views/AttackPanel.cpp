#include "../../include/views/tacticalOfficer/AttackPanel.hpp"
#define PROGRESSBAR_SIZE 200u

AttackPanel::AttackPanel(sf::RenderWindow &window)
    : Component(window), _enemyPanel("./assets/textures/enemyOverviewPanel.png"),
      _phaserProgressbar(window, PROGRESSBAR_SIZE), _torpedoProgressbar(window, PROGRESSBAR_SIZE),
      _enemyShieldProgressbar(window), _enemyHullProgressbar(window), _phaserShootButton(window),
      _torpedoShootButton(window)
{
    resources::shared_font_ptr font = std::make_shared<sf::Font>();
    resources::loadResource<sf::Font>(font.get(), "./assets/fonts/PressStart2P-Regular.ttf");

    // --- configure progress bars ---
    progress::Config progressCircleConfig{"Phaser", sf::Color{48, 187, 242}, font}; // only the title changes
    _phaserProgressbar.configure(progressCircleConfig);
    progressCircleConfig.title = "Torpedo";
    _torpedoProgressbar.configure(progressCircleConfig);

    progress::Config enemyShieldConfig{"Shield", sf::Color{111, 210, 237}, font};
    _enemyShieldProgressbar.configure(enemyShieldConfig);

    progress::Config enemyHullConfig{"Hull", sf::Color{227, 93, 84}, font};
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
    if (currentThrust > 0) // no enemies when travelling
        _enemyButtons.clear();

    // regenerate buttons on system arrival
    const SystemData *systemData = Starship::get().currentSystemData;
    if (currentThrust == 0.0f && _enemyButtons.size() != systemData->enemies.size())
    {
        generateEnemyButtons();
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
        _torpedoProgressbar.setPercentage(currentTorpedoAmmo / MAX_TORPEDO_AMMO);
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

            // update with current enemy values
            _enemyHullProgressbar.setPercentage(btn->data.hull / MAX_HULL);
            _enemyHullProgressbar.update();
            _enemyShieldProgressbar.setPercentage(btn->data.shield / MAX_SHIELD);
            _enemyShieldProgressbar.update();

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

    for (int i = 0; i < enemyCount; ++i)
    {
        EnemyButton::enemybutton_ptr btn = std::make_unique<EnemyButton>(m_window, untoggledTexture, toggledTexture, i);
        btn->setSize({BUTTON_SIZE, BUTTON_SIZE});
        btn->setPosition(panelCenter.x - buttonAreaWidth * 0.5f + i * (BUTTON_SIZE + SPACE_BETWEEN),
                         panelCenter.y - BUTTON_SIZE * 0.5f);

        _enemyButtons.push_back(std::move(btn));
    }
}
