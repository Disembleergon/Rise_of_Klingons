#ifndef PROGRESS_HPP
#define PROGRESS_HPP

#include "../Component.hpp"
#include "../utils/ResourceLoader.hpp"

namespace progress
{

////////////////////////////////////////////////////////

class ProgressCircle final : public Component
{
  public:
    ProgressCircle(sf::RenderWindow &, const sf::String &&title, unsigned int size);

    void update() override;
    void draw() override;
    void resize(float prevOrientationValue, float newOrientationValue);

    ////////// getters and setters ////////////
    void setPercentage(float percentage)
    {
        _percentage = percentage;
    }
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

////////////////////////////////////////////////////////////////////////////////////////

class ProgressBar final : public Component
{
  public:
    struct Config
    {
        sf::String title;
        sf::Color indicatorColor;
        resources::shared_font_ptr titleFont;
    };

    ProgressBar(sf::RenderWindow &);

    void update() override;
    void draw() override;

    void configure(Config &config)
    {
        _progressIndicator.setFillColor(config.indicatorColor);

        _titleFont = config.titleFont;
        _titleDisplay.setFont(*_titleFont);
        _titleDisplay.setString(config.title);
    }

    void setPercentage(float percentage)
    {
        _percentage = percentage;
    }
    [[nodiscard]] float percentage() const
    {
        return _percentage;
    }

    void setPos(sf::Vector2f pos)
    {
        _progressIndicator.setPosition(pos);
        _progressOverlay.setPosition(pos);
    }

    void setSize(sf::Vector2f size)
    {
        _progressOverlay.setSize(size);
        update(); // resize indicator

        _titleDisplay.setCharacterSize(static_cast<unsigned int>(size.y * 0.3f));
        _titleDisplay.setOrigin(0.5f * _titleDisplay.getLocalBounds().width,
                                0.5f * _titleDisplay.getLocalBounds().height);
        _titleDisplay.setPosition(_progressOverlay.getPosition() + 0.5f * size);
    }

  private:
    float _percentage{0.0f};

    sf::RectangleShape _progressIndicator;
    sf::RectangleShape _progressOverlay;

    resources::shared_font_ptr _titleFont;
    sf::Text _titleDisplay;
};

} // namespace progress

#endif
