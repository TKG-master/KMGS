#pragma once
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CShader.h"
#include "CMaterial.h"
#include "CTexture.h"
#include "GameResult.h"


class Fade : public GameUI
{
private:
    float alpha;       // 現在の透明度
    float fadeSpeed;   // フェード速度
    bool fadingIn;     // フェードイン中かどうか
    bool fadingOut;    // フェードアウト中かどうか

public:
    Fade();

    void StartFadeIn(float speed);
    void StartFadeOut(float speed);

    void Update() override;
    void Draw() override;
};

