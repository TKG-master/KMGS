#include "CCollision.h"
#include "GUI.h"
#include "BoxObj.h"
#include "Enemy.h"

using namespace DirectX::SimpleMath;

void CCollision::Init(DirectX::SimpleMath::Vector3 V)
{
    square.centerX = V.x;
    square.centerZ = V.z;
}


bool CCollision::Square3DCollision(const SQUARE3D& box1, const SQUARE3D& box2)
{
    // box1�̊e�ӂ̍ŏ��l�ƍő�l���v�Z
    float box1MinX = box1.centerX - box1.sizeX / 2;
    float box1MaxX = box1.centerX + box1.sizeX / 2;
    float box1MinY = box1.centerY - box1.sizeY / 2;
    float box1MaxY = box1.centerY + box1.sizeY / 2;
    float box1MinZ = box1.centerZ - box1.sizeZ / 2;
    float box1MaxZ = box1.centerZ + box1.sizeZ / 2;

    // box2�̊e�ӂ̍ŏ��l�ƍő�l���v�Z
    float box2MinX = box2.centerX - box2.sizeX / 2;
    float box2MaxX = box2.centerX + box2.sizeX / 2;
    float box2MinY = box2.centerY - box2.sizeY / 2;
    float box2MaxY = box2.centerY + box2.sizeY / 2;
    float box2MinZ = box2.centerZ - box2.sizeZ / 2;
    float box2MaxZ = box2.centerZ + box2.sizeZ / 2;

    // �e���ɂ����āA�d�Ȃ肪���邩�ǂ������`�F�b�N
    bool xOverlap = (box1MinX <= box2MaxX) && (box1MaxX >= box2MinX);
    bool yOverlap = (box1MinY <= box2MaxY) && (box1MaxY >= box2MinY);
    bool zOverlap = (box1MinZ <= box2MaxZ) && (box1MaxZ >= box2MinZ);

    if (xOverlap && zOverlap && yOverlap)
    {
        return true;
    }
    else
    {
        return false;
    }
}




bool CCollision::RayIntersectsBox(const DirectX::SimpleMath::Vector3& origin, const DirectX::SimpleMath::Vector3& direction, const SQUARE3D& box, const std::vector<BoxObj*>& obstacleBoxes,float& hitDistance)
{
    //DirectXCollision �� BoundingBox ���g�p���ē����蔻����s��
    DirectX::BoundingBox boundingBox(
        DirectX::XMFLOAT3(box.centerX,(box.centerY + 50.0f), box.centerZ),
        DirectX::XMFLOAT3(box.sizeX / 2.0f, box.sizeY/* / 2.0f*/, box.sizeZ / 2.0f)
    );

    //�v���C���[�Ƀ��C�������邩�ǂ������m�F
    bool hitTarget = boundingBox.Intersects(origin, direction, hitDistance);

    if (!hitTarget)
    {
        return false; // �v���C���[�ɓ�����Ȃ���� false ��Ԃ�
    }

    //�v���C���[�ɓ�����܂ł̋�����ۑ�
    float targetHitDistance = hitDistance;

    //��Q���Ƃ̓����蔻����m�F
    for (const auto& boxObj : obstacleBoxes)
    {
        const SQUARE3D& box = boxObj->GetCollisionSize();
        DirectX::BoundingBox obstacleBoundingBox(
            DirectX::XMFLOAT3(box.centerX, box.centerY, box.centerZ),
            DirectX::XMFLOAT3(box.sizeX / 2.0f, box.sizeY / 2.0f, box.sizeZ / 2.0f)
        );

        //������܂ł̋�����ۑ�
        float obstacleHitDistance;
        bool hitObstacle = obstacleBoundingBox.Intersects(origin, direction, obstacleHitDistance);

        //��Q���ɓ����肻�̋������v���C���[�ɓ�����܂ł̋��������Z���ꍇ���I�u�W�F�N�g�̃^�C�v��BOX
        if (hitObstacle && obstacleHitDistance < targetHitDistance && box.type == ObjectType::BOX)
        {
            return false; // ��Q���iBox�j�ɓ��������� false ��Ԃ�
        }
    }

    //��Q���ɓ�����Ȃ�������v���C���[�ɓ�����̂� true ��Ԃ�
    hitDistance = targetHitDistance;
    return true;

}

CORRECT_DIR CCollision::ResolveCollision(SQUARE3D& box1, SQUARE3D& box2)
{
    // x,y,z���ꂼ��߂荞��ł��钷�����v�Z
    float overlapX = ((box1.sizeX / 2) + (box2.sizeX / 2)) - std::abs(box1.centerX - box2.centerX);
    float overlapY = ((box1.sizeY / 2) + (box2.sizeY / 2)) - std::abs(box1.centerY - box2.centerY);
    float overlapZ = ((box1.sizeZ / 2) + (box2.sizeZ / 2)) - std::abs(box1.centerZ - box2.centerZ);
    // �␳�����������i�[����CORRECT_DIR�^�ϐ�
    CORRECT_DIR correct_dir = { 0 };

    // �R���C�_�[��␳����
    if (overlapZ < overlapX && overlapZ < overlapY)
    {
        // Z�������ɂ߂荞��ł���ꍇ
        if (box1.centerZ < box2.centerZ)
        {
            box1.centerZ -= overlapZ;
            correct_dir.z = -1;
        }
        else
        {
            box1.centerZ += overlapZ;
            correct_dir.z = 1;
        }
    }
    else if (overlapX < overlapZ && overlapX < overlapY) {
        // X�������ɂ߂荞��ł���ꍇ
        if (box1.centerX < box2.centerX)
        {
            box1.centerX -= overlapX;
            correct_dir.x = -1;
        }
        else
        {
            box1.centerX += overlapX;
            correct_dir.x = 1;
        }
    }
    //else {
    //    // Y�������ɂ߂荞��ł���ꍇ
    //    if (box1.centerY < box2.centerY)
    //    {
    //        box1.centerY -= overlapY;
    //    }
    //    else
    //    {
    //        box1.centerY += overlapY;
    //    }
    //}

    return correct_dir;


    // �R���C�_�[��␳����
    //if (overlapZ < overlapX)
    //{
    //    // Y�������ɂ߂荞��ł���ꍇ
    //    if (box1.centerZ < box2.centerZ)
    //    {
    //        box1.centerZ -= overlapZ;
    //        correct_dir.z = -1;
    //    }
    //    else
    //    {
    //        box1.centerZ += overlapZ;
    //        correct_dir.z = 1;
    //    }
    //}
    //else if (overlapX < overlapZ) {
    //    // X�������ɂ߂荞��ł���ꍇ
    //    if (box1.centerX < box2.centerX)
    //    {
    //        box1.centerX -= overlapX;
    //        correct_dir.x = -1;
    //    }
    //    else if (box1.centerX > box2.centerX)
    //    {
    //        box1.centerX += overlapX;
    //        correct_dir.x = 1;
    //    }
    //}

    //return correct_dir;

}

bool CCollision::IsCollisionWithBox(const DirectX::SimpleMath::Vector3& point, const SQUARE3D& box)
{
    // �{�b�N�X�̋��E�ɐ�`���������邩���v�Z���郍�W�b�N������
    // �Ⴆ�΁A��`�̊O�����{�b�N�X�ɐڐG���邩���`�F�b�N���܂�
    // �����ł͊ȒP�ȃ`�F�b�N�̈��������܂�
    return (point.x >= box.centerX - box.sizeX / 2 &&
        point.x <= box.centerX + box.sizeX / 2 &&
        point.z >= box.centerZ - box.sizeZ / 2 &&
        point.z <= box.centerZ + box.sizeZ / 2);
}

bool CCollision::RayIntersectsBox(const DirectX::SimpleMath::Vector3& rayOrigin, const DirectX::SimpleMath::Vector3& rayDir, const SQUARE3D& box)
{
    // �{�b�N�X�̖ʂƃ��C�̌���������s���֐�

  // �{�b�N�X�̍ŏ��l�imin�j�ƍő�l�imax�j���v�Z
    float minX = box.centerX - box.sizeX / 2;
    float maxX = box.centerX + box.sizeX / 2;
    float minY = box.centerY - box.sizeY / 2;
    float maxY = box.centerY + box.sizeY / 2;
    float minZ = box.centerZ - box.sizeZ / 2;
    float maxZ = box.centerZ + box.sizeZ / 2;

    // ���C�̎n�_�ƕ������g���Č�������
    float tmin = (minX - rayOrigin.x) / rayDir.x;
    float tmax = (maxX - rayOrigin.x) / rayDir.x;

    if (tmin > tmax) std::swap(tmin, tmax);

    float tymin = (minY - rayOrigin.y) / rayDir.y;
    float tymax = (maxY - rayOrigin.y) / rayDir.y;

    if (tymin > tymax) std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    if (tymin > tmin) tmin = tymin;
    if (tymax < tmax) tmax = tymax;

    float tzmin = (minZ - rayOrigin.z) / rayDir.z;
    float tzmax = (maxZ - rayOrigin.z) / rayDir.z;

    if (tzmin > tzmax) std::swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    return true;  // ���C�ƃ{�b�N�X����������ꍇ
}


void CCollision::SetCenterpoint(float CeneterpointX, float CeneterpointZ, float sizeX, float sizeZ)
{
    square.centerX = CeneterpointX;
    square.centerZ = CeneterpointZ;
    square.sizeX = sizeX;
    square.sizeZ = sizeZ;
}

void CCollision::SetSquare3D(float CeneterpointX, float CeneterpointY, float CeneterpointZ, float sizeX, float sizeY, float sizeZ)
{
    square3d.centerX = CeneterpointX;
    square3d.centerY = CeneterpointY;
    square3d.centerZ = CeneterpointZ;
    square3d.sizeX = sizeX;
    square3d.sizeY = sizeY;
    square3d.sizeZ = sizeZ;
}

bool CCollision::PointInCircle(DirectX::SimpleMath::Vector3 Pos, float radius, const DirectX::SimpleMath::Vector3& point)
{
    float dx = Pos.x - point.x;
    float dz = Pos.z - point.z;
    float distance = sqrt(dx * dx + dz * dz);
    return distance <= radius;
}




