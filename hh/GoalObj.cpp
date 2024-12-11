#include "GoalObj.h"
#include "easings.h"

using namespace DirectX::SimpleMath;

GoalObj::GoalObj(float X, float Y, float Z)
{
	this->square.type = ObjectType::Goal;

	// �}�e���A������
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


	// ���݂̉�]���擾
	Vector3 currentRotation = this->GetRotation();

	// Y���̉�]������������������
	currentRotation.x += 1.0f;
	currentRotation.y += 1.0f;
	currentRotation.z += 1.0f;

	// Y���̉�]��359�x�𒴂�����0�x�ɖ߂�
	if (currentRotation.y >= 360.0f)
	{
		currentRotation.x -= 360.0f;
		currentRotation.y -= 360.0f;
		currentRotation.z -= 360.0f;
	}

	// �V������]���Z�b�g
	this->SetRotation(currentRotation);

	if (CCollision::Square3DCollision(this->square, Plsquare))
	{
		this->SetClear(true);
	}


}

void GoalObj::TitleUpdate()
{
	CMesh::Update();

	// ���݂̉�]���擾
	Vector3 currentRotation = this->GetRotation();

	// Y���̉�]������������������
	currentRotation.x += 1.0f;
	currentRotation.y += 1.0f;
	currentRotation.z += 1.0f;

	// Y���̉�]��359�x�𒴂�����0�x�ɖ߂�
	if (currentRotation.y >= 360.0f)
	{
		currentRotation.x -= 360.0f;
		currentRotation.y -= 360.0f;
		currentRotation.z -= 360.0f;
	}

	// �V������]���Z�b�g
	this->SetRotation(currentRotation);
}

void GoalObj::CollisionInit(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 size)
{
	//�����̂̒��S�_
	this->square.centerX = pos.x;
	this->square.centerY = pos.y;
	this->square.centerZ = pos.z;
	//�����̂̃T�C�Y
	this->square.sizeX = size.x;
	this->square.sizeY = size.y;
	this->square.sizeZ = size.z;
}
