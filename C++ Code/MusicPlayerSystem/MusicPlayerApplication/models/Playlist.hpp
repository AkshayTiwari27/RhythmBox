#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <algorithm> // Required for std::remove
#include "Song.hpp"

using namespace std;

class Playlist {
private:
    string playlistName;
    vector<Song*> songList;
public:
    Playlist(string name) {
        playlistName = name;
    }
    string getPlaylistName() {
        return playlistName;
    }
    const vector<Song*>& getSongs() const { // Return by const reference
        return songList;
    }
    int getSize() {
        return (int)songList.size();
    }
    void addSongToPlaylist(Song* song) {
        if (song == nullptr) {
            throw runtime_error("Cannot add null song to a playlist.");
        }
        songList.push_back(song);
    }

    // ADDED: Method to remove a song from the playlist
    void removeSong(Song* song) {
        if (song == nullptr) {
            throw runtime_error("Cannot remove a null song.");
        }
        auto it = std::remove(songList.begin(), songList.end(), song);
        if (it != songList.end()) {
            songList.erase(it, songList.end());
            cout << "Song \"" << song->getTitle() << "\" removed from playlist \"" << playlistName << "\"." << endl;
        } else {
            cout << "Song \"" << song->getTitle() << "\" not found in playlist \"" << playlistName << "\"." << endl;
        }
    }
};