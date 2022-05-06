#ifndef HELMSMAN_HPP
#define HELMSMAN_HPP

#include "../Clickables.hpp"
#include "../Component.hpp"
#include "../GameSprite.hpp"

namespace views
{

class Helmsman final : public Component
{
  public:
    Helmsman(sf::RenderWindow &);

    void update() override;
    void draw() override;

  private:
    const GameSprite _panel;
    Clickable _returnButton;
};

} // namespace views

#endif
