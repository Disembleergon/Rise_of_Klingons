#ifndef GAMESPRITE_HPP
#define GAMESPRITE_HPP

#include "utils/TextureLoader.hpp"
#include <SFML/Graphics.hpp>

class GameSprite : public sf::RectangleShape
{
  public:
    GameSprite() : _texture{std::make_unique<sf::Texture>()}
    {
    }
    GameSprite(const sf::String &texturePath, const sf::Vector2f &pos = {}, const sf::Vector2f &size = {})
        : _texture{std::make_unique<sf::Texture>()}
    {
        setPosition(pos);
        setSize(size);

        setNewTexture(texturePath);
    };

    void setNewTexture(const sf::String &tp)
    {
        TextureLoader::loadTexture(_texture, tp);
        setTexture(_texture.get());
    }

  private:
    TextureLoader::unique_texture_ptr _texture;
};

#endif
