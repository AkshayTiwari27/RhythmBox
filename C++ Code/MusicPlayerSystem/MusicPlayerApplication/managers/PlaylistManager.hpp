#pragma once
#include "../models/Playlist.hpp"
#include<iostream>
#include<string>
#include<map>

using namespace std;

class PlaylistManager {
private:
    static PlaylistManager* instance;
    map<string, Playlist*> playlists;
    PlaylistManager() {}
public:
    static PlaylistManager* getInstance() {
        if (!instance) {
            instance = new PlaylistManager();
        }
        return instance;
    }

    // ADDED: Cleanup method to delete all playlists and prevent memory leaks
    void cleanup() {
        // FIX: Changed to C++11 compatible loop
        for (auto const& pair : playlists) {
            delete pair.second; // Delete the playlist pointer
        }
        playlists.clear();
    }

    void createPlaylist(const string& name) {
        if (playlists.count(name)) {
            throw runtime_error("Playlist \"" + name + "\" already exists.");
        }
        playlists[name] = new Playlist(name);
        cout << "Playlist \"" << name << "\" created." << endl;
    }

    void deletePlaylist(const string& name) {
        if (!playlists.count(name)) {
            throw runtime_error("Playlist \"" + name + "\" not found.");
        }
        delete playlists[name];
        playlists.erase(name);
        cout << "Playlist \"" << name << "\" deleted." << endl;
    }

    void addSongToPlaylist(const string& playlistName, Song* song) {
        if (!playlists.count(playlistName)) {
            throw runtime_error("Playlist \"" + playlistName + "\" not found.");
        }
        playlists[playlistName]->addSongToPlaylist(song);
    }

    void removeSongFromPlaylist(const string& playlistName, Song* song) {
        if (!playlists.count(playlistName)) {
            throw runtime_error("Playlist \"" + playlistName + "\" not found.");
        }
        playlists[playlistName]->removeSong(song);
    }

    Playlist* getPlaylist(const string& name) {
        if (!playlists.count(name)) {
            throw runtime_error("Playlist \"" + name + "\" not found.");
        }
        return playlists[name];
    }
};
PlaylistManager* PlaylistManager::instance = nullptr;