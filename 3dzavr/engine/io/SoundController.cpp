//
// Created by Иван Ильин on 17.10.2021.
//

#include <io/SoundController.h>
#include <utils/ResourceManager.h>
#include <utils/Log.h>

SoundController *SoundController::_instance = nullptr;

float SoundController::_soundVolume = 10;
float SoundController::_musicVolume = 10;

void SoundController::init() {
    delete _instance;
    _instance = new SoundController();

    Log::log("SoundController::init(): sound controller was initialized");
}

void SoundController::setSoundVolume(float volume) { _soundVolume = volume; }

void SoundController::setMusicVolume(float volume) {
    _musicVolume = volume;
    for (auto&[soundTag, sound] : _instance->_sounds) {
        if(soundTag == SoundTag("background")) {
            sound.setVolume(volume);
        }
    }
}

void SoundController::loadAndPlay(const SoundTag &soundTag, const std::string& filename) {
    if (_instance == nullptr) {
        return;
    }
    if (_instance->_sounds.count(soundTag) != 0) {
        _instance->_sounds[soundTag] = sf::Sound(*ResourceManager::loadSoundBuffer(filename));
    } else {
        _instance->_sounds.emplace(soundTag, sf::Sound(*ResourceManager::loadSoundBuffer(filename)));
    }

    _instance->_sounds[soundTag].setVolume(soundTag == SoundTag("background") ? _musicVolume : _soundVolume);
    _instance->_sounds[soundTag].play();
}

void SoundController::loadAndPlayWithVolume(const SoundTag &soundTag, const std::string& filename, float volume) {
    if (_instance == nullptr) {
        return;
    }
    if (_instance->_sounds.count(soundTag) != 0) {
        _instance->_sounds[soundTag] = sf::Sound(*ResourceManager::loadSoundBuffer(filename));
    } else {
        _instance->_sounds.emplace(soundTag, sf::Sound(*ResourceManager::loadSoundBuffer(filename)));
    }

    _instance->_sounds[soundTag].setVolume(soundTag == SoundTag("background") ? _musicVolume : _soundVolume * volume / 100);
    _instance->_sounds[soundTag].play();
}

void SoundController::playSound(const SoundTag &soundTag) {
    if (_instance == nullptr) {
        return;
    }

    if (_instance->_sounds.count(soundTag) != 0) {
        _instance->_sounds[soundTag].play();
    }
}

void SoundController::pauseSound(const SoundTag &soundTag) {
    if (_instance == nullptr) {
        return;
    }

    if (_instance->_sounds.count(soundTag) > 0) {
        _instance->_sounds[soundTag].pause();
    }
}

void SoundController::stopSound(const SoundTag &soundTag) {
    if (_instance == nullptr) {
        return;
    }

    if (_instance->_sounds.count(soundTag) > 0) {
        _instance->_sounds[soundTag].stop();
    }
}

sf::Sound::Status SoundController::getStatus(const SoundTag &soundTag) {
    if (_instance == nullptr) {
        return sf::Sound::Status::Stopped;
    }

    if (_instance->_sounds.count(soundTag) > 0) {
        return _instance->_sounds[soundTag].getStatus();
    } else {
        return sf::Sound::Status::Stopped;
    }
}

void SoundController::free() {
    if (_instance != nullptr) {
        for (auto&[soundTag, sound] : _instance->_sounds) {
            stopSound(soundTag);
        }
        _instance->_sounds.clear();
    }

    delete _instance;
    _instance = nullptr;

    Log::log("SoundController::free(): pointer to 'SoundController' was freed");
}
