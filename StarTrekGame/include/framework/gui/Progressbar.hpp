#ifndef PROGRESSBAR_HPP
#define PROGRESSBAR_HPP

#include "../Component.hpp"
#include "../utils/ResourceLoader.hpp"

class Progressbar final : public Component
{
  public:
    Progressbar(sf::RenderWindow &, const sf::String &&title, unsigned int size);

    void update() override;
    void draw() override;
    void resize(float prevOrientationValue, float newOrientationValue);

    ////////// getters and setters ////////////
    void setPercentage(float percentage);
    [[nodiscard]] float percentage() const
    {
        return _percentage;
    }
    //
    void setFont(resources::shared_font_ptr &font)
    {
        _font = font;
        _percentageDisplay.setFont(*font);
        _titleDisplay.setFont(*font);
    }
    //
    void setPos(sf::Vector2f pos)
    {
        _pos = pos;
        _percentageDisplay.setPosition(pos);
        _titleDisplay.setPosition(pos.x, pos.y + _size * 0.85f);
    }
    [[nodiscard]] sf::Vector2f position() const
    {
        return _pos;
    }
    //
    void setSize(unsigned int size)
    {
        _size = size;
    }
    [[nodiscard]] unsigned int size() const
    {
        return _size;
    }
    ////////// END getters and setters ////////////

  protected:
    void generatePoint(float i, const sf::Color &clr);

  private:
    float _percentage{0.0f};

    sf::Vector2f _pos;
    unsigned int _size;
    std::vector<sf::RectangleShape> _points;

    resources::shared_font_ptr _font;
    sf::Text _percentageDisplay;
    sf::Text _titleDisplay;
};

#endif
