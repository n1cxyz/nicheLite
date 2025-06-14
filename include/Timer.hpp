#pragma once

#include "SDL.h"

class Timer {
private:
    Uint32 startTicks_;
    Uint32 pausedTicks_;

    bool started_;
    bool paused_;
public:
    Timer();

    void start();
    void stop();
    void pause();
    void unpause();

    Uint32 getTicks() const;
    bool isStarted() const;
    bool isPaused() const;
};