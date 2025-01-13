#pragma once
#include <chrono>

// 時間を管理するクラス
class Timer
{
private:
    bool isCountingDown;
    long long initialTime;  // ミリ秒単位で保存
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    long long elapsedTime;  // ミリ秒
    bool isRunning;
    bool TimeUp = false;

public:
    bool TameStarflg = true;

    bool GetTimeUp() { return this->TimeUp; };
    void SetTimeUp(bool flg) { this->TimeUp = flg; };

    Timer(bool countDown = false)
        : isCountingDown(countDown),
        startTime(),
        elapsedTime(0),
        isRunning(false),
        initialTime(0) {}

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

    void SetInitialTime(float timeInMilliseconds) {
        initialTime = static_cast<long long>(timeInMilliseconds);
    }

    void StartCountDown(float timeInSeconds) {
        // 秒をミリ秒に変換
        long long timeInMilliseconds = static_cast<long long>(timeInSeconds * 1000.0f);
        SetInitialTime(static_cast<float>(timeInMilliseconds));
        Restart();
    }

    float GetRemainingTime() const {
        if (!isCountingDown) {
            return 0.0f; // カウントダウンモードでない場合は 0 を返す
        }
        auto now = std::chrono::high_resolution_clock::now();
        long long elapsed = elapsedTime;
        if (isRunning) {
            elapsed += std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime).count();
        }
        long long remainingTime = initialTime - elapsed;
        return remainingTime > 0 ? static_cast<float>(remainingTime) : 0.0f;
    }

    bool IsTimeUp() const {
        return isCountingDown && GetRemainingTime() == 0.0f;
    }
};