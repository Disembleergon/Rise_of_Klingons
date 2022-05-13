#include "../../include/views/helmsman/Starmap.hpp"
#include <random>

Starmap::Starmap(sf::RenderWindow &window, const sf::Vector2f &pos)
    : Component(window), _galaxyBG{"./assets/galaxy.png", pos, {_starmapWidth, _starmapHeight}}
{
    generateButtons();
}

void Starmap::update()
{
    for (starmapbutton_ptr &btn : _starmapButtons)
    {
        btn->update();
    }
}

void Starmap::draw()
{
    m_window.draw(_galaxyBG);

    for (starmapbutton_ptr &btn : _starmapButtons)
    {
        btn->draw();
    }
}

// --- private / protected ---

void Starmap::generateButtons()
{
    static constexpr int SYSTEM_COUNT = 7;
    static constexpr int BUTTON_SIZE = 75;
    static constexpr int SEED = 11011121;
    const auto galaxyPos = _galaxyBG.getPosition();

    // always producing the same pattern
    std::mt19937 engine{SEED};
    std::uniform_real_distribution<float> x_dist{galaxyPos.x, galaxyPos.x + _starmapWidth - BUTTON_SIZE};
    std::uniform_real_distribution<float> y_dist{galaxyPos.y, galaxyPos.y + _starmapHeight - BUTTON_SIZE};

    for (int i = 0; i < SYSTEM_COUNT; ++i)
    {
        starmapbutton_ptr btn = std::make_unique<Clickable>(m_window);
        const sf::Vector2f btnPos{x_dist(engine), y_dist(engine)};
        btn->setPosition(btnPos);
        btn->setSize({BUTTON_SIZE, BUTTON_SIZE});
        btn->setNewTexture("./assets/controls/starmapButton.png");

        _starmapButtons.push_back(std::move(btn));
    }
}
