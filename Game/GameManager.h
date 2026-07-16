//
// Created by Oliver Šmítek on 07.07.2026.
//

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "SFML/System/Clock.hpp"
#include "Managers/SpriteManager.h"



class GameManager {
    public:
    GameManager();

    static GameManager& getInstance(){
        static GameManager theInstance;
        return theInstance;
    }

    sf::Clock tickClock;
    int ticks = 60;
    //def = 60
    float timeInFrames = 1000.f / 60.f;
    long ticksAllredyMade = 0;
    bool updateOfTickRateHappend = false;
    int baseTimer = SpriteManager::getInstance().intervalBetwenAnimations;
    float baseFrameTime = 1000.f / 60.f; // 16.6667 ms

    float baseTime = 1.f;
    float time = 1.f;


    void changeTickRateTo(int slowTimeTo);
    void resetColockForTicks();
    void addToTicksMade();
    void resetTickRateToDef();
    void updateTimeInFrames();
    void updateAnimationTimerToMatchTickRat(int &timerBetwAnim);
    void changeTimeTo(float slowTime);
    void setTimeToDefule();
};



#endif //GAMEMANAGER_H
