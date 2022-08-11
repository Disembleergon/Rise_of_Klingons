#include "../../include/views/tacticalOfficer/TacticalOfficer.hpp"
#include "../../include/Game.hpp"

views::TacticalOfficer::TacticalOfficer(sf::RenderWindow &window)
    : Component(window), _panel("./assets/panel.png"), _returnButton{m_window}, _attackPanel(window)
{
    _returnButton.setNewTexture("./assets/controls/returnButton.png");
    resize(m_window.getSize(), m_window.getSize());
}

void views::TacticalOfficer::update()
{
    _returnButton.update();
    if (_returnButton.clicked())
    {
        Game::currentView = View::BRIDGE;
    }

    _attackPanel.update();
}

void views::TacticalOfficer::draw()
{
    m_window.draw(_panel);
    _returnButton.draw();
    _attackPanel.draw();
}

void views::TacticalOfficer::resize(sf::Vector2u prevWindowSize, sf::Vector2u newWindowSize)
{
    _panel.setPosition(0, 0);
    _panel.setSize(static_cast<sf::Vector2f>(newWindowSize));

    _returnButton.setPosition(newWindowSize.x * 0.06f, newWindowSize.y * 0.08f);
    _returnButton.setSize({newWindowSize.x * 0.05f, newWindowSize.y * 0.07f});

    _attackPanel.resize(prevWindowSize, newWindowSize);
}
