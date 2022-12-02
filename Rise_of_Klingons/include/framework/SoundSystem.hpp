#include <SFML/Audio.hpp>
#include <algorithm>
#include <list>

namespace sound
{

class SoundSystem
{
  public:
    static void playAudio(const sf::String &filepath)
    {
        sf::SoundBuffer buffer;
        buffer.loadFromFile(filepath);
        playAudio(buffer);
    }

    static void playAudio(const sf::SoundBuffer &buffer)
    {
        _activeSounds.emplace_back(buffer);
        _activeSounds.back().play();
    }

    static void cleanUp()
    {
        // remove finished sounds
        const auto rm = std::remove_if(_activeSounds.begin(), _activeSounds.end(),
                                       [](sf::Sound &s) { return s.getStatus() == sf::SoundSource::Status::Stopped; });
        _activeSounds.erase(rm, _activeSounds.end());
    }

    inline static std::list<sf::Sound> _activeSounds{};

  private:
};

} // namespace sound
