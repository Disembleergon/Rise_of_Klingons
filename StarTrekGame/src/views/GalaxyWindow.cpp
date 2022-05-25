#include "../../include/views/bridge/GalaxyWindow.hpp"
#include "../../include/Starship.hpp"
#include "../../include/framework/utils/Random.hpp"
#include "../../include/framework/utils/Time.hpp"
#include <numbers>

galaxywindow::GalaxyWindow::GalaxyWindow(sf::RenderWindow &window, const sf::Vector2f &windowPos,
                                         const sf::Vector2f &windowSize)
    : Component(window), _windowPos{windowPos}, _windowSize{windowSize}, _windowCenter{windowPos.x + windowSize.x / 2,
                                                                                       windowPos.y + windowSize.y / 2}
{
    // -- random stars at first --
    for (int i = 0; i < NUM_STARS; ++i)
    {
        const auto starX = Random::generate_floating_point(_windowPos.x, _windowPos.x + _windowSize.x);
        const auto starY = Random::generate_floating_point(_windowPos.y, _windowPos.y + _windowSize.y);
        generateNewStar(starX, starY);
    }
}

void galaxywindow::GalaxyWindow::update()
{
    const float shipSpeed = Starship::get().thrust;

    // iterating over every star
    for (int i = 0; i < _stars.size();)
    {
        Star *star = _stars.at(i).get();
        sf::Vector2f starPos = star->getPosition();

        // update star's position and size
        starPos.x += star->direction().x * shipSpeed * Time::deltaTime;
        starPos.y += star->direction().y * shipSpeed * Time::deltaTime;
        star->setPosition(starPos);
        star->setSize({2 * Starship::get().thrust + 5, 0.01f * Starship::get().thrust + 5});

        // fade-in effect on spawn
        sf::Color starClr = star->getFillColor();
        starClr.a = std::min(starClr.a + 2, 255);
        star->setFillColor(starClr);

        // erase stars out of sight
        const bool outOfSight = starPos.x < _windowPos.x || starPos.x > _windowPos.x + _windowSize.x ||
                                starPos.y < _windowPos.y || starPos.y > _windowPos.y + _windowSize.y;
        if (outOfSight)
            _stars.erase(_stars.begin() + i);
        else
            ++i;
    };

    if (_stars.size() < NUM_STARS)
    {
        // random offset for direction
        generateNewStar(_windowCenter.x + Random::generate_floating_point<float>(-5, 5),
                        _windowCenter.y + Random::generate_floating_point<float>(-5, 5));
    }
}

void galaxywindow::GalaxyWindow::draw()
{
    for (const Star::star_ptr &star : _stars)
        m_window.draw(*star);
};

// ---- private/protected ----

void galaxywindow::GalaxyWindow::generateNewStar(float starX, float starY)
{
    const float directionAngle = std::atan2f(starY - _windowCenter.y, starX - _windowCenter.x);
    const float deltaX = std::cos(directionAngle);
    const float deltaY = std::sin(directionAngle);

    Star::star_ptr star = std::make_unique<Star>(sf::Vector2f{deltaX, deltaY});
    star->setPosition(starX, starY);
    star->setRotation(directionAngle * (180 / std::numbers::pi));
    _stars.push_back(std::move(star));
}
