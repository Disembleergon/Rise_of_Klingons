#include "./include/Game.hpp"
#include "include/framework/utils/ErrorHandling.hpp"

int main()
{
    try
    {
        Game window{1800, 1300, "Star Trek Game"};
        window.run();
    }
    catch (const asset_not_found &e)
    {
        ErrorHandler::showErrorBox("Couldn't find asset(s).");
    }
}
