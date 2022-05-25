#ifndef GALAXYWINDOW_HPP
#define GALAXYWINDOW_HPP

#include "../../framework/Component.hpp"

namespace galaxywindow
{
class Star : public sf::RectangleShape
{

  public:
    Star(const sf::Vector2f &&direction) : _direction{direction}
    {
        setFillColor(sf::Color{255, 255, 255, 0U});
    }

    sf::Vector2f direction() const
    {
        return _direction;
    }

    using star_ptr = std::unique_ptr<Star>;

  private:
    const sf::Vector2f _direction;
};

class GalaxyWindow final : public Component
{
    static constexpr int NUM_STARS = 100;

  public:
    GalaxyWindow(sf::RenderWindow &window, const sf::Vector2f &windowPos, const sf::Vector2f &windowSize);

    void update() override;
    void draw() override;

  protected:
    void generateNewStar(float starX, float starY);

  private:
    const sf::Vector2f _windowPos;
    const sf::Vector2f _windowSize;
    const sf::Vector2f _windowCenter;

    std::vector<Star::star_ptr> _stars;
};
} // namespace galaxywindow

#endif
