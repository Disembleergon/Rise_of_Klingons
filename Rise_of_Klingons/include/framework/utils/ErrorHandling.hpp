#ifndef ERRORHANDLING_HPP
#define ERRORHANDLING_HPP

#include <stdexcept>

// throwable, MessageBox on catch
class asset_not_found : public std::exception
{
  public:
    asset_not_found(const std::string &p) : path{p}
    {
    }

    const std::string path;
};

class ErrorHandler
{
  public:
    static void showErrorBox(const std::string &&msg);
};

#endif
