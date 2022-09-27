#include "../../include/views/missions/MissionView.hpp"
#include "../../include/Game.hpp"
#include "../../include/Globals.hpp"
#include "../../include/framework/utils/Random.hpp"

using namespace views;

const std::unordered_map<MissionView::MissionType, std::string> MissionView::_missionDescription = {
    {MissionView::MissionType::ELIMINATE, "Eliminate all enemy ships in the marked system!"},
    {MissionView::MissionType::RESCUE, "Rescue all friendly people in the marked system!"},
    {MissionView::MissionType::RETURN, "Return to the space station!"}};

MissionView::MissionView(sf::RenderWindow &window) : Component(window), _returnButton(m_window)
{
    _panel.setNewTexture(Globals::get().PANEL_TEXTURE);
    _returnButton.setNewTexture(Globals::get().RETURN_BTN_TEXTURE);
    resize(m_window.getSize(), m_window.getSize());

    generateMissions();
}

void MissionView::draw()
{
    m_window.draw(_panel);
    _returnButton.draw();
}

void MissionView::update()
{
    _returnButton.update();
    if (_returnButton.clicked())
    {
        Game::currentView = View::BRIDGE;
    }
}

void views::MissionView::resize(sf::Vector2u prevWindowSize, sf::Vector2u newWindowSize)
{
    _panel.setPosition(0, 0);
    _panel.setSize(static_cast<sf::Vector2f>(newWindowSize));

    _returnButton.setPosition(newWindowSize.x * 0.06f, newWindowSize.y * 0.08f);
    _returnButton.setSize({newWindowSize.x * 0.05f, newWindowSize.y * 0.07f});
}

void views::MissionView::generateMissions()
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

    // last mission (always): return to space station
    Mission returnMission;
    returnMission.starsystemIndex = Globals::get().SPACE_STATION_INDEX;
    returnMission.type = MissionType::RETURN;
    missionQueue.push_back(std::move(returnMission));
}
