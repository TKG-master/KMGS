#pragma once
#include"CScene.h"
#include "Camera.h"
#include "Field.h"
#include "Player.h"
#include "Enemy.h"
#include "structs.h"
#include "Radar.h"
#include "CBoxMesh.h"


class AnimScene : public CScene
{
private:
	Camera* camera;
	Player* Pl;
	Enemy* enemy;
	Enemy* enemy2;

	BoxMesh* box;

	Radar* radar;

	DirectX::SimpleMath::Vector3 CharacterScale = DirectX::SimpleMath::Vector3(0.5f, 0.5f, 0.5f);

	int enemyCount = 2; // 必要な敵の数

public:
	//コンストラクタ
	AnimScene();
	//デスストラクタ
	~AnimScene();

	//関数のオーバーライド
	void Update() override;
	void Draw() override;
	void Init() override;
	void UnInit() override;
};

