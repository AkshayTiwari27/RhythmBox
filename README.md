
# **RhythmBox: C++ Music Player System**

RhythmBox is a console-based C++ application that simulates a music player. It is designed with a strong emphasis on clean architecture and the practical application of fundamental software design patterns. The system supports a song library, playlist management, multiple playback strategies, and dynamic audio output device selection.

## **Key Features**

* **Song Library**: Create and maintain a central library of songs.
* **Playlist Management**:
    * Create and delete user-defined playlists.
    * Add songs from the library to any playlist.
    * Remove songs from a specific playlist.
* **Multiple Playback Strategies**:
    * **Sequential**: Plays tracks in the order they appear in the playlist.
    * **Random**: Plays tracks from the playlist in a random, non-repeating order.
    * **Custom Queue**: Allows users to queue a song to play next, otherwise plays sequentially.
* **Dynamic Device Connection**:
    * Supports various audio output types like Headphones, Wired Speakers, and Bluetooth speakers.
    * Dynamically connect to a device type at runtime.
* **Core Playback Controls**:
    * Play a single song or an entire playlist.
    * Pause and resume playback.
    * Navigate with `next()` and `previous()` track functions.

## **Design Patterns Implemented**

This project leverages several key design patterns to ensure a modular, scalable, and maintainable codebase.

* **Facade**: The `MusicPlayerFacade` class provides a simplified, high-level interface to the complex underlying subsystems like the audio engine and various managers. This decouples the client (`main.cpp`) from the internal workings of the application.
* **Singleton**: The `MusicPlayerApplication`, `MusicPlayerFacade`, and all manager classes (`PlaylistManager`, `DeviceManager`, `StrategyManager`) are implemented as singletons. This ensures a single, globally accessible instance for each, managing a shared state consistently across the application.
* **Strategy**: The `PlayStrategy` interface defines a common contract for all playback algorithms. Concrete classes like `SequentialPlayStrategy`, `RandomPlayStrategy`, and `CustomQueueStrategy` implement this interface, allowing the playback behavior to be changed dynamically at runtime.
* **Adapter**: The `BluetoothSpeakerAdapter`, `WiredSpeakerAdapter`, and `HeadphonesAdapter` classes act as adapters. They wrap the incompatible external device APIs (`BluetoothSpeakerAPI`, etc.) to conform to the standard `IAudioOutputDevice` interface required by the system.
* **Factory Method**: The `DeviceFactory` class provides a static `createDevice` method that manufactures and returns instances of `IAudioOutputDevice` based on the specified `DeviceType`. This abstracts the instantiation logic from the client.

## **Project Structure**

The project is organized into a modular structure to separate concerns and improve clarity.

```
MusicPlayerApplication/
│
├── main.cpp                      # Composition root and application entry point
├── MusicPlayerFacade.hpp         # Facade class that orchestrates application features
├── MusicPlayerApplication.hpp    # High-level singleton class to run the application
│
├── core/
│   └── AudioEngine.hpp           # Handles core playback logic (play, pause)
│
├── enums/
│   ├── DeviceType.hpp            # Enum for audio output device types
│   └── PlayStrategyType.hpp      # Enum for playback strategy types
│
├── models/
│   ├── Song.hpp                  # Data model for a song
│   └── Playlist.hpp              # Data model for a playlist
│
├── managers/
│   ├── PlaylistManager.hpp       # Manages playlist creation, deletion, and modification
│   ├── DeviceManager.hpp         # Manages the currently connected audio device
│   └── StrategyManager.hpp       # Manages the available playback strategies
│
├── strategies/
│   ├── PlayStrategy.hpp          # Abstract base class for all playback strategies
│   ├── SequentialPlayStrategy.hpp# Concrete strategy for sequential playback
│   ├── RandomPlayStrategy.hpp    # Concrete strategy for random playback
│   └── CustomQueueStrategy.hpp   # Concrete strategy for queued playback
│
├── device/
│   ├── IAudioOutputDevice.hpp    # Interface for all audio output devices
│   ├── BluetoothSpeakerAdapter.hpp # Adapter for the Bluetooth API
│   ├── WiredSpeakerAdapter.hpp   # Adapter for the Wired Speaker API
│   └── HeadphonesAdapter.hpp     # Adapter for the Headphones API
│
├── external/
│   ├── BluetoothSpeakerAPI.hpp   # Mock external API for a Bluetooth speaker
│   ├── HeadphonesAPI.hpp         # Mock external API for headphones
│   └── WiredSpeakerAPI.hpp       # Mock external API for a wired speaker
│
└── factories/
    └── DeviceFactory.hpp         # Factory for creating audio device instances
```

## **How to Build and Run**

1.  **Prerequisites**: You need a C++ compiler (like g++).
2.  **Compilation**: Since all implementation is in header files and `main.cpp`, you can compile the project with a single command from the root directory:
    ```sh
    g++ -std=c++11 -o RhythmBox main.cpp
    ```
3.  **Execution**: Run the compiled executable:
    ```sh
    ./RhythmBox
    ```

## **Usage Example**

The `main.cpp` file provides a clear demonstration of the application's functionality.

```cpp

#include "MusicPlayerApplication.hpp"
#include <iostream>

using namespace std;

void runApplication() {
    auto application = MusicPlayerApplication::getInstance();

    // 1. Populate the song library
    application->createSongInLibrary("Kesariya", "Arijit Singh", "/music/kesariya.mp3");
    application->createSongInLibrary("Zinda", "Siddharth Mahadevan", "/music/zinda.mp3");

    // 2. Create a playlist and add songs
    application->createPlaylist("Bollywood Vibes");
    application->addSongToPlaylist("Bollywood Vibes", "Kesariya");

    // 3. Connect a device and play a single song
    cout << "\n-- Playing a single song --\n";
    application->connectAudioDevice(DeviceType::HEADPHONES);
    application->playSingleSong("Zinda");

    // 4. Select a strategy and play a playlist
    cout << "\n-- Sequential Playback --\n";
    application->selectPlayStrategy(PlayStrategyType::SEQUENTIAL);
    application->loadPlaylist("Bollywood Vibes");
    application->playAllTracksInPlaylist();

    // 5. Remove a song and demonstrate the change
    cout << "\n-- Deleting a song from a playlist --\n";
    application->removeSongFromPlaylist("Bollywood Vibes", "Kesariya");
    application->playAllTracksInPlaylist(); // Playlist is now empty

    // 6. Delete the playlist
    cout << "\n-- Deleting a playlist --\n";
    application->deletePlaylist("Bollywood Vibes");
}

int main() {
    try {
        runApplication();
    } catch (const exception& error) {
        cerr << "An unexpected error occurred: " << error.what() << endl;
    }

    // 7. Clean up all resources
    MusicPlayerApplication::getInstance()->cleanup();
    cout << "\nApplication finished and all resources cleaned up." << endl;

    return 0;
}

```

## Technologies Used

- C++11
- OOP and SOLID Principles
- Design Patterns (Strategy, Singleton, Facade, Adapter, Factory)
- Command-Line Interface (CLI)

## Future Improvements

- Add support for persistent storage using files or databases
- Implement real-time playback with audio libraries
- GUI version using Qt or ImGui

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

