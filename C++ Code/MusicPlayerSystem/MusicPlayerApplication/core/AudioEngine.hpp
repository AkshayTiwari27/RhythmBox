#pragma once
#include "../models/Song.hpp"
#include "../device/IAudioOutputDevice.hpp"
#include<string>
#include<iostream>

using namespace std;

class AudioEngine {
private:
    Song* currentSong;
public:
    AudioEngine() {
        currentSong = nullptr;
    }

    void play(IAudioOutputDevice* aod, Song* song) {
        if (song == nullptr) {
            throw runtime_error("Cannot play a null song.");
        }

        currentSong = song;
        cout << "Playing song: " << song->getTitle() << "\n";
        aod->playAudio(song);
    }
};