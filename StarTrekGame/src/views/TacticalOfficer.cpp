#include "../../include/views/tacticalOfficer/TacticalOfficer.hpp"
#include "../../include/Game.hpp"

views::TacticalOfficer::TacticalOfficer(sf::RenderWindow &window)
    : Component(window), _panel("./assets/panel.png"), _returnButton{m_window},
      _enemyPanel("./assets/enemyOverviewPanel.png"), _prevSystemData{Starship::get().currentSystemData}
{
    _returnButton.setNewTexture("./assets/controls/returnButton.png");
    resize(m_window.getSize(), m_window.getSize());
    generateEnemyButtons();
}

void views::TacticalOfficer::update()
{
    _returnButton.update();
    if (_returnButton.clicked())
    {
        Game::currentView = View::BRIDGE;
    }

    // regenerate buttons on system arrival
    const auto currentSystemData = Starship::get().currentSystemData;
    if (_prevSystemData != currentSystemData)
    {
        generateEnemyButtons();
        _prevSystemData = currentSystemData;
    }

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

void views::TacticalOfficer::draw()
{
    m_window.draw(_panel);
    _returnButton.draw();

    m_window.draw(_enemyPanel);
    for (enemybutton_ptr &enemyBtn : _enemyButtons)
        enemyBtn->draw();
}

void views::TacticalOfficer::resize(sf::Vector2u prevWindowSize, sf::Vector2u newWindowSize)
{
    _panel.setPosition(0, 0);
    _panel.setSize(static_cast<sf::Vector2f>(newWindowSize));

    _returnButton.setPosition(newWindowSize.x * 0.06f, newWindowSize.y * 0.08f);
    _returnButton.setSize({newWindowSize.x * 0.05f, newWindowSize.y * 0.07f});

    const sf::Vector2f prevEnemyPanelPos = _enemyPanel.getPosition();
    const sf::Vector2f prevEnemyPanelSize = _enemyPanel.getSize();

    _enemyPanel.setPosition(newWindowSize.x * 0.56f, newWindowSize.y * 0.12f);
    _enemyPanel.setSize({newWindowSize.x * 0.35f, newWindowSize.y * 0.24f});

    const sf::Vector2f newEnemyPanelPos = _enemyPanel.getPosition();
    const sf::Vector2f newEnemyPanelSize = _enemyPanel.getSize();

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
}

void views::TacticalOfficer::generateEnemyButtons()
{
    _enemyButtons.clear();

    TextureLoader::shared_texture_ptr untoggledTexture = std::make_shared<sf::Texture>();
    TextureLoader::loadTexture(untoggledTexture, "./assets/controls/enemyButton_untoggled.png");

    TextureLoader::shared_texture_ptr toggledTexture = std::make_shared<sf::Texture>();
    TextureLoader::loadTexture(toggledTexture, "./assets/controls/enemyButton_toggled.png");

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