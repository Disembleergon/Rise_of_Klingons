#ifndef TEXTURELOADER_HPP
#define TEXTURELOADER_HPP

#include "ErrorHandling.hpp"
#include "SFML/Graphics.hpp"

class TextureLoader final
{
  public:
    using shared_texture_ptr = std::shared_ptr<sf::Texture>;
    using unique_texture_ptr = std::unique_ptr<sf::Texture>;

    static void loadTexture(sf::Texture *texture, const sf::String &img)
    {
        if (!texture->loadFromFile(img))
            throw asset_not_found{};
    }

    static void loadTexture(shared_texture_ptr &texture, const sf::String &img)
    {
        if (!texture->loadFromFile(img))
            throw asset_not_found{};
    }

    static void loadTexture(unique_texture_ptr &texture, const sf::String &img)
    {
        if (!texture->loadFromFile(img))
            throw asset_not_found{};
    }
};

#endif
