#pragma once
#include <DirectXMath.h> // DirextX�̐��w�֘A�̃w�b�_�[�t�@�C��
#include <SimpleMath.h>
#include "AnimObj.h"
#include "CCollision.h"

class GameObject
{

protected:

	//SRT���i�p�����j
	DirectX::SimpleMath::Vector3 m_Position = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Rotation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Scale = DirectX::SimpleMath::Vector3(0.1f, 0.1f, 0.1f);

	// �u�����h���[�g
	float BlendRate = 0.0f;

	// �A�j���[�V�����C���f�b�N�X
	int idx = 0;

	// �d��
	float gravity = 9.81f;

public:

	GameObject();
	~GameObject();
	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Uninit();

	void AnimInit();
	void AnimUpdate();
	void AnimDraw();

};

