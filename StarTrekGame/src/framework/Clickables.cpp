#include "../../include/framework/gui/Clickables.hpp"
#include "../../include/framework/utils/Time.hpp"

// ----- clickable -----

Clickable::Clickable(sf::RenderWindow &window) : Component(window)
{
}

void Clickable::update()
{
    if (getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window))))
    {
        _clicked = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        hoverAnimation(true);
    }
    else
    {
        hoverAnimation(false);
        _clicked = false;
    }
}

void Clickable::draw()
{
    m_window.draw(*this);
}

// ----- titled clickable -----

TitledClickable::TitledClickable(sf::RenderWindow &window) : Clickable(window)
{
}

void TitledClickable::draw()
{
    m_window.draw(*this);
    m_window.draw(_title);
}

void TitledClickable::resize(const sf::Vector2u &prevWindowSize, const sf::Vector2u &newWindowSize)
{
    const auto currSize = getSize();
    const sf::Vector2f relSize{currSize.x / prevWindowSize.x, currSize.y / prevWindowSize.y};
    const sf::Vector2f newSize{relSize.x * newWindowSize.x, relSize.y * newWindowSize.y};
    setSize(newSize);

    _title.setCharacterSize(newSize.y * 0.25f);
    _title.setOrigin(_title.getLocalBounds().width * 0.5f, _title.getLocalBounds().height * 0.5f);
    _title.setPosition(getPosition() + 0.5f * getSize());
}

void TitledClickable::configure(const Config &config)
{
    _font = config.font;
    _title.setFont(*_font);
    _title.setString(config.title);
    _title.setFillColor(config.color);
}

// ----- outline button -----

OutlineButton::OutlineButton(sf::RenderWindow &window) : Clickable(window)
{
    setOutlineThickness(_outlineThickness);
    setOutlineColor(sf::Color::Transparent);
}

void OutlineButton::hoverAnimation(bool hover)
{
    const sf::Color outlineClr{247, 216, 37, static_cast<sf::Uint8>(_outlineOpacity)};
    setOutlineColor(outlineClr);

    static constexpr int animationDuration = 800;

    if (hover) // fade in
    {
        _outlineOpacity = std::min(255.0f, _outlineOpacity + animationDuration * Time::deltaTime);
    }
    else // fade out
    {
        _outlineOpacity = std::max(0.0f, _outlineOpacity - animationDuration * Time::deltaTime);
    }
}

// ----- toggle button -----

ToggleButton::ToggleButton(sf::RenderWindow &window, const resources::shared_texture_ptr &texture1,
                           const resources::shared_texture_ptr &texture2)
    : OutlineButton(window), _texture1{texture1}, _texture2{texture2}
{
    setTexture(_texture1.get());
}

void ToggleButton::toggle()
{
    setToggled(!_toggled);
}

void ToggleButton::setToggled(bool state)
{
    if (toggledSinceCurrentClick) // only toggle on second click (one click =
        return;                   // holding down mouse button -> flashy)

    toggledSinceCurrentClick = true;
    _toggled = state;
    setTexture(_toggled ? _texture2.get() : _texture1.get());
}
