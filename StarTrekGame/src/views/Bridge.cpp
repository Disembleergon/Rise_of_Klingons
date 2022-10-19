#include "../../include/views/bridge/Bridge.hpp"
#include "../../include/Game.hpp"
#include "../../include/framework/utils/Time.hpp"

views::Bridge::Bridge(sf::RenderWindow &window)
    : Component(window), _bg{"./assets/textures/bridge.png"}, _helmsman{m_window}, _tacticalOfficer{m_window},
      _galaxyWindow{window}, _missionComputerButton{m_window}
{
    _helmsman.setNewTexture("./assets/textures/helmsman.png");
    _tacticalOfficer.setNewTexture("./assets/textures/tacticalOfficer.png");
    _missionComputerButton.setNewTexture("./assets/textures/controls/missionComputerButton.png");

    _prevSystemIndex = Starship::get().currentSystemData->systemIndex;
    addSpacestation(); // first system always has one
    resize(m_window.getSize(), m_window.getSize());
}

void views::Bridge::update()
{
    _helmsman.update();
    _tacticalOfficer.update();
    _missionComputerButton.update();
    _galaxyWindow.update();

    if (_helmsman.clicked())
    {
        Game::currentView = View::HELMSMAN;
    }
    else if (_tacticalOfficer.clicked())
    {
        Game::currentView = View::TACTICAL_OFFICER;
    }
    else if (_missionComputerButton.clicked())
    {
        Game::currentView = View::MISSION_VIEW;
    }

    // "flying" animation around the fixed position
    for (EnemyShip &enemy : _enemies)
    {
        const auto fixedPos = enemy.getFixedPosition();
        const float x = fixedPos.x + std::sin(enemy.moveProgress.x) * EnemyShip::moveFactor;
        const float y = fixedPos.y + std::sin(enemy.moveProgress.y) * EnemyShip::moveFactor;
        enemy.setPosition(x, y);

        const auto increment = EnemyShip::moveIncrement * Time::deltaTime;
        enemy.moveProgress.x += increment;
        enemy.moveProgress.y += increment;
    }
}

void views::Bridge::draw()
{
    _galaxyWindow.draw();

    if (_spacestation.has_value())
        m_window.draw(_spacestation.value());

    for (const EnemyShip &enemy : _enemies)
        m_window.draw(enemy);

    m_window.draw(_bg);
    _helmsman.draw();
    _tacticalOfficer.draw();
    _missionComputerButton.draw();
}

void views::Bridge::resize(const sf::Vector2u &prevWindowSize, const sf::Vector2u &newWindowSize)
{
    const sf::Vector2f crewmemberSize{newWindowSize.x * 0.11f, newWindowSize.y * 0.46f};
    const auto crewMemberY = newWindowSize.y * 0.45f;

    _helmsman.setPosition(newWindowSize.x * 0.18f, crewMemberY);
    _helmsman.setSize(crewmemberSize);
    _tacticalOfficer.setPosition(newWindowSize.x * 0.71f, crewMemberY);
    _tacticalOfficer.setSize(crewmemberSize);

    _missionComputerButton.setPosition(newWindowSize.x * 0.476f, newWindowSize.y * 0.65f);
    _missionComputerButton.setSize({newWindowSize.x * 0.055f, newWindowSize.y * 0.07f});

    // for resizing the enemy ships
    const sf::Vector2f prevGalaxywindowSize = _galaxyWindow.windowSize;
    const sf::Vector2f prevGalaxywindowPos = _galaxyWindow.windowPos;

    _bg.setSize(static_cast<sf::Vector2f>(newWindowSize));
    _galaxyWindow.resize(prevWindowSize, newWindowSize);

    // for resizing the enemy ships (as well)
    const sf::Vector2f newGalaxywindowSize = _galaxyWindow.windowSize;
    const sf::Vector2f newGalaxywindowPos = _galaxyWindow.windowPos;

    if (_spacestation.has_value())
    {
        const auto stationPos = _spacestation.value().getPosition();
        const sf::Vector2f relPos = {(stationPos.x - prevGalaxywindowPos.x) / prevGalaxywindowSize.x,
                                     ((stationPos.y - prevGalaxywindowPos.y) / prevGalaxywindowSize.y)};
        _spacestation.value().setPosition(newGalaxywindowPos.x + newGalaxywindowSize.x * relPos.x,
                                          newGalaxywindowPos.y + newGalaxywindowSize.y * relPos.y);
        _spacestation.value().setSize(
            {newWindowSize.x * _spacestationSizeFactor.x, newWindowSize.y * _spacestationSizeFactor.y});
    }

    for (EnemyShip &enemy : _enemies)
    {
        const sf::Vector2f enemyFixedPos = enemy.getFixedPosition();
        const sf::Vector2f enemySize = enemy.getSize();

        const sf::Vector2f relPos{(enemyFixedPos.x - prevGalaxywindowPos.x) / prevGalaxywindowSize.x,
                                  (enemyFixedPos.y - prevGalaxywindowPos.y) / prevGalaxywindowSize.y};
        const sf::Vector2f relSize{enemySize.x / prevWindowSize.x, enemySize.y / prevWindowSize.y};
        enemy.setFixedPosition(newGalaxywindowPos.x + newGalaxywindowSize.x * relPos.x,
                               newGalaxywindowPos.y + newGalaxywindowSize.y * relPos.y);
        enemy.setSize({newWindowSize.x * relSize.x, newWindowSize.y * relSize.y});
    }
}

void views::Bridge::onSystemArrival()
{
    const SystemData *currentSystemData = Starship::get().currentSystemData;
    if (_prevSystemIndex == currentSystemData->systemIndex && _enemies.size() == currentSystemData->enemies.size())
        return; // regeneration already happened

    _prevSystemIndex = currentSystemData->systemIndex;

    if (currentSystemData->systemIndex == Globals::get().SPACE_STATION_INDEX)
        addSpacestation();

    // ---- generate new ships ----
    _enemies.clear();
    resources::shared_texture_ptr enemyTexture = std::make_shared<sf::Texture>();
    resources::loadResource<sf::Texture>(enemyTexture.get(), "./assets/textures/enemy.png");

    const auto windowPos = _galaxyWindow.windowPos;
    const auto windowSize = _galaxyWindow.windowSize;

    for (int i = 0; i < currentSystemData->enemies.size(); ++i)
    {
        const auto enemyWidth = Random::generate_floating_point(windowSize.x * 0.05f, windowSize.x * 0.6f);
        const auto enemyHeight = enemyWidth * 0.58f; // apply aspect ratio
        const float enemyX =
            windowPos.x + enemyWidth * 0.5f + (windowSize.x - enemyWidth) * Random::generate_floating_point(0.0f, 1.0f);
        const float enemyY = windowPos.y + enemyHeight * 0.5f +
                             (windowSize.y - enemyHeight) * Random::generate_floating_point(0.0f, 1.0f);

        EnemyShip enemy;
        enemy.setSize({enemyWidth, enemyHeight});
        enemy.setOrigin({enemy.getLocalBounds().width * 0.5f, enemy.getLocalBounds().height * 0.5f});
        enemy.setFixedPosition(enemyX, enemyY);
        enemy.moveProgress.x = Random::generate_floating_point(0.0f, 2.0f);
        enemy.moveProgress.y = Random::generate_floating_point(0.0f, 2.0f);
        enemy.setNewTexture(enemyTexture);

        _enemies.push_back(std::move(enemy));
    }
}

void views::Bridge::clearGalaxyWindow()
{
    _prevSystemIndex = -1; // when stopping anywhere and returning to the same system
    _enemies.clear();
    _spacestation.reset();
}

void views::Bridge::addSpacestation()
{
    GameSprite station{"./assets/textures/spacestation.png"};

    _spacestationSizeFactor.x = Random::generate_floating_point(0.1f, 0.2f);
    _spacestationSizeFactor.y = _spacestationSizeFactor.x * 2;

    const auto windowSize = _galaxyWindow.windowSize;
    const auto windowPos = _galaxyWindow.windowPos;
    const sf::Vector2f size = {windowSize.x * _spacestationSizeFactor.x, windowSize.y * _spacestationSizeFactor.y};

    const float x = windowPos.x + size.x * 0.5f + (windowSize.x - size.x) * Random::generate_floating_point(0.0f, 1.0f);
    const float y = windowPos.y + size.y * 0.5f + (windowSize.y - size.y) * Random::generate_floating_point(0.0f, 1.0f);

    station.setSize(size);
    station.setOrigin({station.getLocalBounds().width * 0.5f, station.getLocalBounds().height * 0.5f});
    station.setPosition(x, y);
    _spacestation = station;

    resize(m_window.getSize(), m_window.getSize()); // quick fix for weirdly stretched station when arriving
}
