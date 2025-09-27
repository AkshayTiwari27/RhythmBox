#pragma once
#include<iostream>
#include "../strategies/SequentialPlayStrategy.hpp"
#include "../strategies/RandomPlayStrategy.hpp"
#include "../enums/PlayStrategyType.hpp"

using namespace std;

class StrategyManager {
private:
    static StrategyManager* instance;
    SequentialPlayStrategy* sequentialStrategy;
    RandomPlayStrategy* randomStrategy;

    StrategyManager() {
        sequentialStrategy = new SequentialPlayStrategy();
        randomStrategy = new RandomPlayStrategy();
    }
public:
    static StrategyManager* getInstance() {
        if (!instance) {
            instance = new StrategyManager();
        }
        return instance;
    }
    
    void cleanup() {
        delete sequentialStrategy;
        delete randomStrategy;
    }

    PlayStrategy* getStrategy(PlayStrategyType type) {
        if (type == PlayStrategyType::SEQUENTIAL) {
            return sequentialStrategy;
        } else { // RANDOM
            return randomStrategy;
        }
    }
};

StrategyManager* StrategyManager::instance = nullptr;