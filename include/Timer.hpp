#pragma once
#include "All.hpp"

class Timer {
public:
    Timer();

    void start();
    void stop();
    void pause();
    void unpause();

    Uint32 getTicks() const;
    bool isStarted() const;
    bool isPaused() const;

private:
    Uint32 startTicks;
    Uint32 pausedTicks;

    bool started;
    bool paused;
};