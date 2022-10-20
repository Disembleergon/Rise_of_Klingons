#include "../../include/views/tacticalOfficer/ContactPanel.hpp"

ContactPanel::ContactPanel(sf::RenderWindow &window) : Component(window)
{
    _panel.setFillColor(sf::Color{203, 219, 252});
    _panel.setOutlineColor(sf::Color{99, 155, 255});

    resize(m_window.getSize(), m_window.getSize());
}

void ContactPanel::update()
{
}

void ContactPanel::draw()
{
    m_window.draw(_panel);
}

void ContactPanel::resize(const sf::Vector2u &prevWindowSize, const sf::Vector2u &newWindowSize)
{
    _panel.setOutlineThickness(newWindowSize.x * 0.005f);
    _panel.setPosition(newWindowSize.x * 0.09f, newWindowSize.y * 0.2f);
    _panel.setSize({newWindowSize.x * 0.39f, newWindowSize.y * 0.45f});
}
