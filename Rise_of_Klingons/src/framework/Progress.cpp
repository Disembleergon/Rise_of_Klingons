#include "../../include/framework/gui/Progress.hpp"
#include <numbers>

static constexpr int GREYVALUE = 40;
static constexpr int GREYTEXTVALUE = GREYVALUE + 100;

/////////////////////////////////////////////////////////////

progress::ProgressCircle::ProgressCircle(sf::RenderWindow &window, unsigned int size) : Component(window), _size{size}
{
    _percentageDisplay.setFillColor(sf::Color{GREYTEXTVALUE});
    setPercentage(0.0f);

    _titleDisplay.setFillColor(sf::Color{GREYTEXTVALUE});
}

void progress::ProgressCircle::update()
{
    // text
    if (_showPercentage)
    {
        const int percentageToDisplay = std::ceil(_percentage * 100);
        const std::string percentageText = std::to_string(percentageToDisplay) + "%";
        _percentageDisplay.setString(percentageText);
        _percentageDisplay.setOrigin(0.5f * _percentageDisplay.getLocalBounds().width,
                                     0.5f * _percentageDisplay.getLocalBounds().height);
    }

    // indicator points
    _points.clear();

    static constexpr float INCREMENT = 0.1f;
    static constexpr float OVERLAP = 0.55f;
    static constexpr float START = std::numbers::pi_v<float> - OVERLAP;
    static constexpr float END = std::numbers::pi_v<float> + OVERLAP * 2.0f;

    // blue part
    for (float i = START; i < START + (END * _percentage); i += INCREMENT)
        generatePoint(i, _clr);

    // grey part
    // (ceil * 10 / 10 ...... round to 1 decimal place)
    for (float i = START + std::ceil(END * _percentage * 10) / 10; i < START + END; i += INCREMENT)
        generatePoint(i, sf::Color{GREYVALUE});
}

void progress::ProgressCircle::draw()
{
    for (sf::RectangleShape &p : _points)
        m_window.draw(p);

    if (_showPercentage)
        m_window.draw(_percentageDisplay);

    m_window.draw(_titleDisplay);
}

void progress::ProgressCircle::resize(float prevOrientationValue, float newOrientationValue)
{
    const auto relSize = _size / prevOrientationValue;
    _size = relSize * newOrientationValue;

    _percentageDisplay.setCharacterSize(static_cast<unsigned int>(_size * 0.3f));
    _percentageDisplay.setOrigin(0.5f * _percentageDisplay.getLocalBounds().width,
                                 0.5f * _percentageDisplay.getLocalBounds().height);

    _titleDisplay.setCharacterSize(static_cast<unsigned int>(_size * 0.12f));
    _titleDisplay.setOrigin(0.5f * _titleDisplay.getLocalBounds().width, 0.5f * _titleDisplay.getLocalBounds().height);

    update(); // regenerate dots
}

void progress::ProgressCircle::generatePoint(float i, const sf::Color &clr)
{
    const float THICKNESS = _size * 0.06f;

    const auto x = _pos.x + std::cos(i) * _size;
    const auto y = _pos.y + std::sin(i) * _size;

    sf::RectangleShape p;
    p.setPosition(x, y);
    p.setSize({THICKNESS, THICKNESS});
    p.setFillColor(clr);
    _points.push_back(std::move(p));
}

/////////////////////////////////////////////////////////

progress::ProgressBar::ProgressBar(sf::RenderWindow &window) : Component(window)
{
    // only border
    _progressOverlay.setFillColor(sf::Color::Transparent);
    _progressOverlay.setOutlineThickness(10);
    _progressOverlay.setOutlineColor(sf::Color{GREYVALUE});

    _titleDisplay.setFillColor(sf::Color{GREYTEXTVALUE});
}

void progress::ProgressBar::update()
{
    const sf::Vector2f progressbarSize = _progressOverlay.getSize();
    const auto indicatorWidth = _percentage * progressbarSize.x;
    _progressIndicator.setSize({indicatorWidth, progressbarSize.y});
}

void progress::ProgressBar::draw()
{
    m_window.draw(_progressIndicator);
    m_window.draw(_progressOverlay);
    m_window.draw(_titleDisplay);
}
