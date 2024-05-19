#include "Audio.h"

#include "SoundNames.h"

std::unordered_map<std::string, sf::SoundBuffer> Audio::soundBuffers{};
std::unordered_map<std::string, sf::Sound> Audio::sounds{};

void Audio::initialize()
{
    soundBuffers[SHOOT].loadFromFile("sounds/shoot.ogg");
    sounds[SHOOT].setBuffer(soundBuffers[SHOOT]);
    sounds[SHOOT].setVolume(.5f);
    soundBuffers[ASTEROID_HIT].loadFromFile("sounds/asteroidHit.ogg");
    sounds[ASTEROID_HIT].setBuffer(soundBuffers[ASTEROID_HIT]);
    sounds[ASTEROID_HIT].setVolume(.5f);
}

void Audio::playSound(std::string soundName)
{
    sounds[soundName].play();
}
