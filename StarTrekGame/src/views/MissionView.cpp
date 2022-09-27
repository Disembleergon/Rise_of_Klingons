#include "../../include/views/MissionView.hpp"
#include "../../include/Globals.hpp"
#include "../../include/framework/utils/Random.hpp"

using namespace views;

const std::unordered_map<MissionView::MissionType, std::string> MissionView::_missionDescription = {
    {MissionView::MissionType::ELIMINATE, "Eliminate all enemy ships in the marked system!"},
    {MissionView::MissionType::RESCUE, "Rescue all friendly people in the marked system!"},
    {MissionView::MissionType::RETURN, "Return to the space station!"}};

MissionView::MissionView(sf::RenderWindow &window) : Component(window)
{
    static constexpr auto generateMissionIndex = []() -> int {
        return Random::generate_integral(0, Globals::get().SYSTEM_COUNT - 1);
    };

    const int numMissions = Random::generate_integral(2, 4);
    for (int i = 0; i < numMissions; ++i)
    {
        int prevMissionIndex = missionQueue.size() > 0 ? missionQueue.back().starsystemIndex : -1;
        int missionIndex = generateMissionIndex();

        while (missionIndex == Globals::get().SPACE_STATION_INDEX || missionIndex == prevMissionIndex)
            missionIndex = generateMissionIndex();

        Mission m;
        m.starsystemIndex = missionIndex;
        m.type = MissionType(Random::generate_integral(0, static_cast<int>(MissionType::ENUM_SIZE) - 2));
        // ^ generate random mission type      ;     -2 because of the RETURN_TO_BASE mission and (i begins at 0)

        missionQueue.push_back(std::move(m));
    }
}

void MissionView::draw()
{
}

void MissionView::update()
{
}
