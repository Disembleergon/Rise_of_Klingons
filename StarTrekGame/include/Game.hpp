#ifndef GAME_HPP
#define GAME_HPP

#include "views/bridge/Bridge.hpp"
#include "views/helmsman/Helmsman.hpp"
#include "views/missions/MissionView.hpp"
#include "views/tacticalOfficer/TacticalOfficer.hpp"
#include <SFML/Graphics.hpp>

#define PREFERRED_WINDOW_WIDTH 1800.0f
#define PREFERRED_WINDOW_HEIGHT 1300.0f

enum class View
{
    BRIDGE,
    HELMSMAN,
    TACTICAL_OFFICER,
    MISSION_VIEW
};

class Game
{
  public:
    Game(unsigned int w, unsigned int h, const sf::String &title);
    void run();

    static constexpr float ASPECT_RATIO = PREFERRED_WINDOW_HEIGHT / PREFERRED_WINDOW_WIDTH;
    static View currentView; // default = View::BRIDGE

  protected:
    sf::RenderWindow m_window;

    sf::Vector2u _previousWindowSize; // keeping track for the previous window size (resize event)
    void handleEvents();
    void resize();

  private:
    views::MissionView _missionView;
    views::Helmsman _helmsman;
    views::Bridge _bridge;
    views::TacticalOfficer _tacticalOfficer;
};

#endif
