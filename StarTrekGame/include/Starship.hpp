#ifndef STARSHIP_HPP
#define STARSHIP_HPP

#include <compare>

#define MAX_PHASER_AMMO 100
#define MAX_TORPEDO_AMMO 20
#define MAX_THRUST 100

struct SystemData
{
    int enemyCount{0};
    auto operator<=>(const SystemData &) const = default;
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

    float thrust{0.0f}; // value between 0 and 100 (look at MAX_THRUST)
    float health{0.0f};

    using phaserAmmo_t = float;
    using torpedoAmmo_t = int;
    float phaserAmmo{MAX_PHASER_AMMO};
    int torpedoAmmo{MAX_TORPEDO_AMMO};

    SystemData currentSystemData;

  private:
    Starship() = default;
    Starship(const Starship &) = delete;
    Starship &operator=(const Starship &) = delete;
};

#endif
