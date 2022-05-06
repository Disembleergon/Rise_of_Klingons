#ifndef GAME_HPP
#define GAME_HPP

#include "views/Bridge.hpp"
#include "views/helmsman/Helmsman.hpp"
#include <SFML/Graphics.hpp>

enum class View
{
    BRIDGE,
    HELMSMAN,
    TACTICAL_OFFICER
};

class Game
{
  public:
    Game(unsigned int w, unsigned int h, const sf::String &title);
    void run();

    static View currentView; // default = View::BRIDGE

  protected:
    sf::RenderWindow m_window;
    void handleEvents();

  private:
    views::Bridge _bridge;
    views::Helmsman _helmsman;
};

#endif
