#include "MusicPlayerApplication.hpp"
#include <iostream>

using namespace std;

// Encapsulate the application logic
void runApplication() {
    auto application = MusicPlayerApplication::getInstance();

    // Populate library
    application->createSongInLibrary("Kesariya", "Arijit Singh", "/music/kesariya.mp3");
    application->createSongInLibrary("Chaiyya Chaiyya", "Sukhwinder Singh", "/music/chaiyya_chaiyya.mp3");
    application->createSongInLibrary("Tum Hi Ho", "Arijit Singh", "/music/tum_hi_ho.mp3");
    application->createSongInLibrary("Jai Ho", "A. R. Rahman", "/music/jai_ho.mp3");
    application->createSongInLibrary("Zinda", "Siddharth Mahadevan", "/music/zinda.mp3"); 

    // Create playlist and add songs
    application->createPlaylist("Bollywood Vibes");
    application->addSongToPlaylist("Bollywood Vibes", "Kesariya");
    application->addSongToPlaylist("Bollywood Vibes", "Chaiyya Chaiyya");
    application->addSongToPlaylist("Bollywood Vibes", "Tum Hi Ho");

    cout << "\n-- Playing a single song --\n";
    application->connectAudioDevice(DeviceType::HEADPHONES);
    application->playSingleSong("Zinda");

    cout << "\n-- Sequential Playback --\n";
    application->selectPlayStrategy(PlayStrategyType::SEQUENTIAL);
    application->loadPlaylist("Bollywood Vibes");
    application->playAllTracksInPlaylist();

    // --- DEMONSTRATE DELETE A SONG FROM PLAYLIST FUNCTIONALITY ---

    cout << "\n-- Deleting a song from a playlist --\n";
    application->removeSongFromPlaylist("Bollywood Vibes", "Chaiyya Chaiyya");

    // Play again to show the song was removed
    cout << "\n-- Playing 'Bollywood Vibes' after deleting a song --\n";
    application->loadPlaylist("Bollywood Vibes"); // Reload playlist in strategy
    application->playAllTracksInPlaylist();

    cout << "\n-- Deleting a playlist --\n";
    application->deletePlaylist("Bollywood Vibes");

    // Attempt to load the deleted playlist (will cause an error)
    try {
        cout << "\n-- Attempting to load deleted playlist --\n";
        application->loadPlaylist("Bollywood Vibes");
    } catch (const exception& e) {
        cerr << "Caught expected error: " << e.what() << endl;
    }
}

int main() {
    try {
        runApplication();
    } catch (const exception& error) {
        cerr << "An unexpected error occurred: " << error.what() << endl;
    }

    // Cleanup all resources before exiting
    MusicPlayerApplication::getInstance()->cleanup();
    cout << "\nApplication finished and all resources cleaned up." << endl;

    return 0;
}