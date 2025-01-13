#pragma once
#include <chrono>

// ���Ԃ��Ǘ�����N���X
class Timer
{
private:
    bool isCountingDown;
    long long initialTime;  // �~���b�P�ʂŕۑ�
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    long long elapsedTime;  // �~���b
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
        // �b���~���b�ɕϊ�
        long long timeInMilliseconds = static_cast<long long>(timeInSeconds * 1000.0f);
        SetInitialTime(static_cast<float>(timeInMilliseconds));
        Restart();
    }

    float GetRemainingTime() const {
        if (!isCountingDown) {
            return 0.0f; // �J�E���g�_�E�����[�h�łȂ��ꍇ�� 0 ��Ԃ�
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