#include "../../include/framework/utils/Random.hpp"
std::random_device Random::rd;
std::mt19937_64 Random::engine{Random::rd()};
