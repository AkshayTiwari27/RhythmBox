#pragma once
#include "managers/PlaylistManager.hpp"
#include "managers/DeviceManager.hpp"
#include "managers/StrategyManager.hpp"
#include "MusicPlayerFacade.hpp"

using namespace std;

class MusicPlayerApplication {
private:
    static MusicPlayerApplication* instance;
    vector<Song*> songLibrary;
    MusicPlayerApplication() {}

public:
    static MusicPlayerApplication* getInstance() {
        if (!instance) {
            instance = new MusicPlayerApplication();
        }
        return instance;
    }

    void cleanup() {
        for (Song* song : songLibrary) {
            delete song;
        }
        songLibrary.clear();
        PlaylistManager::getInstance()->cleanup();
        DeviceManager::getInstance()->cleanup();
        StrategyManager::getInstance()->cleanup();
        MusicPlayerFacade::getInstance()->cleanup();
    }

    void createSongInLibrary(const string& title, const string& artist) {
        Song* newSong = new Song(title, artist);
        songLibrary.push_back(newSong);
    }

    Song* findSongByTitle(const string& title) {
        for (Song* s : songLibrary) {
            if (s->getTitle() == title) {
                return s;
            }
        }
        return nullptr;
    }
    void createPlaylist(const string& playlistName) {
        PlaylistManager::getInstance()->createPlaylist(playlistName);
    }

    void deletePlaylist(const string& playlistName) {
        PlaylistManager::getInstance()->deletePlaylist(playlistName);
    }

    void addSongToPlaylist(const string& playlistName,
                            const string& songTitle) {
        Song* song = findSongByTitle(songTitle);
        if (!song) {
            throw runtime_error("Song \"" + songTitle + "\" not found in library.");
        }
        PlaylistManager::getInstance()
            ->addSongToPlaylist(playlistName, song);
    }

    void removeSongFromPlaylist(const string& playlistName, const string& songTitle) {
        Song* song = findSongByTitle(songTitle);
        if (!song) {
            throw runtime_error("Song \"" + songTitle + "\" not found in library.");
        }
        PlaylistManager::getInstance()->removeSongFromPlaylist(playlistName, song);
    }

    void connectAudioDevice(DeviceType deviceType) {
        MusicPlayerFacade::getInstance()->connectDevice(deviceType);
    }

    void selectPlayStrategy(PlayStrategyType strategyType) {
        MusicPlayerFacade::getInstance()->setPlayStrategy(strategyType);
    }



    void loadPlaylist(const string& playlistName) {
        MusicPlayerFacade::getInstance()->loadPlaylist(playlistName);
    }

    void playSingleSong(const string& songTitle) {
        Song* song = findSongByTitle(songTitle);
        if (!song) {
            throw runtime_error("Song \"" + songTitle + "\" not found.");
        }
        MusicPlayerFacade::getInstance()->playSong(song);
    }

    void playAllTracksInPlaylist() {
        MusicPlayerFacade::getInstance()->playAllTracks();
    }

    void playPreviousTrackInPlaylist() {
        MusicPlayerFacade::getInstance()->playPreviousTrack();
    }
};

MusicPlayerApplication* MusicPlayerApplication::instance = nullptr;