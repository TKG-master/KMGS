#pragma once
#include <chrono>   //時間系のクラスや関数を使うためにインクルード


//時間を管理するクラス
class Timer 
{
private:

    bool isCountingDown;
    long long initialTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    long long elapsedTime;  // milliseconds
    bool isRunning;

public:

    bool TameStarflg = true;

    Timer(bool countDown = false) : isCountingDown(countDown), startTime(), elapsedTime(0), isRunning(false) {}

    void Start() {
        if (!isRunning) {
            startTime = std::chrono::high_resolution_clock::now();
            isRunning = true;
        }
    }

    void Stop() {
        if (isRunning) {
            auto now = std::chrono::high_resolution_clock::now();
            elapsedTime += std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime).count();
            isRunning = false;
        }
    }

    void Reset() {
        startTime = std::chrono::high_resolution_clock::now();
        elapsedTime = 0;
        isRunning = false;
    }

    void Restart() {
        Reset();
        Start();
    }

    bool IsRunning() const {
        return isRunning;
    }

    void SetCountDown(bool countDown) {
        isCountingDown = countDown;
    }

    void SetInitialTime(long long timeInMilliseconds) {
        initialTime = timeInMilliseconds;
    }

    void StartCountDown(long long timeInMilliseconds) {
        SetInitialTime(timeInMilliseconds);
        Restart();
    }

    long long GetRemainingTime() const {
        if (!isCountingDown) {
            return 0; // カウントダウンモードでない場合は0を返す
        }
        auto now = std::chrono::high_resolution_clock::now();
        long long elapsed = elapsedTime;
        if (isRunning) {
            elapsed += std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime).count();
        }
        long long remainingTime = initialTime - elapsed;
        return remainingTime > 0 ? remainingTime : 0;
    }

    bool IsTimeUp() const {
        return isCountingDown && GetRemainingTime() == 0;
    }
};


