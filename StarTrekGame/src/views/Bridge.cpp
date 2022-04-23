#include "../../include/views/Bridge.hpp"

Bridge::Bridge(sf::RenderWindow &window)
    : GameScript(window), _bg{"./assets/bridge.png", {0, 0}, static_cast<sf::Vector2f>(window.getSize())}, _helmsman{
                                                                                                               m_window}
{
    _helmsman.setNewTexture("./assets/helmsman.png");
    _helmsman.setPosition(200, 550);
    _helmsman.setSize({500, 600});
    _helmsman.setHitbox({350, 560}, {150, 550});
}

void Bridge::update()
{
    _helmsman.update();
}

void Bridge::draw()
{
    m_window.draw(_bg);
    _helmsman.draw();
}
