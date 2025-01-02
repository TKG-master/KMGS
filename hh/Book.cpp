#include "Book.h"

void Book::CollisionInit(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 size)
{
	this->square.type = ObjectType::BOOK;
	//�����̂̒��S�_
	this->square.centerX = pos.x;
	this->square.centerY = pos.y;
	this->square.centerZ = pos.z;
	//�����̂̃T�C�Y
	this->square.sizeX = size.x;
	this->square.sizeY = size.y;
	this->square.sizeZ = size.z;
}
