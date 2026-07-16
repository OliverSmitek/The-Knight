//
// Created by Oliver Šmítek on 07.07.2026.
//

#include "GameManager.h"

#include "Managers/SpriteManager.h"

GameManager::GameManager() {}

void GameManager::changeTickRateTo(int slowTimeTo) {
    if (ticks != slowTimeTo) {
        ticks = slowTimeTo;
        updateTimeInFrames();
        updateAnimationTimerToMatchTickRat(SpriteManager::getInstance().intervalBetwenAnimations);
    }

}

void GameManager::resetColockForTicks() {
    tickClock.restart();
}

void GameManager::addToTicksMade() {
    ticksAllredyMade++;
}
void GameManager::resetTickRateToDef() {
    if (ticks != 60) {
        ticks = 60;
        updateTimeInFrames();
        updateAnimationTimerToMatchTickRat(SpriteManager::getInstance().intervalBetwenAnimations);
    }
}

void GameManager::updateTimeInFrames() {
    timeInFrames = 1000.f / static_cast<float>(ticks);
}

void GameManager::updateAnimationTimerToMatchTickRat(int& timerBetwAnim) {
    constexpr float baseFrameTime = 1000.f / 60.f; // 16.6667 ms

    timerBetwAnim = static_cast<int>(
        baseTimer * (timeInFrames / baseFrameTime)
    );

}

void GameManager::changeTimeTo(float slowTime) {
    time = slowTime;
    SpriteManager::getInstance().intervalBetwenAnimations =  SpriteManager::getInstance().baseIntervalBetwenAnimations / time;
}
void GameManager::setTimeToDefule() {
    changeTimeTo(baseTime);
}