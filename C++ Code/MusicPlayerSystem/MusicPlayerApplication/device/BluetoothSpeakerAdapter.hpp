#pragma once
#include "../models/Song.hpp"
#include "IAudioOutputDevice.hpp"
#include "../external/BluetoothSpeakerAPI.hpp"

using namespace std;

class BluetoothSpeakerAdapter : public IAudioOutputDevice {
private:
    BluetoothSpeakerAPI* bluetoothApi;
public:
    BluetoothSpeakerAdapter(BluetoothSpeakerAPI* api) {
        bluetoothApi = api;
    }
    
    // ADDED: Destructor to prevent memory leak
    ~BluetoothSpeakerAdapter() {
        delete bluetoothApi;
    }

    void playAudio(Song* song) override {
        string payload = song->getTitle() + " by " + song->getArtist();
        bluetoothApi->playSoundViaBluetooth(payload);
    }
};