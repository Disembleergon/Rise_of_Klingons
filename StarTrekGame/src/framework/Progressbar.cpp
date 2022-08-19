#include "../../include/framework/gui/Progressbar.hpp"
#include <numbers>

constexpr int GREYVALUE = 40;
constexpr int GREYTEXTVALUE = GREYVALUE + 100;

Progressbar::Progressbar(sf::RenderWindow &window, const sf::String &&title, unsigned int size)
    : Component(window), _size{size}
{
    _percentageDisplay.setFillColor(sf::Color{GREYTEXTVALUE});
    setPercentage(0.0f);

    _titleDisplay.setFillColor(sf::Color{GREYTEXTVALUE});
    _titleDisplay.setString(title);
}

void Progressbar::update()
{
    _points.clear();

    static constexpr float INCREMENT = 0.1f;
    static constexpr float OVERLAP = 0.55f;
    const sf::Color BLUE{48, 187, 242};

    static constexpr float START = std::numbers::pi_v<float> - OVERLAP;
    static constexpr float END = std::numbers::pi_v<float> + OVERLAP * 2.0f;

    // blue part
    for (float i = START; i < START + (END * _percentage); i += INCREMENT)
        generatePoint(i, BLUE);

    // grey part
    for (float i = START + (END * _percentage); i < START + END; i += INCREMENT)
        generatePoint(i, sf::Color{GREYVALUE});
}

void Progressbar::draw()
{
    for (sf::RectangleShape &p : _points)
        m_window.draw(p);

    m_window.draw(_percentageDisplay);
    m_window.draw(_titleDisplay);
}

void Progressbar::resize(float prevOrientationValue, float newOrientationValue)
{
    const auto relSize = _size / prevOrientationValue;
    setSize(relSize * newOrientationValue);

    _percentageDisplay.setCharacterSize(static_cast<unsigned int>(_size * 0.3f));
    _percentageDisplay.setOrigin(0.5f * _percentageDisplay.getLocalBounds().width,
                                 0.5f * _percentageDisplay.getLocalBounds().height);

    _titleDisplay.setCharacterSize(static_cast<unsigned int>(_size * 0.12f));
    _titleDisplay.setOrigin(0.5f * _titleDisplay.getLocalBounds().width, 0.5f * _titleDisplay.getLocalBounds().height);

    update(); // regenerate dots
}

void Progressbar::setPercentage(float percentage)
{
    _percentage = percentage;

    const int percentageToDisplay = std::ceil(_percentage * 100);
    const std::string percentageText = std::to_string(percentageToDisplay) + "%";
    _percentageDisplay.setString(percentageText);
    _percentageDisplay.setOrigin(0.5f * _percentageDisplay.getLocalBounds().width,
                                 0.5f * _percentageDisplay.getLocalBounds().height);
}

void Progressbar::generatePoint(float i, const sf::Color &clr)
{
    static constexpr int THICKNESS = 10;

    const auto x = _pos.x + std::cos(i) * _size;
    const auto y = _pos.y + std::sin(i) * _size;

    sf::RectangleShape p;
    p.setPosition(x, y);
    p.setSize({THICKNESS, THICKNESS});
    p.setFillColor(clr);
    _points.push_back(std::move(p));
}
