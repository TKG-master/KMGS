#pragma once
#include "CBoxMesh.h"
#include "CCollision.h"

class BoxObj : public BoxMesh
{
private:
	bool Hit;
	bool starteasing = false;

public:
	
	SQUARE3D square = { 0.0f,0.0f,0.0f , 0.0f,0.0f,0.0f };

	BoxObj(float X,float Y,float Z,std::string TexPath);
	~BoxObj();

	void SetObjectType(ObjectType Type) { this->square.type = Type; };

	void CollisionInit(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 size);

	SQUARE3D GetCollisionSize() { return this->square; };

	void Setsquare3D(SQUARE3D S) {
		this->square.sizeX = S.sizeX;
		this->square.sizeY = S.sizeY;
		this->square.sizeZ = S.sizeZ;
	}

	void SetHit(bool T) { this->Hit = T; };
	bool GetHit() { return this->Hit; };

	void SetStartEasing(bool E) { this->starteasing = true; };
	bool GetStartEasing() { return this->starteasing; };
	

};

