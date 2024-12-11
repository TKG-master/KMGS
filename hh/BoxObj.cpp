#include "BoxObj.h"

BoxObj::BoxObj(float X, float Y, float Z, std::string TexPath)
{
	this->square.type = ObjectType::BOX;
	this->DrawInit(X, Y, Z , TexPath);
	this->square.sizeX = X;
	this->square.sizeY = Y;
	this->square.sizeZ = Z;
	m_Scale = { 0.0f,0.0f,0.0f };

}

BoxObj::~BoxObj()
{

}

void BoxObj::CollisionInit(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 size)
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
