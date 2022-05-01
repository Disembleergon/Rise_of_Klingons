#include "../../include/views/Bridge.hpp"

Bridge::Bridge(sf::RenderWindow &window)
    : Component(window), _bg{"./assets/bridge.png", {0, 0}, static_cast<sf::Vector2f>(window.getSize())},
      _helmsman{m_window, []() {}}, _tacticalOfficer{m_window, []() {}}
{
    _helmsman.setNewTexture("./assets/helmsman.png");
    _helmsman.setPosition(150, 585);
    _helmsman.setSize({600, 600});
    _helmsman.setHitbox({285, 595}, {280, 550});

    _tacticalOfficer.setNewTexture("./assets/tacticalOfficer.png");
    _tacticalOfficer.setPosition(1100, 585);
    _tacticalOfficer.setSize({600, 600});
    _tacticalOfficer.setHitbox({1240, 595}, {275, 550});
}

void Bridge::update()
{
    _helmsman.update();
    _tacticalOfficer.update();
}

void Bridge::draw()
{
    m_window.draw(_bg);
    _helmsman.draw();
    _tacticalOfficer.draw();
}
