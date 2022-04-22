#include "../include/Game.hpp"
#include "../include/utils/Time.hpp"

Game::Game(unsigned int w, unsigned int h, const sf::String &title)
    : m_window{sf::VideoMode{w, h}, title}, _bg{"./assets/bridge.png",
                                                {0, 0},
                                                static_cast<sf::Vector2f>(m_window.getSize())}
{
    m_window.setFramerateLimit(60);
    m_window.setVerticalSyncEnabled(true);
}

void Game::handleEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_window.close();
    }
}

void Game::run()
{
    // create GameScript objects here

    while (m_window.isOpen())
    {
        Time::updateDeltaTime();
        handleEvents();

        m_window.clear();
        m_window.draw(_bg);
        m_window.display();
    }
}
