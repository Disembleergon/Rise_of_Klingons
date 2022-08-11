#include "../../include/views/tacticalOfficer/AttackPanel.hpp"

AttackPanel::AttackPanel(sf::RenderWindow &window)
    : Component(window),
      _enemyPanel("./assets/enemyOverviewPanel.png"), _prevSystemData{Starship::get().currentSystemData}
{
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
}

void AttackPanel::resize(sf::Vector2u prevWindowSize, sf::Vector2u newWindowSize)
{
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

void AttackPanel::generateEnemyButtons()
{
    _enemyButtons.clear();

    resources::shared_texture_ptr untoggledTexture = std::make_shared<sf::Texture>();
    resources::loadResource<sf::Texture>(untoggledTexture.get(), "./assets/controls/enemyButton_untoggled.png");

    resources::shared_texture_ptr toggledTexture = std::make_shared<sf::Texture>();
    resources::loadResource<sf::Texture>(toggledTexture.get(), "./assets/controls/enemyButton_toggled.png");

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
