#ifndef TIME_HPP
#define TIME_HPP

#include <SFML/System.hpp>

// for movement etc., always multiply the values with deltaTime!
// Just include utils/Time.hpp and multiply with Time::deltaTime

class Time
{
  public:
    static void updateDeltaTime()
    {
        deltaTime = m_dtClock.restart().asSeconds();
    }

    static float deltaTime;

  private:
    static sf::Clock m_dtClock;
};

#endif
