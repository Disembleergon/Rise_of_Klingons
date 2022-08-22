#ifndef PROGRESS_HPP
#define PROGRESS_HPP

#include "../Component.hpp"
#include "../utils/ResourceLoader.hpp"

namespace progress
{

struct Config
{
    sf::String title;
    sf::Color color;
    resources::shared_font_ptr font;
};

// abstract
class ProgressElement
{
  public:
    void setPercentage(float percentage)
    {
        _percentage = percentage;
    }
    [[nodiscard]] float percentage() const
    {
        return _percentage;
    }

    virtual void configure(const Config &) = 0;
    virtual void setPos(sf::Vector2f pos) = 0;

  protected:
    float _percentage{0.0f};
};

////////////////////////////////////////////////////////

class ProgressCircle final : public Component, public ProgressElement
{
  public:
    ProgressCircle(sf::RenderWindow &, unsigned int size);

    void update() override;
    void draw() override;
    void resize(float prevOrientationValue, float newOrientationValue);

    void configure(const Config &config) override
    {
        _clr = config.color;

        _font = config.font;
        _percentageDisplay.setFont(*_font);
        _titleDisplay.setFont(*_font);
        _titleDisplay.setString(config.title);
    }

    void setPos(sf::Vector2f pos) override
    {
        _pos = pos;
        _percentageDisplay.setPosition(pos);
        _titleDisplay.setPosition(pos.x, pos.y + _size * 0.85f);
    }

  protected:
    void generatePoint(float i, const sf::Color &clr);

  private:
    sf::Vector2f _pos;
    unsigned int _size;
    std::vector<sf::RectangleShape> _points;
    sf::Color _clr;

    resources::shared_font_ptr _font;
    sf::Text _percentageDisplay;
    sf::Text _titleDisplay;
};

////////////////////////////////////////////////////////////////////////////////////////

class ProgressBar final : public Component, public ProgressElement
{
  public:
    ProgressBar(sf::RenderWindow &);

    void update() override;
    void draw() override;

    void configure(const Config &config) override
    {
        _progressIndicator.setFillColor(config.color);

        _titleFont = config.font;
        _titleDisplay.setFont(*_titleFont);
        _titleDisplay.setString(config.title);
    }

    void setPos(sf::Vector2f pos) override
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
    sf::RectangleShape _progressIndicator;
    sf::RectangleShape _progressOverlay;

    resources::shared_font_ptr _titleFont;
    sf::Text _titleDisplay;
};

} // namespace progress

#endif
