
# **RhythmBox: An Interactive C++ Music Player**

RhythmBox is a console-based C++ application that simulates a music player, now featuring a fully interactive, menu-driven interface. It's designed to be a practical showcase of fundamental software design patterns in a clean, modular architecture.

The system allows users to manage a song library, build custom playlists, and control playback through a simple and intuitive command-line interface.

## **Key Features** 🎶

The application is controlled by a straightforward interactive menu with the following features:

#### **Music Library & Playlists**

  * **Create Songs**: Add new songs to the central music library.
  * **Manage Playlists**: Create, build, and delete multiple custom playlists.
  * **Add & Remove**: Easily add songs from the library to your playlists or remove them as needed.

#### **Playback Control**

  * **Flexible Playback**: Play entire playlists or individual songs on demand.
  * **Playback Strategies**: Instantly switch between **Sequential** (in-order) and **Random** (shuffled) playback modes.
  * **Track Navigation**: Seamlessly navigate through a loaded playlist with **next** and **previous** track controls.

#### **Device Simulation**

  * **Dynamic Connection**: Simulate connecting to different audio output devices like Headphones, Bluetooth Speakers, and Wired Speakers at runtime.

-----

## **Design Patterns Implemented**

This project leverages several key design patterns to ensure a modular and maintainable codebase:

  * **Facade**: The `MusicPlayerFacade` class provides a simplified, high-level interface to the complex underlying subsystems.
  * **Singleton**: All manager classes, the facade, and the main application class are implemented as singletons to ensure a single, globally accessible instance.
  * **Strategy**: The `PlayStrategy` interface allows the playback behavior (`SequentialPlayStrategy`, `RandomPlayStrategy`) to be changed dynamically at runtime.
  * **Adapter**: The adapter classes wrap incompatible external device APIs to conform to the system's standard `IAudioOutputDevice` interface.
  * **Factory Method**: The `DeviceFactory` class abstracts the instantiation logic for creating audio device objects.

-----

## **Project Structure**

The project is organized into a modular structure to separate concerns and improve clarity.

<!-- \<p align="center"\>
\<img src="UML.svg" alt="RhythmBox UML Diagram" width="850"/\>
<br>
\<em\>Diagram showing RhythmBox interaction in C++ \</em\>
\</p\> -->

```
MusicPlayerApplication/
│
├── main.cpp                      # Composition root and interactive CLI
├── MusicPlayerFacade.hpp         # Facade class that orchestrates features
├── MusicPlayerApplication.hpp    # High-level singleton class to run the application
│
├── core/
│   └── AudioEngine.hpp           # Handles core playback logic
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
│   ├── PlaylistManager.hpp       # Manages playlists
│   ├── DeviceManager.hpp         # Manages the connected audio device
│   └── StrategyManager.hpp       # Manages playback strategies
│
├── strategies/
│   ├── PlayStrategy.hpp          # Abstract base class for playback strategies
│   ├── SequentialPlayStrategy.hpp# Concrete strategy for sequential playback
│   └── RandomPlayStrategy.hpp    # Concrete strategy for random playback
│
├── device/
│   ├── IAudioOutputDevice.hpp    # Interface for all audio output devices
│   ├── BluetoothSpeakerAdapter.hpp
│   ├── WiredSpeakerAdapter.hpp
│   └── HeadphonesAdapter.hpp
│
├── external/
│   ├── BluetoothSpeakerAPI.hpp   # Mock external APIs for devices
│   ├── HeadphonesAPI.hpp
│   └── WiredSpeakerAPI.hpp
│
└── factories/
    └── DeviceFactory.hpp         # Factory for creating audio device instances
```

-----

## **Getting Started**

### **Prerequisites**

  * A C++11 compatible compiler (like g++).

### **Build & Run Instructions**

1.  **Navigate to the Source Directory**:
    Open your terminal and navigate to the application's main folder.

    ```sh
    cd "RhythmBox/C++ Code/MusicPlayerSystem/MusicPlayerApplication"
    ```

2.  **Compile the Application**:
    Use the following command to compile the source code into an executable file named `RhythmBox`.

    ```sh
    g++ -std=c++11 -o RhythmBox main.cpp
    ```

3.  **Run the Program**:
    Execute the compiled program to start the interactive session.

    ```sh
    ./RhythmBox
    ```

-----

## **Interactive Session Walkthrough**

Here’s a quick example of how you can use RhythmBox:

```text
Initial song library populated with 5 songs.

===== RhythmBox Music Player =====
1.  Create Song in Library
2.  Create Playlist
...
==================================
Enter your choice: 2
Enter new playlist name: Road Trip Mix

Playlist "Road Trip Mix" created.

===== RhythmBox Music Player =====
...
Enter your choice: 3
Enter playlist name: Road Trip Mix
Enter song title to add: Zinda

Song added to playlist successfully.

===== RhythmBox Music Player =====
...
Enter your choice: 6
Select a device (1: Headphones, 2: Bluetooth, 3: Wired): 2

Bluetooth device connected

===== RhythmBox Music Player =====
...
Enter your choice: 8
Enter playlist name to play: Road Trip Mix

-- Playing all tracks in 'Road Trip Mix' --
Playing song: Zinda
[BluetoothSpeaker] Playing: Zinda by Siddharth Mahadevan
Completed playlist: Road Trip Mix
```

-----

## **Technologies Used**

  * C++11
  * OOP and SOLID Principles
  * Design Patterns (Strategy, Singleton, Facade, Adapter, Factory)
  * Command-Line Interface (CLI)

-----

## **Future Improvements**

  * Add support for persistent storage using files or a database.
  * Implement real-time playback with actual audio libraries.
  * Develop a GUI version using a framework like Qt or ImGui.

-----

## **License**

This project is licensed under the MIT License - see the [LICENSE](https://www.google.com/search?q=LICENSE) file for details.