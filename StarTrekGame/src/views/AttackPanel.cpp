#include "../../include/views/tacticalOfficer/AttackPanel.hpp"
#define PROGRESSBAR_SIZE 200u

AttackPanel::AttackPanel(sf::RenderWindow &window)
    : Component(window),
      _enemyPanel("./assets/textures/enemyOverviewPanel.png"), _prevSystemData{Starship::get().currentSystemData},
      _phaserProgressbar(window, "Phaser", PROGRESSBAR_SIZE), _torpedoProgressbar(window, "Torpedo", PROGRESSBAR_SIZE)
{
    resources::shared_font_ptr font = std::make_shared<sf::Font>();
    resources::loadResource<sf::Font>(font.get(), "./assets/fonts/PressStart2P-Regular.ttf");
    _phaserProgressbar.setFont(font);
    _torpedoProgressbar.setFont(font);

    resize(m_window.getSize(), m_window.getSize());
    generateEnemyButtons();
}

void AttackPanel::update()
{
    // regenerate buttons on system arrival
    const auto currentSystemData = Starship::get().currentSystemData;
    if (_prevSystemData != currentSystemData)
    {
        generateEnemyButtons();
        _prevSystemData = currentSystemData;
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
    for (enemybutton_ptr &btn : _enemyButtons)
    {
        btn->update();
        if (btn->clicked())
        {
            btn->setToggled(true);

            // untoggle all buttons except the one that was clicked
            for (enemybutton_ptr &b : _enemyButtons)
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
    for (enemybutton_ptr &enemyBtn : _enemyButtons)
        enemyBtn->draw();

    _phaserProgressbar.draw();
    _torpedoProgressbar.draw();
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

    for (enemybutton_ptr &btn : _enemyButtons)
    {
        const sf::Vector2f pos = btn->getPosition() - prevEnemyPanelPos;
        const sf::Vector2f relPos{pos.x / prevEnemyPanelSize.x, pos.y / prevEnemyPanelSize.y};
        btn->setPosition(newEnemyPanelPos.x + relPos.x * newEnemyPanelSize.x,
                         newEnemyPanelPos.y + relPos.y * newEnemyPanelSize.y);

        const sf::Vector2f size = btn->getSize();
        const sf::Vector2f relSize{size.x / prevEnemyPanelSize.x, size.y / prevEnemyPanelSize.y};
        btn->setSize({relSize.x * newEnemyPanelSize.x, relSize.y * newEnemyPanelSize.y});
    }

    _phaserProgressbar.setPos({newWindowSize.x * 0.64f, newWindowSize.y * 0.5f});
    _phaserProgressbar.resize(prevEnemyPanelSize.y, newEnemyPanelSize.y);
    _torpedoProgressbar.setPos({newWindowSize.x * 0.82f, newWindowSize.y * 0.5f});
    _torpedoProgressbar.resize(prevEnemyPanelSize.y, newEnemyPanelSize.y);
}

void AttackPanel::generateEnemyButtons()
{
    _enemyButtons.clear();

    resources::shared_texture_ptr untoggledTexture = std::make_shared<sf::Texture>();
    resources::loadResource<sf::Texture>(untoggledTexture.get(),
                                         "./assets/textures/controls/enemyButton_untoggled.png");

    resources::shared_texture_ptr toggledTexture = std::make_shared<sf::Texture>();
    resources::loadResource<sf::Texture>(toggledTexture.get(), "./assets/textures/controls/enemyButton_toggled.png");

    const auto enemyCount = Starship::get().currentSystemData.enemyCount;
    const auto SPACE_BETWEEN = _enemyPanel.getSize().x * 0.05f;
    const auto BUTTON_SIZE = _enemyPanel.getSize().x * 0.2f;
    const auto buttonAreaWidth = BUTTON_SIZE * enemyCount + SPACE_BETWEEN * (enemyCount - 1);
    const auto panelCenter = _enemyPanel.getPosition() + 0.5f * _enemyPanel.getSize();

    for (int i = 0; i < enemyCount; ++i)
    {
        enemybutton_ptr btn = std::make_unique<enemybutton>(m_window, untoggledTexture, toggledTexture);
        btn->setSize({BUTTON_SIZE, BUTTON_SIZE});
        btn->setPosition(panelCenter.x - buttonAreaWidth * 0.5f + i * (BUTTON_SIZE + SPACE_BETWEEN),
                         panelCenter.y - BUTTON_SIZE * 0.5f);

        _enemyButtons.push_back(std::move(btn));
    }
}
