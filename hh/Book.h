#pragma once
#include "CFBXMesh.h"
#include "CCollision.h"


class Book : public FBXMesh
{
private:

	DirectX::SimpleMath::Vector3 size = {10.0f,10.0f,10.0f};
	bool thisbook = false;

public:

	SQUARE3D square = { 0.0f,0.0f,0.0f , 0.0f,0.0f,0.0f };

	void CollisionInit(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 size);

	void Setthisbook(bool flg) { this->thisbook = flg; };
	bool Getthisbook() { return this->thisbook; };




};

