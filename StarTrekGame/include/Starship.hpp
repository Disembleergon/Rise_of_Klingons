#ifndef STARSHIP_HPP
#define STARSHIP_HPP

/*
 * Singleton
 */

class Starship final
{
  public:
    [[nodiscard]] static Starship &get()
    {
        static Starship starship;
        return starship;
    }

    float thrust{0.0f};
    float health{0.0f};

  private:
    Starship() = default;
    Starship(const Starship &) = delete;
    Starship &operator=(const Starship &) = delete;
};

#endif
