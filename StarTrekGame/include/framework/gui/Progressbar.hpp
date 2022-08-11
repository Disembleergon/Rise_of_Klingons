#ifndef PROGRESSBAR_HPP
#define PROGRESSBAR_HPP

#include "../Component.hpp"
#include "../utils/ResourceLoader.hpp"

class Progressbar final : public Component
{
  public:
    Progressbar(sf::RenderWindow &, const sf::Vector2f &pos, int size, resources::shared_font_ptr &font);

    void update() override;
    void draw() override;

    void setPercentage(float percentage);
    [[nodiscard]] inline float percentage() const
    {
        return _percentage;
    }

  private:
    float _percentage{0.0f};

    const sf::Vector2f _pos;
    const int _size;
    std::vector<sf::RectangleShape> _points;

    resources::shared_font_ptr _font;
    sf::Text _percentageDisplay;
};

#endif
