#include "../../include/views/tacticalOfficer/TacticalOfficer.hpp"
#include "../../include/Game.hpp"
#include "../../include/Globals.hpp"

#define STARSHIP_STATS_PROGRESSBAR_SIZE 150u

views::TacticalOfficer::TacticalOfficer(sf::RenderWindow &window)
    : Component(window), _panel("./assets/textures/panel.png"), _returnButton{m_window}, _attackPanel(window),
      _starshipHullDisplay(window, STARSHIP_STATS_PROGRESSBAR_SIZE),
      _starshipShieldDisplay(window, STARSHIP_STATS_PROGRESSBAR_SIZE)
{
    resources::shared_font_ptr font = std::make_shared<sf::Font>();
    resources::loadResource<sf::Font>(font.get(), globals::FONT_PATH);

    progress::Config hullDisplayConfig{"Hull", globals::HULL_RED, font};
    _starshipHullDisplay.configure(hullDisplayConfig);
    progress::Config shieldDisplayConfig{"Shield", globals::SHIELD_BLUE, font};
    _starshipShieldDisplay.configure(shieldDisplayConfig);

    _returnButton.setNewTexture("./assets/textures/controls/returnButton.png");
    resize(m_window.getSize(), m_window.getSize());
}

void views::TacticalOfficer::update()
{
    _returnButton.update();
    if (_returnButton.clicked())
    {
        Game::currentView = View::BRIDGE;
    }

    const auto currentHull = Starship::get().hull;
    const auto currentShield = Starship::get().shield;
    if (_prevStarshipHull != currentHull)
    {
        _starshipHullDisplay.setPercentage(currentHull / MAX_HULL);
        _starshipHullDisplay.update();
        _prevStarshipHull = currentHull;
    }
    if (_prevStarshipShield != currentShield)
    {
        _starshipShieldDisplay.setPercentage(currentShield / MAX_SHIELD);
        _starshipShieldDisplay.update();
        _prevStarshipShield = currentShield;
    }

    _attackPanel.update();
}

void views::TacticalOfficer::draw()
{
    m_window.draw(_panel);
    _returnButton.draw();
    _starshipHullDisplay.draw();
    _starshipShieldDisplay.draw();

    _attackPanel.draw();
}

void views::TacticalOfficer::resize(sf::Vector2u prevWindowSize, sf::Vector2u newWindowSize)
{
    _panel.setPosition(0, 0);
    _panel.setSize(static_cast<sf::Vector2f>(newWindowSize));

    float prevReturnButtonSize = _returnButton.getSize().x; // orientation values for ProgressCircles
    _returnButton.setPosition(newWindowSize.x * 0.06f, newWindowSize.y * 0.08f);
    _returnButton.setSize({newWindowSize.x * 0.05f, newWindowSize.y * 0.07f});
    const float newReturnButtonSize = _returnButton.getSize().x;

    // for resizing the progressbars at the beginning
    if (prevReturnButtonSize == 0.0f)
        prevReturnButtonSize = newReturnButtonSize;

    _starshipHullDisplay.setPos({newWindowSize.x * 0.19f, newWindowSize.y * 0.8f});
    _starshipHullDisplay.resize(prevReturnButtonSize, newReturnButtonSize);
    _starshipShieldDisplay.setPos({newWindowSize.x * 0.33f, newWindowSize.y * 0.8f});
    _starshipShieldDisplay.resize(prevReturnButtonSize, newReturnButtonSize);

    _attackPanel.resize(prevWindowSize, newWindowSize);
}
