#pragma once
#include<iostream>
#include "../models/Playlist.hpp"
#include "PlayStrategy.hpp"
#include <vector>
#include <stack>   
#include <ctime>   // Added missing header for time()
#include <cstdlib> // Added missing header for srand() and rand()

using namespace std;

class RandomPlayStrategy : public PlayStrategy {
private:
    Playlist* currentPlaylist;
    vector<Song*> remainingSongs; 
    stack<Song*> history; 

public:
    RandomPlayStrategy() {
        currentPlaylist = nullptr;
        srand((unsigned)time(nullptr));
    }

    void setPlaylist(Playlist* playlist) override {
        currentPlaylist = playlist;
        if (!currentPlaylist || currentPlaylist->getSize() == 0) return;

        remainingSongs = currentPlaylist->getSongs();
        history = stack<Song*>(); 
    }

    bool hasNext() override {
        return currentPlaylist && !remainingSongs.empty();
    }

    Song* next() override {
        if (!currentPlaylist || currentPlaylist->getSize() == 0) {
            throw runtime_error("No playlist loaded or playlist is empty.");
        }
        if (remainingSongs.empty()) {
            throw runtime_error("No songs left to play");
        }

        int idx = rand() % remainingSongs.size();
        Song* selectedSong = remainingSongs[idx];
        
        swap(remainingSongs[idx], remainingSongs.back());
        remainingSongs.pop_back();

        history.push(selectedSong);
        return selectedSong;
    }

    bool hasPrevious() override {
        return history.size() > 0;
    }

    Song* previous() override {
        if (history.empty()) {
            throw std::runtime_error("No previous song available.");
        }

        Song* song = history.top();
        history.pop();
        return song;
    }
};