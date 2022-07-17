#include "../include/Game.hpp"
#include "../include/framework/utils/Time.hpp"

// static member variable
View Game::currentView = View::BRIDGE;

Game::Game(unsigned int w, unsigned int h, const sf::String &title)
    : m_window{sf::VideoMode{w, h}, title, sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close},
      _bridge(m_window), _helmsman(m_window, _bridge), _tacticalOfficer(m_window)
{
    m_window.setFramerateLimit(60);
    m_window.setVerticalSyncEnabled(true);
}

void Game::handleEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            m_window.close();
            break;
        case sf::Event::Resized:
            resize();
            break;
        }
    }
}

void Game::resize()
{
    // ---- keep aspect ratio ----
    auto windowSize = m_window.getSize();
    if (windowSize.y >= windowSize.x)
    {
        windowSize.x = windowSize.y / ASPECT_RATIO;
    }
    else
    {
        windowSize.y = windowSize.x * ASPECT_RATIO;
    }

    // --- update sprites/hitboxes etc. ---
    _bridge.resize(_previousWindowSize, windowSize);
    _helmsman.resize(_previousWindowSize, windowSize);
    _tacticalOfficer.resize(_previousWindowSize, windowSize);

    m_window.setSize(windowSize);
    sf::View newView{sf::FloatRect{0, 0, static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)}};
    m_window.setView(newView);
}

void Game::run()
{
    while (m_window.isOpen())
    {
        Time::updateDeltaTime();

        _previousWindowSize = m_window.getSize();
        handleEvents();
        m_window.clear();

        // things that have to always get updated/drawn
        _helmsman.updateStarshipPositionOnStarmap();

        // update/draw things depending on current view
        switch (currentView)
        {
        case View::BRIDGE:
            _bridge.update();
            _bridge.draw();
            break;
        case View::HELMSMAN:
            _helmsman.update();
            _helmsman.draw();
            break;
        case View::TACTICAL_OFFICER:
            _tacticalOfficer.update();
            _tacticalOfficer.draw();
            break;
        }

        m_window.display();
    }
}
