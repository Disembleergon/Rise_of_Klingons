#include "../../include/framework/gui/Progressbar.hpp"
#include <numbers>

Progressbar::Progressbar(sf::RenderWindow &window, const sf::Vector2f &pos, int size, resources::shared_font_ptr &font)
    : Component(window), _pos{pos}, _size{size}, _points{sf::PrimitiveType::LineStrip}, _font{font}
{
    _percentageDisplay.setFont(*_font);
    _percentageDisplay.setCharacterSize(static_cast<unsigned int>(size * 0.3f));
    _percentageDisplay.setPosition(pos);
    setPercentage(0.0f);
}

void Progressbar::update()
{
    _points.clear();

    static constexpr int THICKNESS = 10;
    static constexpr float INCREMENT = 0.1f;
    static constexpr float OVERLAP = 0.55f;
    const sf::Color COLOR{48, 187, 242};

    static constexpr float START = std::numbers::pi_v<float> - OVERLAP;
    static constexpr float END = std::numbers::pi_v<float> + OVERLAP * 2.0f;

    for (float i = START; i < START + (END * _percentage); i += INCREMENT)
    {
        const auto x = _pos.x + std::cos(i) * _size;
        const auto y = _pos.y + std::sin(i) * _size;

        sf::RectangleShape p;
        p.setPosition(x, y);
        p.setSize({THICKNESS, THICKNESS});
        p.setFillColor(COLOR);
        _points.push_back(std::move(p));
    }
}

void Progressbar::draw()
{
    for (sf::RectangleShape &p : _points)
        m_window.draw(p);

    m_window.draw(_percentageDisplay);
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
