#include "GoalObj.h"
#include "easings.h"

using namespace DirectX::SimpleMath;

GoalObj::GoalObj(float X, float Y, float Z)
{
	this->square.type = ObjectType::Goal;

	// マテリアル生成
	MATERIAL	mtrl;
	mtrl.Ambient = DirectX::SimpleMath::Color(0, 0, 0, 0);
	mtrl.Diffuse = DirectX::SimpleMath::Color(1, 1, 1, 1);
	mtrl.Emission = DirectX::SimpleMath::Color(0, 0, 0, 0);
	mtrl.Specular = DirectX::SimpleMath::Color(0, 0, 0, 0);
	mtrl.Shiness = 0;
	mtrl.TextureEnable = TRUE;

	this->Init(X, Y, Z, DirectX::SimpleMath::Color(0.0f, 0.75f, 0.75f, 0.5f),
		"assets\\siro.jpg", "shader/unlitTextureVS.hlsl", "shader/unlitTexturePS.hlsl", mtrl);

	this->square.sizeX = X;
	this->square.sizeY = Y;
	this->square.sizeZ = Z;

	this->SetClear(false);
}

GoalObj::~GoalObj()
{

}

void GoalObj::Update(SQUARE3D Plsquare)
{
	CMesh::Update();


	// 現在の回転を取得
	Vector3 currentRotation = this->GetRotation();

	// Y軸の回転を少しずつ増加させる
	currentRotation.x += 1.0f;
	currentRotation.y += 1.0f;
	currentRotation.z += 1.0f;

	// Y軸の回転が359度を超えたら0度に戻す
	if (currentRotation.y >= 360.0f)
	{
		currentRotation.x -= 360.0f;
		currentRotation.y -= 360.0f;
		currentRotation.z -= 360.0f;
	}

	// 新しい回転をセット
	this->SetRotation(currentRotation);

	if (CCollision::Square3DCollision(this->square, Plsquare))
	{
		this->SetClear(true);
	}


}

void GoalObj::TitleUpdate()
{
	CMesh::Update();

	// 現在の回転を取得
	Vector3 currentRotation = this->GetRotation();

	// Y軸の回転を少しずつ増加させる
	currentRotation.x += 1.0f;
	currentRotation.y += 1.0f;
	currentRotation.z += 1.0f;

	// Y軸の回転が359度を超えたら0度に戻す
	if (currentRotation.y >= 360.0f)
	{
		currentRotation.x -= 360.0f;
		currentRotation.y -= 360.0f;
		currentRotation.z -= 360.0f;
	}

	// 新しい回転をセット
	this->SetRotation(currentRotation);
}

void GoalObj::CollisionInit(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 size)
{
	//立方体の中心点
	this->square.centerX = pos.x;
	this->square.centerY = pos.y;
	this->square.centerZ = pos.z;
	//立方体のサイズ
	this->square.sizeX = size.x;
	this->square.sizeY = size.y;
	this->square.sizeZ = size.z;
}
