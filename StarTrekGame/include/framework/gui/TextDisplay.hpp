#ifndef TEXTDISPLAY_HPP
#define TEXTDISPLAY_HPP

#include "../../Globals.hpp"
#include "../Component.hpp"
#include "../utils/ResourceLoader.hpp"

class TextDisplay : public Component
{
  public:
    TextDisplay(sf::RenderWindow &window, const sf::String &text, resources::shared_texture_ptr &bgTexture)
        : Component(window), _bgTexture(bgTexture), _text(text)
    {
        _bgShape.setTexture(bgTexture.get());
        _textDisplay.setFont(*Globals::get().FONT.get());
    }

    void draw() override;
    void update() override;
    void updateTextWrap();

    // --- getters & setters ---
    void setPosition(sf::Vector2f pos)
    {
        _bgShape.setPosition(pos);
        reconfigureTextDisplay();
    }
    [[nodiscard]] sf::Vector2f position() const
    {
        return _bgShape.getPosition();
    }

    void setSize(sf::Vector2f size)
    {
        _bgShape.setSize(size);
        reconfigureTextDisplay();
    }
    [[nodiscard]] sf::Vector2f size() const
    {
        return _bgShape.getSize();
    }

  protected:
    void reconfigureTextDisplay();

  private:
    resources::shared_texture_ptr _bgTexture;
    sf::RectangleShape _bgShape;

    const sf::String _text;
    sf::Text _textDisplay;
};

#endif
