#include "../../include/framework/gui/TextDisplay.hpp"

void TextDisplay::draw()
{
    m_window.draw(_bgShape);
    m_window.draw(_textDisplay);
}

void TextDisplay::update()
{
    // EMPTY
}

void TextDisplay::updateTextWrap()
{
    const auto bgShapeWidth = _bgShape.getSize().x;
    const auto textDisplayPosX = _textDisplay.getPosition().x;
    const auto textMarginLeft = textDisplayPosX - _bgShape.getPosition().x;
    const auto charSize = _textDisplay.getCharacterSize();

    sf::String result;
    sf::String currentLine;

    int prevIndex = 0;
    auto whitespaceIndex = _text.find(" ");
    while (whitespaceIndex != sf::String::InvalidPos)
    {
        sf::String word = _text.substring(prevIndex, whitespaceIndex - prevIndex);
        if ((currentLine.getSize() + word.getSize()) * charSize > bgShapeWidth - textMarginLeft)
        {
            result += (currentLine + "\n");
            currentLine = word.substring(1, word.getSize());
        }
        else
        {
            currentLine += word;
        }
        prevIndex = whitespaceIndex;
        whitespaceIndex = _text.find(" ", prevIndex + 1);
    }
    currentLine += _text.substring(prevIndex, _text.getSize() - prevIndex); // last word after last whitespace
    result += currentLine;
    _textDisplay.setString(result);
}

void TextDisplay::reconfigureTextDisplay()
{
    const auto bgShapeSize = _bgShape.getSize();
    const auto bgShapePos = _bgShape.getPosition();

    _textDisplay.setPosition(bgShapePos.x + bgShapeSize.x * 0.1f, bgShapePos.y + bgShapeSize.y * 0.25f);
    _textDisplay.setCharacterSize(bgShapeSize.y * 0.25f);
}
