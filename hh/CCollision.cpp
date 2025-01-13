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
    // box1の各辺の最小値と最大値を計算
    float box1MinX = box1.centerX - box1.sizeX / 2;
    float box1MaxX = box1.centerX + box1.sizeX / 2;
    float box1MinY = box1.centerY - box1.sizeY / 2;
    float box1MaxY = box1.centerY + box1.sizeY / 2;
    float box1MinZ = box1.centerZ - box1.sizeZ / 2;
    float box1MaxZ = box1.centerZ + box1.sizeZ / 2;

    // box2の各辺の最小値と最大値を計算
    float box2MinX = box2.centerX - box2.sizeX / 2;
    float box2MaxX = box2.centerX + box2.sizeX / 2;
    float box2MinY = box2.centerY - box2.sizeY / 2;
    float box2MaxY = box2.centerY + box2.sizeY / 2;
    float box2MinZ = box2.centerZ - box2.sizeZ / 2;
    float box2MaxZ = box2.centerZ + box2.sizeZ / 2;

    // 各軸において、重なりがあるかどうかをチェック
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
    //DirectXCollision の BoundingBox を使用して当たり判定を行う
    DirectX::BoundingBox boundingBox(
        DirectX::XMFLOAT3(box.centerX,(box.centerY + 50.0f), box.centerZ),
        DirectX::XMFLOAT3(box.sizeX / 2.0f, box.sizeY/* / 2.0f*/, box.sizeZ / 2.0f)
    );

    //プレイヤーにレイが当たるかどうかを確認
    bool hitTarget = boundingBox.Intersects(origin, direction, hitDistance);

    if (!hitTarget)
    {
        return false; // プレイヤーに当たらなければ false を返す
    }

    //プレイヤーに当たるまでの距離を保存
    float targetHitDistance = hitDistance;

    //障害物との当たり判定を確認
    for (const auto& boxObj : obstacleBoxes)
    {
        const SQUARE3D& box = boxObj->GetCollisionSize();
        DirectX::BoundingBox obstacleBoundingBox(
            DirectX::XMFLOAT3(box.centerX, box.centerY, box.centerZ),
            DirectX::XMFLOAT3(box.sizeX / 2.0f, box.sizeY / 2.0f, box.sizeZ / 2.0f)
        );

        //当たるまでの距離を保存
        float obstacleHitDistance;
        bool hitObstacle = obstacleBoundingBox.Intersects(origin, direction, obstacleHitDistance);

        //障害物に当たりその距離がプレイヤーに当たるまでの距離よりも短い場合かつオブジェクトのタイプがBOX
        if (hitObstacle && obstacleHitDistance < targetHitDistance && box.type == ObjectType::BOX)
        {
            return false; // 障害物（Box）に当たったら false を返す
        }
    }

    //障害物に当たらなかったらプレイヤーに当たるので true を返す
    hitDistance = targetHitDistance;
    return true;

}

CORRECT_DIR CCollision::ResolveCollision(SQUARE3D& box1, SQUARE3D& box2)
{
    // x,y,zそれぞれめり込んでいる長さを計算
    float overlapX = ((box1.sizeX / 2) + (box2.sizeX / 2)) - std::abs(box1.centerX - box2.centerX);
    float overlapY = ((box1.sizeY / 2) + (box2.sizeY / 2)) - std::abs(box1.centerY - box2.centerY);
    float overlapZ = ((box1.sizeZ / 2) + (box2.sizeZ / 2)) - std::abs(box1.centerZ - box2.centerZ);
    // 補正した方向を格納するCORRECT_DIR型変数
    CORRECT_DIR correct_dir = { 0 };

    // コライダーを補正する
    if (overlapZ < overlapX && overlapZ < overlapY)
    {
        // Z軸方向にめり込んでいる場合
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
        // X軸方向にめり込んでいる場合
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
    //    // Y軸方向にめり込んでいる場合
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


    // コライダーを補正する
    //if (overlapZ < overlapX)
    //{
    //    // Y軸方向にめり込んでいる場合
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
    //    // X軸方向にめり込んでいる場合
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
    // ボックスの境界に扇形が交差するかを計算するロジックを実装
    // 例えば、扇形の外周がボックスに接触するかをチェックします
    // ここでは簡単なチェックの一例を示します
    return (point.x >= box.centerX - box.sizeX / 2 &&
        point.x <= box.centerX + box.sizeX / 2 &&
        point.z >= box.centerZ - box.sizeZ / 2 &&
        point.z <= box.centerZ + box.sizeZ / 2);
}

bool CCollision::RayIntersectsBox(const DirectX::SimpleMath::Vector3& rayOrigin, const DirectX::SimpleMath::Vector3& rayDir, const SQUARE3D& box)
{
    // ボックスの面とレイの交差判定を行う関数

  // ボックスの最小値（min）と最大値（max）を計算
    float minX = box.centerX - box.sizeX / 2;
    float maxX = box.centerX + box.sizeX / 2;
    float minY = box.centerY - box.sizeY / 2;
    float maxY = box.centerY + box.sizeY / 2;
    float minZ = box.centerZ - box.sizeZ / 2;
    float maxZ = box.centerZ + box.sizeZ / 2;

    // レイの始点と方向を使って交差判定
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

    return true;  // レイとボックスが交差する場合
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




