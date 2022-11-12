#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <concepts>
#include <random>

class Random
{
  public:
    template <std::integral T> static T generate_integral(const T min, const T max)
    {
        std::uniform_int_distribution<T> dist(min, max);
        return dist(engine);
    }

    template <std::floating_point T> static T generate_floating_point(const T min, const T max)
    {
        std::uniform_real_distribution<T> dist(min, max);
        return dist(engine);
    }

  private:
    static std::random_device rd;
    static std::mt19937_64 engine;
};

#endif
