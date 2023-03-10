#ifndef BRIDGE_HPP
#define BRIDGE_HPP

#include "../../Starship.hpp"
#include "../../framework/Component.hpp"
#include "../../framework/GameSprite.hpp"
#include "../../framework/gui/Clickables.hpp"
#include "GalaxyWindow.hpp"

#include <optional>

namespace views
{
class Bridge final : public Component
{
    class EnemyShip final : public sf::RectangleShape
    {
      public:
        void setNewTexture(resources::shared_texture_ptr &texture)
        {
            _texture = texture;
            setTexture(_texture.get());
        }

        // ship "flies" around this position
        void setFixedPosition(float x, float y)
        {
            _fixedPos = {x, y};
            setPosition(x, y);
        }

        sf::Vector2f getFixedPosition() const
        {
            return _fixedPos;
        }

        static constexpr int moveIncrement{3};
        static constexpr int moveFactor{20};
        sf::Vector2f moveProgress;

      private:
        resources::shared_texture_ptr _texture;
        sf::Vector2f _fixedPos;
    };

  public:
    Bridge(sf::RenderWindow &window);
    void update() override;
    void draw() override;
    void resize(const sf::Vector2u &prevWindowSize, const sf::Vector2u &newWindowSize) override;

    void onSystemArrival();
    void clearGalaxyWindow();

  protected:
    void addSpacestation();

  private:
    int _prevSystemIndex;
    std::vector<EnemyShip> _enemies;

    sf::Vector2f _spacestationSizeFactor;
    std::optional<GameSprite> _spacestation;

    GameSprite _bg;
    galaxywindow::GalaxyWindow _galaxyWindow;

    OutlineButton _helmsman;
    OutlineButton _tacticalOfficer;
    OutlineButton _missionComputerButton;
};

} // namespace views
#endif
