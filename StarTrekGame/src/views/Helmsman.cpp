#include "../../include/views/Helmsman.hpp"
#include "../../include/Game.hpp"

views::Helmsman::Helmsman(sf::RenderWindow &window)
    : Component(window),
      _panel("./assets/panel.png", {0, 0}, static_cast<sf::Vector2f>(window.getSize())), _returnButton{m_window}
{
    _returnButton.setNewTexture("./assets/controls/returnButton.png");
    _returnButton.setPosition(100, 100);
    _returnButton.setSize({100, 100});
    _returnButton.setClickEvent([]() { Game::currentView = View::BRIDGE; });
}

void views::Helmsman::update()
{
    _returnButton.update();
}

void views::Helmsman::draw()
{
    m_window.draw(_panel);
    _returnButton.draw();
}
