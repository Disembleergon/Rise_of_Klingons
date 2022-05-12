#include "../../include/views/helmsman/Helmsman.hpp"
#include "../../include/Game.hpp"

views::Helmsman::Helmsman(sf::RenderWindow &window)
    : Component(window), _panel("./assets/panel.png", {0, 0}, static_cast<sf::Vector2f>(window.getSize())),
      _returnButton{m_window}, _starmap{m_window, {650, 180}}
{
    _returnButton.setNewTexture("./assets/controls/returnButton.png");
    _returnButton.setPosition(100, 100);
    _returnButton.setSize({100, 100});
}

void views::Helmsman::update()
{
    _returnButton.update();
    _starmap.update();

    if (_returnButton.clicked())
    {
        Game::currentView = View::BRIDGE;
    }
}

void views::Helmsman::draw()
{
    m_window.draw(_panel);
    _returnButton.draw();
    _starmap.draw();
}
