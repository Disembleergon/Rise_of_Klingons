#ifndef STARSHIP_HPP
#define STARSHIP_HPP

struct SystemData
{
    int enemyCount{0};
};

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
    SystemData currentSystemData;

  private:
    Starship() = default;
    Starship(const Starship &) = delete;
    Starship &operator=(const Starship &) = delete;
};

#endif
