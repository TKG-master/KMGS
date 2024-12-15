#include "Fade.h"

using namespace DirectX::SimpleMath;

Fade::Fade()
    : alpha(1.0f), fadeSpeed(1.0f), fadingIn(false), fadingOut(false)
{}

void Fade::StartFadeIn(float speed)
{
    fadeSpeed = speed;
    fadingIn = true;
    fadingOut = false;
}

void Fade::StartFadeOut(float speed)
{
    fadeSpeed = speed;
    fadingIn = false;
    fadingOut = true;
}

void Fade::Update()
{
    GameUI::Update();

    if (fadingIn)
    {
        alpha += fadeSpeed;
        if (alpha >= 1.0f)
        {
            alpha = 1.0f;
            fadingIn = false;
        }
    }
    else if (fadingOut)
    {
        alpha -= fadeSpeed;
        if (alpha <= 0.0f)
        {
            alpha = 0.0f;
            fadingOut = false;
        }
    }

    // アルファ値を更新
    color = DirectX::SimpleMath::Color(color.R(), color.G(), color.B(), alpha);
}

void Fade::Draw()
{
    if (alpha > 0.0f)
    {
        GameUI::Draw();
    }
}