#include "../../include/views/bridge/GalaxyWindow.hpp"
#include "../../include/Starship.hpp"
#include "../../include/framework/utils/Random.hpp"
#include "../../include/framework/utils/Time.hpp"
#include <numbers>

galaxywindow::GalaxyWindow::GalaxyWindow(sf::RenderWindow &window) : Component(window)
{
    resize(m_window.getSize(), m_window.getSize());
    generateStars();
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
        star->setSize({2 * Starship::get().thrust + 5, 1}); // {length, width}

        // fade-in effect on spawn
        sf::Color starClr = star->getFillColor();
        starClr.a = std::min(starClr.a + 2, 255);
        star->setFillColor(starClr);

        // erase stars out of sight
        const bool outOfSight = starPos.x < windowPos.x || starPos.x > windowPos.x + windowSize.x ||
                                starPos.y < windowPos.y || starPos.y > windowPos.y + windowSize.y;
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
}
void galaxywindow::GalaxyWindow::resize(const sf::Vector2u &prevWindowSize, const sf::Vector2u &newWindowSize)
{
    windowPos = {newWindowSize.x * 0.1f, newWindowSize.y * 0.07f};
    windowSize = {newWindowSize.x * 0.81f, newWindowSize.y * 0.48f};
    _windowCenter = {windowPos.x + windowSize.x * 0.5f, windowPos.y + windowSize.y * 0.5f};

    _stars.clear();
    generateStars();
};

// ---- private/protected ----

void galaxywindow::GalaxyWindow::generateStars()
{
    for (int i = 0; i < NUM_STARS; ++i)
    {
        const auto starX = Random::generate_floating_point(windowPos.x, windowPos.x + windowSize.x);
        const auto starY = Random::generate_floating_point(windowPos.y, windowPos.y + windowSize.y);
        generateNewStar(starX, starY);
    }
}

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
