#include "ActionMoveToWaypoint.h"
#include "Enemy.h"
#include "easings.h"

bool ActionMoveToWaypoint::Execute(Enemy* enemy)
{

    DirectX::SimpleMath::Vector3 target = enemy->GetTargetPos();
    DirectX::SimpleMath::Vector3 current = enemy->GetPosition();

    DirectX::SimpleMath::Vector3 direction = target - current;
    float distance = direction.Length();

    if (distance < enemy->GetMoveSpeed() * 2.5f) {
        return true; // ���łɖړI�n�ɋ߂��ꍇ�A�ړ����Ȃ�
    }

    // ���K�����Ĉړ�
    direction.Normalize();
    enemy->SetPosition(current + direction * enemy->GetMoveSpeed());

    //�i�s�����Ɍ����ĉ�]���X�V
    if (direction.LengthSquared() > 0.0f) {
        DirectX::SimpleMath::Vector3 currentForward = enemy->Getforward();
        DirectX::SimpleMath::Vector3 newForward = EaseInCirc(currentForward, direction, enemy->GetTime1());
        enemy->Setforward(newForward);
        enemy->SetTime1(enemy->GetTime1() + enemy->Getdeltatime());
        if (enemy->GetTime1() >= 1.0f) {
            enemy->SetTime1(0.0f);
        }
    }


    return false;
}
