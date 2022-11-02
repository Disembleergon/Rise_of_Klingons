#include "../../include/views/missions/MissionView.hpp"
#include "../../include/Game.hpp"
#include "../../include/Globals.hpp"
#include "../../include/framework/utils/Random.hpp"

using namespace views;

const std::unordered_map<MissionView::MissionType, std::string> MissionView::_missionDescription = {
    {MissionView::MissionType::ELIMINATE, "Eliminate all enemy ships in the marked system!"},
    {MissionView::MissionType::RESCUE, "Rescue all friendly people in the marked system!"},
    {MissionView::MissionType::RETURN, "Return to the space station!"}};

MissionView::MissionView(sf::RenderWindow &window)
    : Component(window), _returnButton(m_window), _missionOverviewPanel{"./assets/textures/missionOverviewPanel.png"}
{
    _panel.setNewTexture(Globals::get().PANEL_TEXTURE);
    _returnButton.setNewTexture(Globals::get().RETURN_BTN_TEXTURE);

    generateMissions();
    resize(m_window.getSize(), m_window.getSize());
}

void MissionView::draw()
{
    m_window.draw(_panel);
    _returnButton.draw();
    m_window.draw(_missionOverviewPanel);

    for (missionElement_ptr &elem : _missionUIElements)
        elem->draw();
}

void MissionView::update()
{
    _returnButton.update();
    if (_returnButton.clicked())
    {
        Game::currentView = View::BRIDGE;
    }

    if (_prevMissionCount != missionQueue.size())
    {
        generateMissionUIElements();
        _prevMissionCount = missionQueue.size();
    }
}

void views::MissionView::resize(const sf::Vector2u &prevWindowSize, const sf::Vector2u &newWindowSize)
{
    _panel.setPosition(0, 0);
    _panel.setSize(static_cast<sf::Vector2f>(newWindowSize));

    _returnButton.setPosition(newWindowSize.x * 0.06f, newWindowSize.y * 0.08f);
    _returnButton.setSize({newWindowSize.x * 0.05f, newWindowSize.y * 0.07f});

    _missionOverviewPanel.setPosition({newWindowSize.x * 0.1f, newWindowSize.y * 0.17f});
    _missionOverviewPanel.setSize({newWindowSize.x * 0.8f, newWindowSize.y * 0.65f});

    configureMissionUIElements();
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

        while (missionIndex == prevMissionIndex)
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

    _prevMissionCount = missionQueue.size();
    generateMissionUIElements();
}

void views::MissionView::generateMissionUIElements()
{
    _missionUIElements.clear();

    resources::shared_texture_ptr bgTexture = std::make_shared<sf::Texture>();
    resources::loadResource<sf::Texture>(bgTexture.get(), "./assets/textures/textBar.png");

    for (int i = 0; i < missionQueue.size(); ++i)
    {
        const auto missionDescription = _missionDescription.at(missionQueue[i].type);
        missionElement_ptr missionElement = std::make_unique<TextDisplay>(m_window, missionDescription, bgTexture);
        _missionUIElements.push_back(std::move(missionElement));
    }

    configureMissionUIElements();
}

void views::MissionView::configureMissionUIElements()
{
    const sf::Vector2f missionOverviewPanelPos = _missionOverviewPanel.getPosition();
    const sf::Vector2f missionOverviewPanelSize = _missionOverviewPanel.getSize();

    for (int i = 0; i < _missionUIElements.size(); ++i)
    {
        TextDisplay *missionElement = _missionUIElements.at(i).get();
        missionElement->setPosition({missionOverviewPanelPos.x + missionOverviewPanelSize.x * 0.2f,
                                     missionOverviewPanelPos.y + missionOverviewPanelSize.y * 0.15f * (i + 1)});
        missionElement->setSize({missionOverviewPanelSize.x * 0.6f, missionOverviewPanelSize.y * 0.1f});
        missionElement->updateTextWrap();
    }
}
