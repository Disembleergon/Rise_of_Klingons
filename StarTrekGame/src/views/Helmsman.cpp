#include "../../include/views/helmsman/Helmsman.hpp"
#include "../../include/Game.hpp"
#include "../../include/Globals.hpp"
#include "../../include/Starship.hpp"

views::Helmsman::Helmsman(sf::RenderWindow &window, Bridge &bridge)
    : Component(window), _returnButton{m_window}, _starmap{m_window, bridge, _warpslider},
      _warpslider{window, std::move(_warpsliderConfig)}
{
    _panel.setNewTexture(Globals::get().PANEL_TEXTURE);
    _returnButton.setNewTexture(Globals::get().RETURN_BTN_TEXTURE);
    resize(m_window.getSize(), m_window.getSize());
}

void views::Helmsman::update()
{
    _returnButton.update();
    _starmap.update();

    _warpslider.update();
    Starship::get().thrust = _warpslider.value() * MAX_THRUST;

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

void views::Helmsman::resize(const sf::Vector2u &prevWindowSize, const sf::Vector2u &newWindowSize)
{
    _panel.setPosition(0, 0);
    _panel.setSize(static_cast<sf::Vector2f>(newWindowSize));

    _returnButton.setPosition(newWindowSize.x * 0.06f, newWindowSize.y * 0.08f);
    _returnButton.setSize({newWindowSize.x * 0.05f, newWindowSize.y * 0.07f});

    _starmap.resize(prevWindowSize, newWindowSize);
    _warpslider.resize(prevWindowSize, newWindowSize);
}
