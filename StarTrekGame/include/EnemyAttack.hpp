#ifndef ENEMYATTACK_HPP
#define ENEMYATTACK_HPP

#include "Globals.hpp"
#include "Starship.hpp"
#include "framework/utils/Time.hpp"

void updateEnemyAttacks()
{
    if (!Starship::get().currentSystemData || Starship::get().thrust > 0)
        return;

    for (auto &enemy : Starship::get().currentSystemData->enemies)
    {
        ////////////////PHASER/////////////////
        // delay between each phaser shot
        if (enemy.shootingDelay > 0)
            enemy.shootingDelay -= Time::deltaTime;
        else
            enemy.isShootingPhasers = true;

        // don't shoot yet
        if (!enemy.isShootingPhasers)
            continue;

        // stop shooting
        if (enemy.phaserShootingProgress > Globals::get().PHASER_SHOOTING_DURATION)
        {
            enemy.isShootingPhasers = false;
            enemy.phaserShootingProgress = 0.0f;
            enemy.shootingDelay = Random::generate_floating_point(5.0f, 10.0f);
        }

        enemy.phaserShootingProgress += Time::deltaTime;

        static constexpr int SHIELD_DAMAGE = 4;
        static constexpr int HULL_DAMAGE = 2;
        Starship &starship = Starship::get();

        // do damage
        if (starship.shield > 0.0f)
            starship.shield -= Time::deltaTime * SHIELD_DAMAGE;
        else if (starship.hull > 0.0f)
            starship.hull -= Time::deltaTime * HULL_DAMAGE;
    }
}

#endif
