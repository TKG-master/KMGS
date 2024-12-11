#pragma once
#include "CBoxMesh.h"
#include "CCollision.h"

class GoalObj : public BoxMesh
{
private:
	bool Hit;
	float Time = 0.01f;
	// 例: フレーム毎の時間（16ms）
	float deltaTime = 0.016f;

	bool TestScale = true;

	bool Clear = false;

public:

	SQUARE3D square = { 0.0f,0.0f,0.0f , 0.0f,0.0f,0.0f };

	GoalObj(float X, float Y, float Z);
	~GoalObj();

	void CollisionInit(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 size);

	SQUARE3D GetCollisionSize() { return this->square; };

	void Update(SQUARE3D Plsquare);

	void Setsquare3D(SQUARE3D S) {
		this->square.sizeX = S.sizeX;
		this->square.sizeY = S.sizeY;
		this->square.sizeZ = S.sizeZ;
	}
	//クリアのbool型のセッターとゲッター
	void SetClear(bool flg) { this->Clear = flg; };
	bool GetClear() { return this->Clear; };

	void TitleUpdate();


	void SetHit(bool T) { this->Hit = T; };
	bool GetHit() { return this->Hit; };
};

