#ifndef RESOURCELOADER_HPP
#define RESOURCELOADER_HPP

#include "ErrorHandling.hpp"
#include "SFML/Audio/SoundBuffer.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/String.hpp"

#include <concepts>
#include <memory>

namespace resources
{
//
using shared_texture_ptr = std::shared_ptr<sf::Texture>;
using shared_font_ptr = std::shared_ptr<sf::Font>;
//

template <class T>
    requires std::is_same_v<T, sf::Texture> || std::is_same_v<T, sf::Font> || std::is_same_v<T, sf::SoundBuffer>
void loadResource(T *ptr, const sf::String &path)
{
    if (!ptr->loadFromFile(path))
        throw asset_not_found{path};
}
} // namespace resources

#endif
