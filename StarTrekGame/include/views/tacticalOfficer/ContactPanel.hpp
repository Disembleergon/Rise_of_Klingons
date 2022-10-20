#ifndef CONTACTPANEL_HPP
#define CONTACTPANEL_HPP

#include "../../framework/Component.hpp"

class ContactPanel final : public Component
{
  public:
    ContactPanel(sf::RenderWindow &);

    void update() override;
    void draw() override;
    void resize(const sf::Vector2u &prevWindowSize, const sf::Vector2u &newWindowSize) override;

  private:
    sf::RectangleShape _panel;
};

#endif
