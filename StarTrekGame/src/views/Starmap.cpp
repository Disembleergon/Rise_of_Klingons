#include "../../include/views/helmsman/Starmap.hpp"
#include "../../include/Starship.hpp"
#include "../../include/framework/utils/Random.hpp"
#include "../../include/framework/utils/Time.hpp"

Starmap::Starmap(sf::RenderWindow &window, Slider &throttleSider, const sf::Vector2f &pos)
    : Component(window), _throttleSlider{throttleSider},
      _galaxyBG{"./assets/galaxy.png", pos, {_starmapWidth, _starmapHeight}}, _starship{
                                                                                  "./assets/starship.png", {}, {30, 60}}
{
    generateButtons();

    // select random star system and toggle it
    const int currentSystemButtonIndex = Random::generate_integral<int>(0, SYSTEM_COUNT - 1);
    _currentSystemButton = _starmapButtons.at(currentSystemButtonIndex).get();
    _currentSystemButton->setToggled(true);

    // place starship at selected system
    _starship.setOrigin(_starship.getSize().x * 0.5f, _starship.getSize().y * 0.5f);
    _starship.setPosition(getStarshipTargetPosition());
}

void Starmap::update()
{
    // update starmap buttons
    for (starmapbutton_ptr &btn : _starmapButtons)
    {
        btn->update();
        if (btn->clicked())
        {
            btn->setToggled(true);
            _currentSystemButton = btn.get();

            // untoggle all buttons except the one that was clicked
            for (starmapbutton_ptr &b : _starmapButtons)
            {
                if (b == btn)
                    continue;
                b->setToggled(false);
            }
        }
        else
        {
            btn->toggledSinceCurrentClick = false;
        }
    }
}

void Starmap::draw()
{
    m_window.draw(_galaxyBG);

    for (starmapbutton_ptr &btn : _starmapButtons)
    {
        btn->draw();
    }

    m_window.draw(_starship);
}

void Starmap::updateStarshipPosition()
{
    sf::Vector2f starshipPos = _starship.getPosition();
    const sf::Vector2f targetPos = getStarshipTargetPosition();
    const float shipToTargetX = targetPos.x - starshipPos.x;
    const float shipToTargetY = targetPos.y - starshipPos.y;

    const auto distance = std::hypot(shipToTargetX, shipToTargetY);
    if (distance <= 1) // starship already at target
        slowDownShip();

    // move ship to target
    static constexpr float speedFactor = 0.35f;
    const float angle = std::atan2(shipToTargetY, shipToTargetX);
    starshipPos.x += std::cos(angle) * Starship::get().thrust * Time::deltaTime * speedFactor;
    starshipPos.y += std::sin(angle) * Starship::get().thrust * Time::deltaTime * speedFactor;
    _starship.setPosition(starshipPos);
}

// --- private / protected ---

sf::Vector2f Starmap::getStarshipTargetPosition()
{
    static constexpr float STARSHIP_POS_PERCENTAGE = 0.9f;

    const auto targetPosX =
        _currentSystemButton->getPosition().x + _currentSystemButton->getSize().x * STARSHIP_POS_PERCENTAGE;
    const auto targetPosY =
        _currentSystemButton->getPosition().y + _currentSystemButton->getSize().y * STARSHIP_POS_PERCENTAGE;
    return sf::Vector2f{targetPosX, targetPosY};
}

void Starmap::slowDownShip()
{
    if (_throttleSlider.value() == 0.0f)
        return;

    static constexpr float SPEED_REDUCTION = 1.5f;

    const float thrustVal = std::max(0.0f, _throttleSlider.value() - SPEED_REDUCTION * Time::deltaTime);
    _throttleSlider.setValue(thrustVal);
    Starship::get().thrust = _throttleSlider.value() * 100.0f;
}

void Starmap::generateButtons()
{
    static constexpr int BUTTON_SIZE = 75;
    static constexpr int SEED = 11011121;
    const auto galaxyPos = _galaxyBG.getPosition();

    TextureLoader::texture_ptr systemTexture = std::make_shared<sf::Texture>();
    TextureLoader::loadTexture(systemTexture, "./assets/controls/starmapButton.png");

    TextureLoader::texture_ptr toggledSystemTexture = std::make_shared<sf::Texture>();
    TextureLoader::loadTexture(toggledSystemTexture, "./assets/controls/starmapButton_toggled.png");

    // always producing the same pattern
    std::mt19937 engine{SEED};
    std::uniform_real_distribution<float> x_dist{galaxyPos.x, galaxyPos.x + _starmapWidth - BUTTON_SIZE};
    std::uniform_real_distribution<float> y_dist{galaxyPos.y, galaxyPos.y + _starmapHeight - BUTTON_SIZE};

    for (int i = 0; i < SYSTEM_COUNT; ++i)
    {
        // configure button
        starmapbutton_ptr btn = std::make_unique<ToggleButton>(m_window, systemTexture, toggledSystemTexture);
        const sf::Vector2f btnPos{x_dist(engine), y_dist(engine)};
        btn->setPosition(btnPos);
        btn->setSize({BUTTON_SIZE, BUTTON_SIZE});

        _starmapButtons.push_back(std::move(btn));
    }
}
