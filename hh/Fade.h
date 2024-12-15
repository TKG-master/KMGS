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
    float alpha;       // ���݂̓����x
    float fadeSpeed;   // �t�F�[�h���x
    bool fadingIn;     // �t�F�[�h�C�������ǂ���
    bool fadingOut;    // �t�F�[�h�A�E�g�����ǂ���

public:
    Fade();

    void StartFadeIn(float speed);
    void StartFadeOut(float speed);

    void Update() override;
    void Draw() override;
};

