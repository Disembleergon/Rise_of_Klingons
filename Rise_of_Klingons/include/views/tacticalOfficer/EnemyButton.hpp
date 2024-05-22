#ifndef ENEMYBUTTON_HPP
#define ENEMYBUTTON_HPP

#include "../../Starship.hpp"
#include "../../framework/gui/Clickables.hpp"
#include <memory>

class EnemyButton final : public ToggleButton
{
  public:
    EnemyButton(sf::RenderWindow &window, const resources::shared_texture_ptr &texture1,
                const resources::shared_texture_ptr &texture2, EnemyData &enemydata)
        : ToggleButton(window, texture1, texture2), data{enemydata}
    {
    }

    EnemyData &data; // modify enemy data value of current system data (stored in
                     // current selected StarmapButton)
    using enemybutton_ptr = std::unique_ptr<EnemyButton>;
};

#endif
