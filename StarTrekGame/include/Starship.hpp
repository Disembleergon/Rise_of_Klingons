#ifndef STARSHIP_HPP
#define STARSHIP_HPP

#include <compare>
#include <vector>

#define MAX_PHASER_AMMO 100
#define MAX_TORPEDO_AMMO 20
#define MAX_THRUST 100
#define MAX_HULL 100
#define MAX_SHIELD 100

struct EnemyData
{
    float hull{MAX_HULL};
    float shield{MAX_SHIELD};
};

struct SystemData
{
    std::vector<EnemyData> enemies;
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
    float hull{MAX_HULL};
    float shield{MAX_SHIELD};

    using phaserAmmo_t = float;
    using torpedoAmmo_t = int;
    float phaserAmmo{MAX_PHASER_AMMO};
    int torpedoAmmo{MAX_TORPEDO_AMMO};

    SystemData *currentSystemData{nullptr}; // pointer to modify the system data (stored in StarmapButton class)

  private:
    Starship() = default;
    Starship(const Starship &) = delete;
    Starship &operator=(const Starship &) = delete;
};

#endif
