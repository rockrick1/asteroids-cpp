#pragma once
#include <string>
#include <unordered_map>
#include <SFML/Audio.hpp>

class Audio
{
    static std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
    static std::unordered_map<std::string, sf::Sound> sounds;

public:
    static void initialize();
    static void playSound(std::string soundName);
};
