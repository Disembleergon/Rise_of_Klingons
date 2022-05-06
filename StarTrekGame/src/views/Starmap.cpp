#include "../../include/views/helmsman/Starmap.hpp"

Starmap::Starmap(sf::RenderWindow &window, const sf::Vector2f &pos)
    : Component(window), _galaxyBG{"./assets/galaxy.png", pos, {_starmapWidth, _starmapHeight}}
{
}

void Starmap::update()
{
}

void Starmap::draw()
{
    m_window.draw(_galaxyBG);
}
