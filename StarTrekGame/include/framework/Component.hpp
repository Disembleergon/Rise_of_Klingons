#ifndef GAMESCRIPT_HPP
#define GAMESCRIPT_HPP

#include <SFML/Graphics.hpp>

class Component
{
  public:
    Component(sf::RenderWindow &window)
        : m_window(window){
              // EMPTY
          };

    Component() = delete;
    virtual ~Component() = default;
    Component(const Component &) = delete;
    Component &operator=(const Component &) = delete;

    virtual void draw() = 0;
    virtual void update() = 0;

  protected:
    sf::RenderWindow &m_window;
};

#endif
