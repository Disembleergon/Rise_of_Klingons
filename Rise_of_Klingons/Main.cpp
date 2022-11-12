#include "./include/Game.hpp"
#include "include/framework/utils/ErrorHandling.hpp"

int main()
{
    const auto screenWidth = sf::VideoMode::getDesktopMode().width;
    const auto windowWidth = static_cast<unsigned int>(screenWidth * 0.6f);
    const auto windowHeight = static_cast<unsigned int>(windowWidth * Game::ASPECT_RATIO);

    try
    {
        Game window{windowWidth, windowHeight, "Star Trek: Rise of Klingons"};
        window.run();
    }
    catch (const asset_not_found &e)
    {
        ErrorHandler::showErrorBox("Couldn't find asset(s).\n[ " + e.path + " ]");
    }
}
