#ifndef MISSIONVIEW_HPP
#define MISSIONVIEW_HPP

#include "../framework/Component.hpp"
#include <deque>
#include <unordered_map>

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
    // void resize(sf::Vector2u prevWindowSize, sf::Vector2u newWindowSize)
    // override;
};
} // namespace views
#endif
