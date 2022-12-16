#include "../../include/views/helmsman/Starmap.hpp"
#include "../../include/Game.hpp"
#include "../../include/Globals.hpp"
#include "../../include/Starship.hpp"
#include "../../include/framework/utils/Random.hpp"
#include "../../include/framework/utils/Time.hpp"

unsigned int Starmap::StarmapButton::enemyIdCounter = 0;

Starmap::Starmap(sf::RenderWindow &window, views::Bridge &bridge, Slider &throttleSider)
    : Component(window), _throttleSlider{throttleSider}, _bridge{bridge}, _galaxyBG{"./assets/textures/galaxy.png"},
      _starship{"./assets/textures/starship.png"}, _missionIndicator{"./assets/textures/missionIndicator.png"},
      _spacestationIndicator{"./assets/textures/spacestationIndicator.png"},
      _warpSoundBuffer(std::make_unique<sf::SoundBuffer>())
{
    resources::loadResource(_warpSoundBuffer.get(), "./assets/audio/warpSound.wav");
    _warpSound.setBuffer(*_warpSoundBuffer);
    _warpSound.setLoop(true);

    constexpr auto generateSpacestationIndex = []() {
        Globals::get().SPACE_STATION_INDEX = Random::generate_integral<int>(0, Globals::get().SYSTEM_COUNT - 1);
    };

    // SPACE_STATION_INDEX = starting system (current system for now)
    generateSpacestationIndex();
    while (Globals::get().SPACE_STATION_INDEX == views::MissionView::missionQueue.front().starsystemIndex)
        generateSpacestationIndex();

    resize(m_window.getSize(), m_window.getSize());
    generateSystems();
    placeIndicator(_missionIndicator, views::MissionView::missionQueue.front().starsystemIndex);

    // select random star system and toggle it
    _currentSystemButton = _starmapButtons.at(Globals::get().SPACE_STATION_INDEX).get();
    _currentSystemButton->setToggled(true);

    _currentSystemButton->data.enemies.clear(); // no enemies in starting system
    Starship::get().currentSystemData = &_currentSystemButton->data;

    // place starship at selected system
    _starship.setOrigin(_starship.getSize().x * 0.5f, _starship.getSize().y * 0.5f);
    _starship.setPosition(getStarshipTargetPosition());
}

void Starmap::update()
{
    // update starmap buttons
    for (StarmapButton::starmapbutton_ptr &btn : _starmapButtons)
    {
        btn->update();
        if (btn->clicked())
        {
            btn->setToggled(true);
            _currentSystemButton = btn.get();

            // untoggle all buttons except the one that was clicked
            for (StarmapButton::starmapbutton_ptr &b : _starmapButtons)
            {
                if (b == btn)
                    continue;
                b->setToggled(false);
            }
        }
    }
}

void Starmap::draw()
{
    m_window.draw(_galaxyBG);

    for (StarmapButton::starmapbutton_ptr &btn : _starmapButtons)
    {
        btn->draw();
    }

    m_window.draw(_missionIndicator);
    m_window.draw(_spacestationIndicator);
    m_window.draw(_starship);
}

void Starmap::resize(const sf::Vector2u &prevWindowSize, const sf::Vector2u &newWindowSize)
{
    _starmapWidth = newWindowSize.x * 0.56f;
    _starmapHeight = newWindowSize.y * 0.69f;

    const sf::Vector2f prevStarmapSize{_starmapWidth, _starmapHeight};
    _galaxyBG.setPosition(newWindowSize.x * 0.36f, newWindowSize.y * 0.14f);
    _galaxyBG.setSize({_starmapWidth, _starmapHeight});

    _starship.setSize({newWindowSize.x * 0.02f, newWindowSize.y * 0.05f});
    _starship.setOrigin(0.5f * _starship.getSize());

    const sf::Vector2f indicatorSize = {newWindowSize.x * 0.015f, newWindowSize.y * 0.02f};
    _missionIndicator.setSize(indicatorSize);
    _missionIndicator.setOrigin(0.5f * indicatorSize);
    _spacestationIndicator.setSize(indicatorSize);
    _spacestationIndicator.setOrigin(0.5f * indicatorSize);

    placeIndicator(_spacestationIndicator, Globals::get().SPACE_STATION_INDEX);
    placeIndicator(_missionIndicator, views::MissionView::missionQueue.front().starsystemIndex);

    configureButtons();

    if (_currentSystemButton)
        _starship.setPosition(getStarshipTargetPosition());
}

static constexpr float MIN_PITCH_WARPSOUND = 0.5f;

void Starmap::updateStarshipPosition()
{
    sf::Vector2f starshipPos = _starship.getPosition();
    const sf::Vector2f targetPos = getStarshipTargetPosition();
    const float shipToTargetX = targetPos.x - starshipPos.x;
    const float shipToTargetY = targetPos.y - starshipPos.y;

    const auto distance = std::hypot(shipToTargetX, shipToTargetY);
    if (distance <= 1) // starship already at target
    {
        slowDownShip();
    }
    else if (_throttleSlider.value() > 0)
    {
        _bridge.clearGalaxyWindow();
        Starship::get().currentSystemData = nullptr;

        if (_warpSound.getStatus() != sf::SoundSource::Playing)
            _warpSound.play();

        _warpSound.setPitch(MIN_PITCH_WARPSOUND + _throttleSlider.value());
    }

    // move ship to target
    static constexpr float speedFactor = 0.35f;
    const float angle = std::atan2(shipToTargetY, shipToTargetX);
    starshipPos.x += std::cos(angle) * Starship::get().thrust * Time::deltaTime * speedFactor;
    starshipPos.y += std::sin(angle) * Starship::get().thrust * Time::deltaTime * speedFactor;
    _starship.setPosition(starshipPos);
}

void Starmap::placeIndicator(GameSprite &indicator, int systemIndex)
{
    if (views::MissionView::missionQueue.size() == 0 || _starmapButtons.size() == 0)
        return;

    const StarmapButton *system = _starmapButtons.at(systemIndex).get();
    const sf::Vector2f systemPos = system->getPosition();
    const sf::Vector2f systemSize = system->getSize();
    indicator.setPosition(systemPos.x + systemSize.x * 0.1f, systemPos.y + systemSize.y * 0.9f);
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
    {
        Starship::get().currentSystemData = &_currentSystemButton->data;
        _bridge.onSystemArrival();

        _warpSound.setPitch(1.0f);
        _warpSound.stop();

        return;
    }
    _warpSound.setPitch(MIN_PITCH_WARPSOUND + _throttleSlider.value());

    static constexpr float SPEED_REDUCTION = 1.5f;
    const float thrustVal = std::max(0.0f, _throttleSlider.value() - SPEED_REDUCTION * Time::deltaTime);
    _throttleSlider.setValue(thrustVal);
    Starship::get().thrust = _throttleSlider.value() * MAX_THRUST;
}

void Starmap::configureButtons()
{
    const sf::Vector2f galaxyPos = _galaxyBG.getPosition();
    const auto buttonSize = m_window.getSize().x * 0.04f;

    // always producing the same pattern
    static constexpr int SEED = 11011121;
    std::mt19937 engine{SEED};
    std::uniform_real_distribution<float> x_dist{galaxyPos.x, galaxyPos.x + _starmapWidth - buttonSize};
    std::uniform_real_distribution<float> y_dist{galaxyPos.y, galaxyPos.y + _starmapHeight - buttonSize};

    for (StarmapButton::starmapbutton_ptr &btn : _starmapButtons)
    {
        const sf::Vector2f btnPos{x_dist(engine), y_dist(engine)};
        btn->setPosition(btnPos);
        btn->setSize({buttonSize, buttonSize});
    }
}

void Starmap::generateSystems()
{
    resources::shared_texture_ptr systemTexture = std::make_shared<sf::Texture>();
    resources::loadResource<sf::Texture>(systemTexture.get(), "./assets/textures/controls/starmapButton.png");

    resources::shared_texture_ptr toggledSystemTexture = std::make_shared<sf::Texture>();
    resources::loadResource<sf::Texture>(toggledSystemTexture.get(),
                                         "./assets/textures/controls/starmapButton_toggled.png");

    for (int i = 0; i < Globals::get().SYSTEM_COUNT; ++i)
    {
        StarmapButton::starmapbutton_ptr btn =
            std::make_unique<StarmapButton>(m_window, systemTexture, toggledSystemTexture);
        btn->data.systemIndex = i;
        _starmapButtons.push_back(std::move(btn));
    }

    configureButtons();
}
