#include "../../include/views/tacticalOfficer/ContactPanel.hpp"
#include "../../include/Globals.hpp"

ContactPanel::ContactPanel(sf::RenderWindow &window)
    : Component(window), _stationRefillAmmoButton(window), _stationRepairHullButton(window),
      _stationRepresentation("./assets/textures/spacestation_blue.png")
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
    resources::loadResource<sf::Texture>(btnTexture.get(), "./assets/textures/missionUIElement.png");

    _titledBtnConig.title = "Refill Ammo";
    _stationRefillAmmoButton.configure(_titledBtnConig);
    _stationRefillAmmoButton.setNewTexture(btnTexture);

    _titledBtnConig.title = "Repair Hull";
    _stationRepairHullButton.configure(_titledBtnConig);
    _stationRepairHullButton.setNewTexture(btnTexture);

    resize(m_window.getSize(), m_window.getSize());
}

void ContactPanel::update()
{
    using enum ContactMode;
    switch (_currentMode)
    {
    case STATION:
        _stationRefillAmmoButton.update();
        _stationRepairHullButton.update();
        break;
    }
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
    }
}

void ContactPanel::resize(const sf::Vector2u &prevWindowSize, const sf::Vector2u &newWindowSize)
{
    _panel.setOutlineThickness(newWindowSize.x * 0.005f);
    _panel.setPosition(newWindowSize.x * 0.09f, newWindowSize.y * 0.2f);
    _panel.setSize({newWindowSize.x * 0.39f, newWindowSize.y * 0.45f});

    _title.setCharacterSize(_panel.getSize().y * 0.05f);
    configureTitle();
    _title.setPosition(newWindowSize.x * 0.28f, newWindowSize.y * 0.24f);

    _stationRefillAmmoButton.setPosition(newWindowSize.x * 0.11f, newWindowSize.y * 0.29f);
    _stationRefillAmmoButton.setSize({newWindowSize.x * 0.35f, newWindowSize.y * 0.05f});
    _stationRefillAmmoButton.resize(prevWindowSize, newWindowSize);

    _stationRepairHullButton.setPosition(newWindowSize.x * 0.11f, newWindowSize.y * 0.36f);
    _stationRepairHullButton.setSize({newWindowSize.x * 0.35f, newWindowSize.y * 0.05f});
    _stationRepairHullButton.resize(prevWindowSize, newWindowSize);

    _stationRepresentation.setSize({newWindowSize.x * 0.12f, newWindowSize.y * 0.18f});
    _stationRepresentation.setOrigin(_stationRepresentation.getLocalBounds().width * 0.5f,
                                     _stationRepresentation.getLocalBounds().height * 0.5f);
    _stationRepresentation.setPosition(newWindowSize.x * 0.275f, newWindowSize.y * 0.53f);
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
