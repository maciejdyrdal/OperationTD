#ifndef TIMER_H
#define TIMER_H

// The application time based timer
class Timer
{
public:
    Timer();

    // The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    // Get the timer's time
    int getTicks();

    // Check the status of the timer
    bool isStarted();
    bool isPaused();

private:
    // The clock time when the timer started
    int mStartTicks;

    // The ticks stored when the timer was paused
    int mPausedTicks;

    // The timer status
    bool mPaused;
    bool mStarted;
};

#endif // !TIMER_H

