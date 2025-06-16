#pragma once
#include<iostream>
#include "../models/Playlist.hpp"
#include "PlayStrategy.hpp"

using namespace std;

class SequentialPlayStrategy : public PlayStrategy {
private:
    Playlist* currentPlaylist;
    int currentIndex;
public:
    SequentialPlayStrategy() {
        currentPlaylist = nullptr;
        currentIndex = -1;
    }

    void setPlaylist(Playlist* playlist) override {
        currentPlaylist = playlist;
        currentIndex = -1;
    }

    bool hasNext() override {
        if (!currentPlaylist) return false;
        return ((currentIndex + 1) < currentPlaylist->getSize());
    }

    Song* next() override {
        if (!hasNext()) {
            throw runtime_error("No next song available.");
        }
        currentIndex++;
        return currentPlaylist->getSongs()[currentIndex];
    }

    bool hasPrevious() override {
        if (!currentPlaylist) return false;
        return (currentIndex > 0);
    }

    Song* previous() override {
        if (!hasPrevious()) {
            throw runtime_error("No previous song available.");
        }
        currentIndex--;
        return currentPlaylist->getSongs()[currentIndex];
    }
};