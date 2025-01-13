#include "easings.h"
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <SimpleMath.h>
#include <cmath>
#include <algorithm>

DirectX::SimpleMath::Vector3 EaseInOut(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time)
{
    // Time �� 0.0 ���� 1.0 �͈̔͂ɐ���
    Time = std::clamp(Time, 0.0f, 1.0f);

    float t;

    // �C�[�W���O�̌v�Z
    if (Time < 0.5f)
    {
        t = 8 * Time * Time * Time * Time;
    }
    else
    {
        t = 1 - powf(-2 * Time + 2, 4) / 2;  // powf ���g�p���� float �ɕϊ�
    }

    // ���
    DirectX::SimpleMath::Vector3 Result = DirectX::SimpleMath::Vector3::Lerp(Start, Goal, t);
    return Result;
}

DirectX::SimpleMath::Vector3 EaseInOutCirc(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time)
{
    // Time �� 0.0 ���� 1.0 �͈̔͂ɐ���
    Time = std::clamp(Time, 0.0f, 1.0f);

    float t;

    if (Time < 0.5f) {
        t = (1.0f - sqrtf(1.0f - powf(2.0f * Time, 2.0f))) / 2.0f;  // sqrtf �� powf ���g�p
    }
    else {
        t = (sqrtf(1.0f - powf(-2.0f * Time + 2.0f, 2.0f)) + 1.0f) / 2.0f;
    }

    // ���
    DirectX::SimpleMath::Vector3 Result = DirectX::SimpleMath::Vector3::Lerp(Start, Goal, t);

    return Result;
}

DirectX::SimpleMath::Vector3 EaseInOutQuart(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time)
{
    // Time �� 0.0 ���� 1.0 �͈̔͂ɐ���
    Time = std::clamp(Time, 0.0f, 1.0f);

    float t;
    if (Time < 0.5f) {
        t = 8 * Time * Time * Time * Time;
    }
    else {
        t = 1 - std::powf(-2 * Time + 2, 4) / 2;  // std::powf ���g�p���� float �ɕϊ�
    }

    // ���
    DirectX::SimpleMath::Vector3 Result = DirectX::SimpleMath::Vector3::Lerp(Start, Goal, t);

    return Result;
}

DirectX::SimpleMath::Vector3 EaselnSine(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time)
{
    // Time �� 0.0 ���� 1.0 �͈̔͂ɐ���
    Time = std::clamp(Time, 0.0f, 1.0f);

    // easeInSine �̌v�Z
    float t = 1.0f - std::cos((Time * DirectX::XM_PI) / 2.0f);

    // ���
    DirectX::SimpleMath::Vector3 Result = DirectX::SimpleMath::Vector3::Lerp(Start, Goal, t);

    return Result;
}

DirectX::SimpleMath::Vector3 EaselnBack(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time)
{
    // Time �� 0.0 ���� 1.0 �͈̔͂ɐ���
    Time = std::clamp(Time, 0.0f, 1.0f);

    // �o�b�N�C�[�W���O�̌v�Z
    const float c1 = 1.70158f;
    const float c3 = c1 + 1.0f;

    float t = c3 * Time * Time * Time - c1 * Time * Time;

    // ���
    DirectX::SimpleMath::Vector3 Result = DirectX::SimpleMath::Vector3::Lerp(Start, Goal, t);

    return Result;
}

DirectX::SimpleMath::Vector3 EaselnOutBack(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time)
{
    // Time �� 0.0 ���� 1.0 �͈̔͂ɐ���
    Time = std::clamp(Time, 0.0f, 1.0f);

    // �o�b�N�C�[�W���O�̌v�Z
    const float c1 = 1.70158f;
    const float c2 = c1 * 1.525f;

    float t;
    if (Time < 0.5f) {
        t = (std::powf(2 * Time, 2) * ((c2 + 1) * 2 * Time - c2)) / 2;
    }
    else {
        t = (std::powf(2 * Time - 2, 2) * ((c2 + 1) * (2 * Time - 2) + c2) + 2) / 2;
    }

    // ���
    DirectX::SimpleMath::Vector3 Result = DirectX::SimpleMath::Vector3::Lerp(Start, Goal, t);

    return Result;
}

DirectX::SimpleMath::Vector3 EaselnOutQuint(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time)
{
    // Time �� 0.0 ���� 1.0 �͈̔͂ɐ���
    Time = std::clamp(Time, 0.0f, 1.0f);

    float t = 1.0f - powf(1.0f - Time, 5.0f);  // powf ���g�p���� float �ɕϊ�

    // ���
    DirectX::SimpleMath::Vector3 Result = DirectX::SimpleMath::Vector3::Lerp(Start, Goal, t);

    return Result;
}

DirectX::SimpleMath::Vector3 EaselnElastic(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time)
{
    // Time �� 0.0 ���� 1.0 �͈̔͂ɐ���
    Time = std::clamp(Time, 0.0f, 1.0f);

    const float c4 = (2 * DirectX::XM_PI) / 3;

    float t = 0.0f;

    if (Time == 0.0f) {
        t = 0;
    }
    else if (Time == 1.0f) {
        t = 1;
    }
    else {
        t = -powf(2, -10 * Time) * std::sin((Time * 10 - 0.75f) * c4) + 1;  // powf �� sinf ���g�p
    }

    // ���
    DirectX::SimpleMath::Vector3 Result = DirectX::SimpleMath::Vector3::Lerp(Start, Goal, t);

    return Result;
}

DirectX::SimpleMath::Vector3 EaselnQuart(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time)
{
    // Time �� 0.0 ���� 1.0 �͈̔͂ɐ���
    Time = std::clamp(Time, 0.0f, 1.0f);

    float t = Time * Time * Time * Time;

    // ���
    DirectX::SimpleMath::Vector3 Result = DirectX::SimpleMath::Vector3::Lerp(Start, Goal, t);

    return Result;
}

DirectX::SimpleMath::Vector3 EaselnQutExpo(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time)
{
    // Time �� 0.0 ���� 1.0 �͈̔͂ɐ���
    Time = std::clamp(Time, 0.0f, 1.0f);

    float t;
    if (Time == 0.0f) {
        t = 0.0f;
    }
    else if (Time == 1.0f) {
        t = 1.0f;
    }
    else if (Time < 0.5f) {
        t = std::powf(2, 20 * Time - 10) / 2;  // powf ���g�p
    }
    else {
        t = (2 - std::powf(2, -20 * Time + 10)) / 2;
    }

    // ���
    DirectX::SimpleMath::Vector3 Result = DirectX::SimpleMath::Vector3::Lerp(Start, Goal, t);

    return Result;
}

DirectX::SimpleMath::Vector3 EaseOutCirc(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time)
{
    // Time �� 0.0 ���� 1.0 �͈̔͂ɐ���
    Time = std::clamp(Time, 0.0f, 1.0f);

    float t = std::sqrtf(1 - std::powf(Time - 1, 2));  // std::sqrtf �� powf ���g�p

    // ���
    DirectX::SimpleMath::Vector3 Result = DirectX::SimpleMath::Vector3::Lerp(Start, Goal, t);

    return Result;
}

DirectX::SimpleMath::Vector3 easeInOutElastic(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time)
{
    // Time �� 0.0 ���� 1.0 �͈̔͂ɐ���
    Time = std::clamp(Time, 0.0f, 1.0f);

    const float c5 = (2 * DirectX::XM_PI) / 4.5f;

    float t;
    if (Time == 0.0f)
        t = 0.0f;
    else if (Time == 1.0f)
        t = 1.0f;
    else if (Time < 0.5f)
        t = -(std::powf(2, 20 * Time - 10) * std::sin((20 * Time - 11.125f) * c5)) / 2;  // powf �� sinf ���g�p
    else
        t = (std::powf(2, -20 * Time + 10) * std::sin((20 * Time - 11.125f) * c5)) / 2 + 1;

    // ���
    DirectX::SimpleMath::Vector3 Result = DirectX::SimpleMath::Vector3::Lerp(Start, Goal, t);

    return Result;
}

DirectX::SimpleMath::Vector3 EaseInCirc(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time)
{
    // Time �� 0.0 ���� 1.0 �͈̔͂ɐ���
    Time = std::clamp(Time, 0.0f, 1.0f);

    float t = 1 - std::sqrtf(1 - std::powf(Time, 2));  // std::sqrtf �� powf ���g�p

    // ���
    DirectX::SimpleMath::Vector3 Result = DirectX::SimpleMath::Vector3::Lerp(Start, Goal, t);

    return Result;
}