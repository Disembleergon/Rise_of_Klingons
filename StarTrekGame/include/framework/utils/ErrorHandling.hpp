#ifndef ERRORHANDLING_HPP
#define ERRORHANDLING_HPP

#include <stdexcept>

// throwable, MessageBox on catch
class asset_not_found : public std::exception
{
};

class ErrorHandler
{
  public:
    static void showErrorBox(const std::string &&msg);
};

#endif
