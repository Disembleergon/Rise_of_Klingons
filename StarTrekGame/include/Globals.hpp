#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include "framework/utils/ResourceLoader.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/String.hpp>

/*
 * Singleton
 */
class Globals
{
  public:
    static const Globals &get()
    {
        static Globals instance;
        return instance;
    }

    inline static const sf::Color UI_BLUE{48, 187, 242};
    inline static const sf::Color HULL_RED{227, 93, 84};
    inline static const sf::Color SHIELD_BLUE{111, 210, 237};

    static constexpr float PHASER_SHOOTING_DURATION = 2.5f;

    inline static resources::shared_font_ptr FONT{std::make_shared<sf::Font>()};
    inline static resources::shared_texture_ptr PANEL_TEXTURE{std::make_shared<sf::Texture>()};
    inline static resources::shared_texture_ptr RETURN_BTN_TEXTURE{std::make_shared<sf::Texture>()};

  private:
    Globals()
    {
        resources::loadResource<sf::Font>(FONT.get(), "./assets/fonts/PressStart2P-Regular.ttf");
        resources::loadResource<sf::Texture>(PANEL_TEXTURE.get(), "./assets/textures/panel.png");
        resources::loadResource<sf::Texture>(RETURN_BTN_TEXTURE.get(), "./assets/textures/controls/returnButton.png");
    }

    Globals(const Globals &) = delete;
    Globals &operator=(const Globals &) = delete;
};

#endif
