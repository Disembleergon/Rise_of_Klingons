#ifndef BRIDGE_HPP
#define BRIDGE_HPP

#include "../../Starship.hpp"
#include "../../framework/gui/Clickables.hpp"
#include "../../framework/Component.hpp"
#include "../../framework/GameSprite.hpp"
#include "GalaxyWindow.hpp"

namespace views
{
class Bridge final : public Component
{
    class EnemyShip final : public sf::RectangleShape
    {
      public:
        void setNewTexture(TextureLoader::shared_texture_ptr &texture)
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
        TextureLoader::shared_texture_ptr _texture;
        sf::Vector2f _fixedPos;
    };

  public:
    Bridge(sf::RenderWindow &window);
    void update() override;
    void draw() override;
    void resize(sf::Vector2u prevWindowSize, sf::Vector2u newWindowSize) override;

    void onSystemArrival();
    void clearEnemyVec();

  private:
    std::vector<EnemyShip> _enemies;
    SystemData _lastSystemData;

    GameSprite _bg;
    galaxywindow::GalaxyWindow _galaxyWindow;
    OutlineButton _helmsman;
    OutlineButton _tacticalOfficer;
};

} // namespace views
#endif
