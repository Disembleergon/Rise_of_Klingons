#ifndef MISSIONVIEW_HPP
#define MISSIONVIEW_HPP

#include "../../framework/Component.hpp"
#include "../../framework/GameSprite.hpp"
#include "../../framework/gui/Clickables.hpp"
#include "../../framework/gui/TextDisplay.hpp"
#include <deque>
#include <unordered_map>
#include <vector>

namespace views
{
class MissionView : public Component
{
    enum class MissionType
    {
        ELIMINATE,
        RESCUE,

        RETURN,
        ENUM_SIZE // to get length/size of enum
    };
    const static std::unordered_map<MissionType, std::string> _missionDescription;

  public:
    struct Mission
    {
        MissionType type;
        int starsystemIndex;
    };
    inline static std::deque<Mission> missionQueue{};

    MissionView(sf::RenderWindow &window);
    void draw() override;
    void update() override;
    void resize(const sf::Vector2u &prevWindowSize, const sf::Vector2u &newWindowSize) override;

  protected:
    void generateMissions();
    void generateMissionUIElements();
    void configureMissionUIElements();

  private:
    GameSprite _panel;
    Clickable _returnButton;

    int _prevMissionCount{0}; // for updating misison ui elements
    GameSprite _missionOverviewPanel;

    using missionElement_ptr = std::unique_ptr<TextDisplay>;
    std::vector<missionElement_ptr> _missionUIElements;
};
} // namespace views
#endif
