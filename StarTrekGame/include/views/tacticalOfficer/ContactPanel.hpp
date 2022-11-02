#ifndef CONTACTPANEL_HPP
#define CONTACTPANEL_HPP

#include "../../framework/Component.hpp"
#include "../../framework/gui/Clickables.hpp"

class ContactPanel final : public Component
{
    enum class ContactMode
    {
        STATION,
        ENEMY,
        NONE
    };
    ContactMode _currentMode{ContactMode::STATION};

  public:
    ContactPanel(sf::RenderWindow &);

    void update() override;
    void draw() override;
    void resize(const sf::Vector2u &prevWindowSize, const sf::Vector2u &newWindowSize) override;

  protected:
    void configureTitle();

  private:
    sf::RectangleShape _panel;

    sf::Text _title;
    TitledClickable _stationRefillAmmoButton;
    TitledClickable _stationRepairHullButton;
    GameSprite _stationRepresentation;
};

#endif
