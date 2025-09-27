#pragma once
#include <string>
#include <iostream>

using namespace std;

class Song {
private:
    string title;
    string artist;
public:
    Song(string t, string a) {
        title = t;
        artist = a;
    }
    string getTitle() { 
        return title; 
    }
    string getArtist() { 
        return artist;      
    }
};