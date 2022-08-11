#ifndef RESOURCELOADER_HPP
#define RESOURCELOADER_HPP

#include "ErrorHandling.hpp"
#include "SFML/Graphics.hpp"

#include <concepts>

namespace resources
{
//
using shared_texture_ptr = std::shared_ptr<sf::Texture>;
using unique_texture_ptr = std::unique_ptr<sf::Texture>;
//
using shared_font_ptr = std::shared_ptr<sf::Font>;
//

template <class T>
requires std::is_same_v<T, sf::Texture> || std::is_same_v<T, sf::Font>
void loadResource(T *ptr, const sf::String &path)
{
    if (!ptr->loadFromFile(path))
        throw asset_not_found{path};
}
} // namespace resources

#endif
