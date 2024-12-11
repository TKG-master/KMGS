#pragma once
#include <SimpleMath.h>
#include <DirectXCollision.h> // BoundingBoxクラスが含まれているヘッダー
#include "Type.h"

struct SQUARE3D {
	float centerX;	// Boxコライダーの中心点X
	float centerZ;	// Boxコライダーの中心点Z
	float centerY;	// Boxコライダーの中心点Y
	float sizeX;	// Boxコライダーのx方向の大きさ
	float sizeY;	// Boxコライダーのy方向の大きさ
	float sizeZ;	// Boxコライダーのz方向の大きさ
	ObjectType type;
};
// 補正方向型の定義
struct CORRECT_DIR
{
	int x;
	int z;
};

class BoxObj;

class CCollision
{
private:

public:

	struct SQUARE {
		float centerX;	// Boxコライダーの中心点X
		float centerZ;	// Boxコライダーの中心点Z
		float sizeX;	// Boxコライダーのx方向の大きさ
		float sizeZ;	// Boxコライダーのy方向の大きさ

		// 四角形を移動する関数
		void Moveplus(float dx, float dz) {
			centerX += dx;
			centerZ += dz;
		}

		void Moveminus(float dx, float dz) {
			centerX -= dx;
			centerZ -= dz;
		}

		void operator = (DirectX::SimpleMath::Vector3 n) {
			this->centerX = n.x;
			this->centerZ = n.z;
		}

	};

	SQUARE3D square3d;
	SQUARE square;

	void Init(DirectX::SimpleMath::Vector3 V);

	//立方体の当たり判定
	static bool Square3DCollision(const SQUARE3D& box1, const SQUARE3D& box2);

	// レイと立方体の当たり判定
	static bool RayIntersectsBox(const DirectX::SimpleMath::Vector3& origin,
		const DirectX::SimpleMath::Vector3& direction, 
		const SQUARE3D& targetbox,
		const std::vector<BoxObj*>& obstacleBoxes,
		float& hitDistance);

	static CORRECT_DIR ResolveCollision(SQUARE3D& box1, SQUARE3D& box2);


	//squareの中身をゲット
	float GetCenterpoint();

	//squareをセット
	void SetCenterpoint(float CeneterpointX, float CeneterpointZ , float sizeX,float sizeZ);
	
	void SetSquare3D(float CeneterpointX, float CeneterpointY,float CeneterpointZ, float sizeX,float sizeY,float sizeZ);

	// 点が円の中に入っているかの判定
	static bool PointInCircle(DirectX::SimpleMath::Vector3 Pos, float radius,const DirectX::SimpleMath::Vector3& point);

};
