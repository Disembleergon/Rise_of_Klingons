#include "../../include/views/helmsman/Helmsman.hpp"
#include "../../include/Game.hpp"
#include "../../include/Starship.hpp"

views::Helmsman::Helmsman(sf::RenderWindow &window)
    : Component(window), _panel("./assets/panel.png", {0, 0}, static_cast<sf::Vector2f>(window.getSize())),
      _returnButton{m_window}, _starmap{m_window, {650, 180}}, _warpslider{window, std::move(_warpsliderConfig)}
{
    _returnButton.setNewTexture("./assets/controls/returnButton.png");
    _returnButton.setPosition(100, 100);
    _returnButton.setSize({100, 100});
}

void views::Helmsman::update()
{
    _returnButton.update();
    _starmap.update();

    _warpslider.update();
    Starship::get().thrust = _warpslider.value() * 100;

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
    _warpslider.draw();
}
