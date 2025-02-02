#include "ActionSerchMove.h"
#include "Enemy.h"

bool ActionPathMove::Execute(Enemy* enemy)
{

    if (enemy->GetAstatus() != WALK)
    {
        enemy->SetAstatus(WALK);
    }

    // �ڕW�n�_���擾
    DirectX::SimpleMath::Vector3 targetPos = enemy->Getpath()[enemy->GetPathIndex()];
    DirectX::SimpleMath::Vector3 currentPosition = enemy->GetPosition();

    // �ړ��ʂ��v�Z
    DirectX::SimpleMath::Vector3 direction = targetPos - currentPosition;
    float distance = direction.Length();

    // ���e�͈͓��Ȃ玟�̃|�C���g��
    float tolerance = enemy->GetMoveSpeed() * 2.5f;
    if (distance < tolerance) {
        enemy->SetPosition(targetPos);
        if (enemy->GetPathIndex() <= enemy->Getpath().size())
        {
            enemy->SetPathIndex(enemy->GetPathIndex() + 1);
        }
        return true;
    }

    // �����𐳋K�����A�ړ�
    direction.Normalize();
    enemy->SetPosition(currentPosition + direction * enemy->GetMoveSpeed() * 1.5f);

    // �i�s�����Ɍ����ĉ�]���X�V
    if (direction.LengthSquared() > 0.0f) {
        //�������Z�b�g
        enemy->Setforward(direction);
        enemy->UpdateRotation();  // ��]�̍X�V
    }

    return false;

}
