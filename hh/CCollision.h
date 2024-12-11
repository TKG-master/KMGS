#pragma once
#include <SimpleMath.h>
#include <DirectXCollision.h> // BoundingBox�N���X���܂܂�Ă���w�b�_�[
#include "Type.h"

struct SQUARE3D {
	float centerX;	// Box�R���C�_�[�̒��S�_X
	float centerZ;	// Box�R���C�_�[�̒��S�_Z
	float centerY;	// Box�R���C�_�[�̒��S�_Y
	float sizeX;	// Box�R���C�_�[��x�����̑傫��
	float sizeY;	// Box�R���C�_�[��y�����̑傫��
	float sizeZ;	// Box�R���C�_�[��z�����̑傫��
	ObjectType type;
};
// �␳�����^�̒�`
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
		float centerX;	// Box�R���C�_�[�̒��S�_X
		float centerZ;	// Box�R���C�_�[�̒��S�_Z
		float sizeX;	// Box�R���C�_�[��x�����̑傫��
		float sizeZ;	// Box�R���C�_�[��y�����̑傫��

		// �l�p�`���ړ�����֐�
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

	//�����̂̓����蔻��
	static bool Square3DCollision(const SQUARE3D& box1, const SQUARE3D& box2);

	// ���C�Ɨ����̂̓����蔻��
	static bool RayIntersectsBox(const DirectX::SimpleMath::Vector3& origin,
		const DirectX::SimpleMath::Vector3& direction, 
		const SQUARE3D& targetbox,
		const std::vector<BoxObj*>& obstacleBoxes,
		float& hitDistance);

	static CORRECT_DIR ResolveCollision(SQUARE3D& box1, SQUARE3D& box2);


	//square�̒��g���Q�b�g
	float GetCenterpoint();

	//square���Z�b�g
	void SetCenterpoint(float CeneterpointX, float CeneterpointZ , float sizeX,float sizeZ);
	
	void SetSquare3D(float CeneterpointX, float CeneterpointY,float CeneterpointZ, float sizeX,float sizeY,float sizeZ);

	// �_���~�̒��ɓ����Ă��邩�̔���
	static bool PointInCircle(DirectX::SimpleMath::Vector3 Pos, float radius,const DirectX::SimpleMath::Vector3& point);

};
