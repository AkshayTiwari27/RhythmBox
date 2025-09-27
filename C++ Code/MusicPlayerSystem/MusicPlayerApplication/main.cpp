#include "MusicPlayerApplication.hpp"
#include "MusicPlayerFacade.hpp"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

void showMenu() {
    cout << "\n===== RhythmBox Music Player =====\n";
    cout << "1.  Create Song in Library\n";
    cout << "2.  Create Playlist\n";
    cout << "3.  Add Song to Playlist\n";
    cout << "4.  Remove Song from Playlist\n";
    cout << "5.  Delete Playlist\n";
    cout << "6.  Connect Audio Device\n";
    cout << "7.  Select Playback Strategy\n";
    cout << "8.  Load and Play Entire Playlist\n";
    cout << "9.  Play Single Song\n";
    cout << "10. Play Next Track in Loaded Playlist\n";
    cout << "11. Play Previous Track in Loaded Playlist\n";
    cout << "0.  Exit\n";
    cout << "==================================\n";
    cout << "Enter your choice: ";
}

string getInput(const string& prompt) {
    cout << prompt;
    string input;
    getline(cin, input);
    return input;
}

void populateInitialLibrary(MusicPlayerApplication* app) {
    app->createSongInLibrary("Kesariya", "Arijit Singh");
    app->createSongInLibrary("Chaiyya Chaiyya", "Sukhwinder Singh");
    app->createSongInLibrary("Tum Hi Ho", "Arijit Singh");
    app->createSongInLibrary("Jai Ho", "A. R. Rahman");
    app->createSongInLibrary("Zinda", "Siddharth Mahadevan");
    cout << "Initial song library populated with 5 songs.\n";
}

void runInteractiveSession() {
    auto application = MusicPlayerApplication::getInstance();
    populateInitialLibrary(application);

    int choice = -1;
    while (choice != 0) {
        showMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        try {
            switch (choice) {
                case 1: {
                    string title = getInput("Enter song title: ");
                    string artist = getInput("Enter artist name: ");
                    application->createSongInLibrary(title, artist);
                    cout << "Song \"" << title << "\" added to library.\n";
                    break;
                }
                case 2: {
                    string name = getInput("Enter new playlist name: ");
                    application->createPlaylist(name);
                    break;
                }
                case 3: {
                    string playlistName = getInput("Enter playlist name: ");
                    string songTitle = getInput("Enter song title to add: ");
                    application->addSongToPlaylist(playlistName, songTitle);
                    cout << "Song added to playlist successfully.\n";
                    break;
                }
                case 4: {
                    string playlistName = getInput("Enter playlist name: ");
                    string songTitle = getInput("Enter song title to remove: ");
                    application->removeSongFromPlaylist(playlistName, songTitle);
                    break;
                }
                 case 5: {
                    string playlistName = getInput("Enter playlist name to delete: ");
                    application->deletePlaylist(playlistName);
                    break;
                }
                case 6: {
                    cout << "Select a device (1: Headphones, 2: Bluetooth, 3: Wired): ";
                    int deviceChoice;
                    cin >> deviceChoice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    DeviceType type;
                    if (deviceChoice == 1) type = DeviceType::HEADPHONES;
                    else if (deviceChoice == 2) type = DeviceType::BLUETOOTH;
                    else if (deviceChoice == 3) type = DeviceType::WIRED;
                    else {
                        cout << "Invalid device choice.\n";
                        break;
                    }
                    application->connectAudioDevice(type);
                    break;
                }
                case 7: {
                    cout << "Select a strategy (1: Sequential, 2: Random): ";
                    int strategyChoice;
                    cin >> strategyChoice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    PlayStrategyType type;
                    if (strategyChoice == 1) type = PlayStrategyType::SEQUENTIAL;
                    else if (strategyChoice == 2) type = PlayStrategyType::RANDOM;
                    else {
                        cout << "Invalid strategy choice.\n";
                        break;
                    }
                    application->selectPlayStrategy(type);
                    cout << "Playback strategy set.\n";
                    break;
                }
                case 8: {
                    string playlistName = getInput("Enter playlist name to play: ");
                    application->loadPlaylist(playlistName);
                    cout << "\n-- Playing all tracks in '" << playlistName << "' --\n";
                    application->playAllTracksInPlaylist();
                    break;
                }
                case 9: {
                    string songTitle = getInput("Enter song title to play: ");
                    cout << "\n-- Playing single song --\n";
                    application->playSingleSong(songTitle);
                    break;
                }
                case 10: {
                     cout << "\n-- Playing next track --\n";
                     MusicPlayerFacade::getInstance()->playNextTrack();
                    break;
                }
                case 11: {
                     cout << "\n-- Playing previous track --\n";
                     application->playPreviousTrackInPlaylist();
                    break;
                }
                case 0:
                    cout << "Exiting RhythmBox...\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
                    break;
            }
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
}


int main() {
    try {
        runInteractiveSession();
    } catch (const exception& error) {
        cerr << "An unexpected error occurred: " << error.what() << endl;
    }

    MusicPlayerApplication::getInstance()->cleanup();
    cout << "\nApplication finished and all resources cleaned up." << endl;

    return 0;
}