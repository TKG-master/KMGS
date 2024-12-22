#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <chrono>
#include <string>
#include <sstream>
#include <iomanip> // std::setfill, std::setw

using namespace DirectX;

class Timer;

class TimerUI
{
private:
    Timer* timer;                    // タイマーインスタンス
public:

	TimerUI(ID3D11Device* dev, ID3D11DeviceContext* ctx);
	~TimerUI();

	void Update();


};

