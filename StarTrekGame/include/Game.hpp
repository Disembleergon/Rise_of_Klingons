#ifndef GAME_HPP
#define GAME_HPP

#include "views/Bridge.hpp"
#include <SFML/Graphics.hpp>

class Game
{
  public:
    Game(unsigned int w, unsigned int h, const sf::String &title);
    void run();

  private:
    sf::RenderWindow m_window;
    void handleEvents();

    Bridge _bridge;
};

#endif
