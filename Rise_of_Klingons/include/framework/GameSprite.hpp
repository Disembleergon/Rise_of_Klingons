#ifndef GAMESPRITE_HPP
#define GAMESPRITE_HPP

#include "utils/ResourceLoader.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class GameSprite : public sf::RectangleShape
{
  public:
    GameSprite() : _texture(std::make_unique<sf::Texture>())
    {
    }
    GameSprite(const sf::String &texturePath, const sf::Vector2f &pos = {}, const sf::Vector2f &size = {})
        : _texture{std::make_shared<sf::Texture>()}
    {
        setPosition(pos);
        setSize(size);

        setNewTexture(texturePath);
    };

    void setNewTexture(const sf::String &tp)
    {
        resources::loadResource<sf::Texture>(_texture.get(), tp);
        setTexture(_texture.get());
    }

    void setNewTexture(resources::shared_texture_ptr &texture)
    {
        _texture = texture;
        setTexture(_texture.get());
    }

  private:
    resources::shared_texture_ptr _texture;
};

#endif
