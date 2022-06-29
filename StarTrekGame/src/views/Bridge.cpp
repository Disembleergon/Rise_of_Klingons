#include "../../include/views/bridge/Bridge.hpp"
#include "../../include/Game.hpp"

views::Bridge::Bridge(sf::RenderWindow &window)
    : Component(window), _bg{"./assets/bridge.png"}, _helmsman{m_window}, _tacticalOfficer{m_window}, _galaxyWindow{
                                                                                                          window}
{
    _helmsman.setNewTexture("./assets/helmsman.png");
    _tacticalOfficer.setNewTexture("./assets/tacticalOfficer.png");

    resize(m_window.getSize(), m_window.getSize());
}

void views::Bridge::update()
{
    _helmsman.update();
    _tacticalOfficer.update();
    _galaxyWindow.update();

    if (_helmsman.clicked())
    {
        Game::currentView = View::HELMSMAN;
    }
    else if (_tacticalOfficer.clicked())
    {
        Game::currentView = View::TACTICAL_OFFICER;
    }
}

void views::Bridge::draw()
{
    _galaxyWindow.draw();
    m_window.draw(_bg);
    _helmsman.draw();
    _tacticalOfficer.draw();
}

void views::Bridge::resize(sf::Vector2u prevWindowSize, sf::Vector2u newWindowSize)
{
    const sf::Vector2f crewmemberSize{newWindowSize.x * 0.11f, newWindowSize.y * 0.46f};
    const auto crewMemberY = newWindowSize.y * 0.45f;

    _helmsman.setPosition(newWindowSize.x * 0.18f, crewMemberY);
    _helmsman.setSize(crewmemberSize);
    _tacticalOfficer.setPosition(newWindowSize.x * 0.71f, crewMemberY);
    _tacticalOfficer.setSize(crewmemberSize);

    _bg.setSize(static_cast<sf::Vector2f>(newWindowSize));
    _galaxyWindow.resize(prevWindowSize, newWindowSize);
}
