#include "../../include/framework/utils/ErrorHandling.hpp"

#ifdef _WIN32
#include <Windows.h>
#endif

void ErrorHandler::showErrorBox(const std::string &&msg)
{
#ifdef _WIN32
    MessageBox(NULL, msg.c_str(), NULL, MB_OK | MB_ICONERROR);
#endif
}
