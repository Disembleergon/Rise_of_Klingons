#ifndef GAMESPRITE_HPP
#define GAMESPRITE_HPP

#include "utils/ErrorHandling.hpp"
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
        loadTexture(tp);
        setTexture(&_texture);
    }

  protected:
    void loadTexture(const sf::String &tp)
    {
        if (!_texture.loadFromFile(tp))
            throw asset_not_found{};
    }

    sf::Texture _texture;
};

#endif
