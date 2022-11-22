#include "../../include/views/tacticalOfficer/ContactPanel.hpp"
#include "../../include/Globals.hpp"
#include "../../include/Starship.hpp"
#include "../../include/framework/utils/Time.hpp"
#include "../../include/views/tacticalOfficer/AttackPanel.hpp"

ContactPanel::ContactPanel(sf::RenderWindow &window)
    : Component(window), _stationRefillAmmoButton(window), _stationRepairHullButton(window),
      _stationRepresentation("./assets/textures/spacestation_blue.png"), _enemyShieldHackButton(window),
      _enemyWeaponHackButton(window),
      _enemyRepresentation("./assets/textures/enemy_top_blue.png"), _hackingProgressCircle{window, 190u}
{
    const sf::Color BLUE{99, 155, 255};
    _panel.setFillColor(sf::Color{203, 219, 252});
    _panel.setOutlineColor(BLUE);

    _title.setFont(*Globals::get().FONT);
    _title.setFillColor(BLUE);

    // ---- config buttons ----

    TitledClickable::Config _titledBtnConig;
    _titledBtnConig.color = sf::Color::White;
    _titledBtnConig.font = Globals::get().FONT;

    resources::shared_texture_ptr btnTexture = std::make_shared<sf::Texture>();
    resources::loadResource<sf::Texture>(btnTexture.get(), "./assets/textures/textBar.png");
    //
    _titledBtnConig.title = "Refill Ammo";
    _stationRefillAmmoButton.configure(_titledBtnConig);
    _stationRefillAmmoButton.setNewTexture(btnTexture);

    _titledBtnConig.title = "Repair Hull";
    _stationRepairHullButton.configure(_titledBtnConig);
    _stationRepairHullButton.setNewTexture(btnTexture);
    //
    _titledBtnConig.title = "Disable Shields";
    _enemyShieldHackButton.configure(_titledBtnConig);
    _enemyShieldHackButton.setNewTexture(btnTexture);

    _titledBtnConig.title = "Interrupt Weapons";
    _enemyWeaponHackButton.configure(_titledBtnConig);
    _enemyWeaponHackButton.setNewTexture(btnTexture);
    // ----

    progress::Config progressBarConfig;
    progressBarConfig.title = "";
    progressBarConfig.font = nullptr;
    progressBarConfig.color = BLUE;
    _hackingProgressCircle.configure(progressBarConfig);
    _hackingProgressCircle.showPercentage(false);

    resize(m_window.getSize(), m_window.getSize());
}

void ContactPanel::update()
{
    using enum ContactMode;

    // ---- update mode ----
    SystemData *currentSystemData = Starship::get().currentSystemData;
    _currentMode = NONE;

    if (currentSystemData)
    {
        if (AttackPanel::selectedEnemy)
            _currentMode = ENEMY;
        else if (currentSystemData->systemIndex == Globals::get().SPACE_STATION_INDEX)
            _currentMode = STATION;
    }
    // ---

    switch (_currentMode)
    {
    case STATION:
        _stationRefillAmmoButton.update();
        _stationRepairHullButton.update();

        if (_stationRefillAmmoButton.clicked())
        {
            Starship::get().phaserAmmo = MAX_PHASER_AMMO;
            Starship::get().torpedoAmmo = MAX_TORPEDO_AMMO;
        }
        else if (_stationRepairHullButton.clicked())
        {
            Starship::get().hull = MAX_HULL;
        }
        break;
    case ENEMY:
        _enemyShieldHackButton.update();
        _enemyWeaponHackButton.update();

        if (_enemyShieldHackButton.clicked() && !Starship::get().enemyToGetHacked)
        {
            Starship::get().enemyToGetHacked = AttackPanel::selectedEnemy;
        }
        break;
    }

    if (Starship::get().enemyToGetHacked)
        hackEnemyShield();
    else
        _hackingProgress = 0.0f;

    configureTitle();
}

void ContactPanel::draw()
{
    m_window.draw(_panel);

    using enum ContactMode;
    switch (_currentMode)
    {
    case STATION:
        m_window.draw(_title);
        _stationRefillAmmoButton.draw();
        _stationRepairHullButton.draw();
        m_window.draw(_stationRepresentation);
        break;
    case ENEMY:
        m_window.draw(_title);
        _enemyShieldHackButton.draw();
        _enemyWeaponHackButton.draw();
        m_window.draw(_enemyRepresentation);
        _hackingProgressCircle.draw();
        break;
    }
}

void ContactPanel::resize(const sf::Vector2u &prevWindowSize, const sf::Vector2u &newWindowSize)
{
    auto prevPanelSize = _panel.getSize(); // for _hackingProgressBar
    _panel.setOutlineThickness(newWindowSize.x * 0.005f);
    _panel.setPosition(newWindowSize.x * 0.09f, newWindowSize.y * 0.2f);
    _panel.setSize({newWindowSize.x * 0.39f, newWindowSize.y * 0.45f});

    // first time always 0
    if (prevPanelSize.x == 0.0f)
        prevPanelSize = _panel.getSize();

    _title.setCharacterSize(_panel.getSize().y * 0.05f);
    configureTitle();
    _title.setPosition(newWindowSize.x * 0.28f, newWindowSize.y * 0.24f);

    _stationRefillAmmoButton.setPosition(newWindowSize.x * 0.11f, newWindowSize.y * 0.29f);
    _stationRefillAmmoButton.setSize({newWindowSize.x * 0.35f, newWindowSize.y * 0.05f});
    _stationRefillAmmoButton.resize(prevWindowSize, newWindowSize);

    _stationRepairHullButton.setPosition(newWindowSize.x * 0.11f, newWindowSize.y * 0.36f);
    _stationRepairHullButton.setSize({newWindowSize.x * 0.35f, newWindowSize.y * 0.05f});
    _stationRepairHullButton.resize(prevWindowSize, newWindowSize);

    _stationRepresentation.setSize({newWindowSize.x * 0.10f, newWindowSize.y * 0.18f});
    _stationRepresentation.setOrigin(_stationRepresentation.getLocalBounds().width * 0.5f,
                                     _stationRepresentation.getLocalBounds().height * 0.5f);
    _stationRepresentation.setPosition(newWindowSize.x * 0.275f, newWindowSize.y * 0.53f);

    // -----

    _enemyShieldHackButton.setPosition(newWindowSize.x * 0.11f, newWindowSize.y * 0.29f);
    _enemyShieldHackButton.setSize({newWindowSize.x * 0.35f, newWindowSize.y * 0.05f});
    _enemyShieldHackButton.resize(prevWindowSize, newWindowSize);

    _enemyWeaponHackButton.setPosition(newWindowSize.x * 0.11f, newWindowSize.y * 0.36f);
    _enemyWeaponHackButton.setSize({newWindowSize.x * 0.35f, newWindowSize.y * 0.05f});
    _enemyWeaponHackButton.resize(prevWindowSize, newWindowSize);

    _enemyRepresentation.setSize({newWindowSize.x * 0.13f, newWindowSize.y * 0.13f});
    _enemyRepresentation.setOrigin(_stationRepresentation.getLocalBounds().width * 0.5f,
                                   _stationRepresentation.getLocalBounds().height * 0.5f);
    _enemyRepresentation.setPosition(newWindowSize.x * 0.262f, newWindowSize.y * 0.56f);

    _hackingProgressCircle.setPos({newWindowSize.x * 0.275f, newWindowSize.y * 0.54f});
    _hackingProgressCircle.resize(prevPanelSize.x, _panel.getSize().x);
}

void ContactPanel::hackEnemyShield()
{
    static constexpr float HACKING_DURATION = 15.0f;
    _hackingProgress += Time::deltaTime;

    if (!AttackPanel::selectedEnemy)
    {
        Starship::get().enemyToGetHacked = nullptr;
        _hackingProgress = 0.0f;
        updateHackingProgressBar(0.0f);
    }
    else if (Starship::get().enemyToGetHacked->data == AttackPanel::selectedEnemy->data)
    {
        updateHackingProgressBar(_hackingProgress / HACKING_DURATION);
    }
    else
    {
        // current view isnt the one that gets hacked... dont show progress
        updateHackingProgressBar(0.0f);
    }

    if (_hackingProgress < HACKING_DURATION)
        return;

    Starship::get().enemyToGetHacked->data.shield = 0.0f;
    Starship::get().enemyToGetHacked = nullptr;
    _hackingProgress = 0.0f;

    updateHackingProgressBar(0.0f);
}

void ContactPanel::updateHackingProgressBar(float percentage)
{
    _hackingProgressCircle.setPercentage(percentage);
    _hackingProgressCircle.update();
}

void ContactPanel::configureTitle()
{
    sf::String title;
    using enum ContactMode;
    switch (_currentMode)
    {
    case STATION:
        title = "Space Station";
        break;
    case ENEMY:
        title = "Selected Enemy";
    }

    _title.setString(title);
    _title.setOrigin(_title.getLocalBounds().width * 0.5f, _title.getLocalBounds().height * 0.5f);
}
