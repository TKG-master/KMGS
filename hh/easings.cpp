#include "easings.h"
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <SimpleMath.h>
#include <cmath>
#include <algorithm>


DirectX::SimpleMath::Vector3 EaseInOut(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time)
{
	// Time を 0.0 から 1.0 の範囲に制限
	Time = std::clamp(Time, 0.0f, 1.0f);

	float t;

	//イージングの計算
	if (Time < 0.5f)
	{
		t = 8 * Time * Time * Time * Time;
	}
	else
	{
		t = 1 - pow(-2 * Time + 2, 4) / 2;
	}

	// 補間
	DirectX::SimpleMath::Vector3 Result = DirectX::SimpleMath::Vector3::Lerp(Start, Goal, t);
	return Result;
}

DirectX::SimpleMath::Vector3 EaseInOutCirc(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time)
{
	// Time を 0.0 から 1.0 の範囲に制限
	Time = std::clamp(Time, 0.0f, 1.0f);

	float t;

	if (Time < 0.5f) {
		t = (1.0f - sqrt(1.0f - pow(2.0f * Time, 2.0f))) / 2.0f;
	}
	else {
		t = (sqrt(1.0f - pow(-2.0f * Time + 2.0f, 2.0f)) + 1.0f) / 2.0f;
	}

	// 補間
	DirectX::SimpleMath::Vector3 Result = DirectX::SimpleMath::Vector3::Lerp(Start, Goal, t);

	return Result;
}

DirectX::SimpleMath::Vector3 EaseInOutQuart(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time)
{
	// Time を 0.0 から 1.0 の範囲に制限
	Time = std::clamp(Time, 0.0f, 1.0f);

	// EaseInOutQuart の計算
	float t;
	if (Time < 0.5f) {
		t = 8 * Time * Time * Time * Time;
	}
	else {
		t = 1 - std::pow(-2 * Time + 2, 4) / 2;
	}

	// Lerp を使って Start から Goal へのベクトルを補間
	DirectX::SimpleMath::Vector3 Result = DirectX::SimpleMath::Vector3::Lerp(Start, Goal, t);

	return Result;
}

DirectX::SimpleMath::Vector3 EaselnSine(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time)
{
	// Time を 0.0 から 1.0 の範囲に制限
	Time = std::clamp(Time, 0.0f, 1.0f);

	// easeInSine の計算
	float t = 1.0f - std::cos((Time * DirectX::XM_PI) / 2.0f);

	// Lerp を使って Start から Goal へのベクトルを補間
	DirectX::SimpleMath::Vector3 Result = DirectX::SimpleMath::Vector3::Lerp(Start, Goal, t);

	// Lerp を使って Start から Goal へのベクトルを補間
	return Result;
}

DirectX::SimpleMath::Vector3 EaselnBack(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time)
{
	// Time を 0.0 から 1.0 の範囲に制限
	Time = std::clamp(Time, 0.0f, 1.0f);

	// バックイージングの計算
	const float c1 = 1.70158f;
	const float c3 = c1 + 1.0f;

	float t = c3 * Time * Time * Time - c1 * Time * Time;

	// Lerp を使って Start から Goal へのベクトルを補間
	DirectX::SimpleMath::Vector3 Result = DirectX::SimpleMath::Vector3::Lerp(Start, Goal, t);

	return Result;
}

DirectX::SimpleMath::Vector3 EaselnOutBack(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time)
{
	// Time を 0.0 から 1.0 の範囲に制限
	Time = std::clamp(Time, 0.0f, 1.0f);

	// バックイージングの計算
	const float c1 = 1.70158f;
	const float c2 = c1 * 1.525f;

	float t;
	if (Time < 0.5f) {
		t = (std::pow(2 * Time, 2) * ((c2 + 1) * 2 * Time - c2)) / 2;
	}
	else {
		t = (std::pow(2 * Time - 2, 2) * ((c2 + 1) * (2 * Time - 2) + c2) + 2) / 2;
	}

	// Lerp を使って Start から Goal へのベクトルを補間
	DirectX::SimpleMath::Vector3 Result = DirectX::SimpleMath::Vector3::Lerp(Start, Goal, t);

	return Result;
}

DirectX::SimpleMath::Vector3 EaselnOutQuint(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time)
{
	// Time を 0.0 から 1.0 の範囲に制限
	Time = std::clamp(Time, 0.0f, 1.0f);

	float t = 1.0f - pow(1.0f - Time, 5.0f);

	// Lerp を使って Start から Goal へのベクトルを補間
	DirectX::SimpleMath::Vector3 Result = DirectX::SimpleMath::Vector3::Lerp(Start, Goal, t);

	return Result;
}

DirectX::SimpleMath::Vector3 EaselnElastic(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time)
{
	// Time を 0.0 から 1.0 の範囲に制限
	Time = std::clamp(Time, 0.0f, 1.0f);

	const float c4 = (2 * DirectX::XM_PI) / 3;

	float t = 0.0f;

	if (Time == 0) {
		t = 0;
	}
	else if (Time == 1) {
		t = 1;
	}
	else {
		t = -pow(2, -10 * Time) * sin((Time * 10 - 0.75) * c4) + 1;
	}

	// Lerp を使って Start から Goal へのベクトルを補間
	DirectX::SimpleMath::Vector3 Result = DirectX::SimpleMath::Vector3::Lerp(Start, Goal, t);

	return Result;
}

DirectX::SimpleMath::Vector3 EaselnQuart(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time)
{

	// Time を 0.0 から 1.0 の範囲に制限
	Time = std::clamp(Time, 0.0f, 1.0f);

	float t = Time * Time * Time * Time;

	// Lerp を使って Start から Goal へのベクトルを補間
	DirectX::SimpleMath::Vector3 Result = DirectX::SimpleMath::Vector3::Lerp(Start, Goal, t);

	return Result;
}

DirectX::SimpleMath::Vector3 EaselnQutExpo(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time)
{
	// Time を 0.0 から 1.0 の範囲に制限
	Time = std::clamp(Time, 0.0f, 1.0f);

	float t;
	if (Time == 0) {
		t = 0;
	}
	else if (Time == 1) {
		t = 1;
	}
	else if (Time < 0.5f) {
		t = std::pow(2, 20 * Time - 10) / 2;
	}
	else {
		t = (2 - std::pow(2, -20 * Time + 10)) / 2;
	}


	// Lerp を使って Start から Goal へのベクトルを補間
	DirectX::SimpleMath::Vector3 Result = DirectX::SimpleMath::Vector3::Lerp(Start, Goal, t);

	return Result;
}

DirectX::SimpleMath::Vector3 EaseOutCirc(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time)
{
	// Time を 0.0 から 1.0 の範囲に制限
	Time = std::clamp(Time, 0.0f, 1.0f);

	float t = std::sqrt(1 - std::pow(Time - 1, 2));

	// Lerp を使って Start から Goal へのベクトルを補間
	DirectX::SimpleMath::Vector3 Result = DirectX::SimpleMath::Vector3::Lerp(Start, Goal, t);

	return Result;
}

DirectX::SimpleMath::Vector3 easeInOutElastic(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time)
{
	// Time を 0.0 から 1.0 の範囲に制限
	Time = std::clamp(Time, 0.0f, 1.0f);

	const float c5 = (2 * DirectX::XM_PI) / 4.5f;

	float t;
	if (Time == 0.0f)
		t = 0.0f;
	else if (Time == 1.0f)
		t = 1.0f;
	else if (Time < 0.5f)
		t = -(std::pow(2, 20 * Time - 10) * std::sin((20 * Time - 11.125f) * c5)) / 2;
	else
		t = (std::pow(2, -20 * Time + 10) * std::sin((20 * Time - 11.125f) * c5)) / 2 + 1;

	// Lerp を使って Start から Goal へのベクトルを補間
	DirectX::SimpleMath::Vector3 Result = DirectX::SimpleMath::Vector3::Lerp(Start, Goal, t);

	return Result;
}

DirectX::SimpleMath::Vector3 EaseInCirc(DirectX::SimpleMath::Vector3 Start, DirectX::SimpleMath::Vector3 Goal, float Time)
{
	// Time を 0.0 から 1.0 の範囲に制限
	Time = std::clamp(Time, 0.0f, 1.0f);

	float t = 1 - std::sqrt(1 - std::pow(Time, 2));

	// Lerp を使って Start から Goal へのベクトルを補間
	DirectX::SimpleMath::Vector3 Result = DirectX::SimpleMath::Vector3::Lerp(Start, Goal, t);

	return Result;
}