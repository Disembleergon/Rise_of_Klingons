#include "../include/Game.hpp"
#include "../include/utils/Time.hpp"

// static member variable
View Game::currentView = View::BRIDGE;

Game::Game(unsigned int w, unsigned int h, const sf::String &title)
    : m_window{sf::VideoMode{w, h}, title}, _bridge(m_window)
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

        switch (currentView)
        {
        case View::BRIDGE:
            _bridge.update();
            _bridge.draw();
            break;
        }

        m_window.display();
    }
}
