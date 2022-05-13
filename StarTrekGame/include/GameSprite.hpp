#ifndef GAMESPRITE_HPP
#define GAMESPRITE_HPP

#include "utils/TextureLoader.hpp"
#include <SFML/Graphics.hpp>

class GameSprite : public sf::RectangleShape
{
  public:
    GameSprite() = default;
    GameSprite(const sf::String &texturePath, const sf::Vector2f &pos = {}, const sf::Vector2f &size = {})
    {
        setPosition(pos);
        setSize(size);

        setNewTexture(texturePath);
    };

    void setNewTexture(const sf::String &tp)
    {
        TextureLoader::loadTexture(_texture, tp);
        setTexture(&_texture);
    }

  private:
    sf::Texture _texture;
};

#endif
