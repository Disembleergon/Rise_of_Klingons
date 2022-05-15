#include "../../include/views/helmsman/Starmap.hpp"
#include <algorithm>
#include <random>

Starmap::Starmap(sf::RenderWindow &window, const sf::Vector2f &pos)
    : Component(window), _galaxyBG{"./assets/galaxy.png", pos, {_starmapWidth, _starmapHeight}},
      _warpslider{window, std::move(_warpsliderConfig)}
{
    generateButtons();
}

void Starmap::update()
{
    // update starmap buttons
    for (starmapbutton_ptr &btn : _starmapButtons)
    {
        btn->update();
        if (btn->clicked())
        {
            btn->setToggled(true);

            // untoggle all buttons except the one that was clicked
            for (starmapbutton_ptr &b : _starmapButtons)
            {
                if (b == btn)
                    continue;
                b->setToggled(false);
            }
        }
        else
        {
            btn->toggledSinceCurrentClick = false;
        }
    }

    _warpslider.update();
}

void Starmap::draw()
{
    m_window.draw(_galaxyBG);

    for (starmapbutton_ptr &btn : _starmapButtons)
    {
        btn->draw();
    }

    _warpslider.draw();
}

// --- private / protected ---

void Starmap::generateButtons()
{
    static constexpr int SYSTEM_COUNT = 7;
    static constexpr int BUTTON_SIZE = 75;
    static constexpr int SEED = 11011121;
    const auto galaxyPos = _galaxyBG.getPosition();

    TextureLoader::texture_ptr systemTexture = std::make_shared<sf::Texture>();
    TextureLoader::loadTexture(systemTexture, "./assets/controls/starmapButton.png");

    TextureLoader::texture_ptr toggledSystemTexture = std::make_shared<sf::Texture>();
    TextureLoader::loadTexture(toggledSystemTexture, "./assets/controls/starmapButton_toggled.png");

    // always producing the same pattern
    std::mt19937 engine{SEED};
    std::uniform_real_distribution<float> x_dist{galaxyPos.x, galaxyPos.x + _starmapWidth - BUTTON_SIZE};
    std::uniform_real_distribution<float> y_dist{galaxyPos.y, galaxyPos.y + _starmapHeight - BUTTON_SIZE};

    for (int i = 0; i < SYSTEM_COUNT; ++i)
    {
        // configure button
        starmapbutton_ptr btn = std::make_unique<ToggleButton>(m_window, systemTexture, toggledSystemTexture);
        const sf::Vector2f btnPos{x_dist(engine), y_dist(engine)};
        btn->setPosition(btnPos);
        btn->setSize({BUTTON_SIZE, BUTTON_SIZE});

        _starmapButtons.push_back(std::move(btn));
    }
}
